//////////////////////////////////////////////////
// Simple NTP client for ESP8266, RTOS SDK.
// Copyright 2016 jp cocatrix (KaraWin)
// jp@karawin.fr
// See license.txt for license terms.
//////////////////////////////////////////////////
// esp32
#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#define TAG "NTP"
//
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
//#include <zlib.h>
#include "lwip/sockets.h"
#include "lwip/api.h"
#include "lwip/netdb.h"

#include "ntp.h"
#include "interface.h"

// list of major public servers http://tf.nist.gov/tf-cgi/servers.cgi
//time.nist.gov 


// A task if needed
/*
void ntpTask(void *pvParams) {

	while (1)
	{
		vTaskDelay(60000);
		ntp_get_time();
	}	
}
*/
// get ntp time and return an allocated tm struct (UTC)
bool ntp_get_time(struct tm **dt) {
	struct timeval timeout; 
    timeout.tv_usec = 0;
	timeout.tv_sec = 5; 
	int sockfd = 0;
	ntp_t* ntp;
	char *msg;
	int rv;
	char service[] = {"123"}; //ntp port
	char node[] = {"pool.ntp.org"}; // this one is universel
    struct addrinfo hints, *servinfo = NULL, *p = NULL;
//	struct tm *dt;
	time_t timestamp;
//	int8_t tz;
	
	msg = calloc(sizeof(ntp_t),1);
	if (msg == NULL){
		ESP_LOGE(TAG,"##SYS.DATE#: ntp fails on calloc");
		return false;
	} 
	// build the message to send
	ntp = (ntp_t*)msg;
	ntp->options = 0x1B; //3 first flags set in binary: 00 001 011  LI=0 VN=3 MODE=CLIENT
	ntp->stratum = 0;
	ntp->poll = 6;
	ntp->precision = 1;
//	ntp->ref_id = 0x4C4F434C; // LOCL

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM; // Use UDP
	if ((rv = getaddrinfo(node, service, &hints, &servinfo)) != 0) {
		//ESP_LOGE(TAG,"##SYS.DATE#: ntp fails on %s %d","getaddrinfo",rv);
		free(msg);
		return false;
	} 		
// loop in result socket
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,p->ai_protocol)) == -1) {
			ESP_LOGE(TAG,"##SYS.DATE#: ntp fails on %s %d","sockfd",sockfd);
			continue;
		}
		break;
	}
// set a timeout for recvfrom
	if (setsockopt (sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0){
		ESP_LOGE(TAG,"##SYS.DATE#: ntp fails on %s %d","setsockopt",0);	free (msg);freeaddrinfo(servinfo);	close(sockfd);
		return false;
	} 	
//send the request	
	if ((rv = sendto(sockfd, msg, sizeof(ntp_t), 0,p->ai_addr, p->ai_addrlen)) == -1) {
		ESP_LOGE(TAG,"##SYS.DATE#: ntp fails on %s %d","sendto",rv); free (msg);freeaddrinfo(servinfo);	close(sockfd);
		return false;					
	}
	freeaddrinfo(servinfo);	
 	if ((rv = recvfrom(sockfd, msg, sizeof(ntp_t) , 0,NULL, NULL)) <=0) {
		ESP_LOGE(TAG,"##SYS.DATE#: ntp fails on %s %d","recvfrom",rv);free(msg);close(sockfd);
		return false;	
	}	
			
	//extract time
	ntp = (ntp_t*)msg;	
	timestamp = ntp->trans_time[0] << 24 | ntp->trans_time[1] << 16 |ntp->trans_time[2] << 8 | ntp->trans_time[3];
	// convert to unix time
	timestamp -= 2208988800UL;
	// create tm struct
	*dt = gmtime(&timestamp);
	free(msg);
	close(sockfd);
	return true;
}

// print  date time in ISO-8601 local time format
void ntp_print_time() {
	struct tm* dt;
	int8_t tz;	
	char msg[30];
	
	if (ntp_get_time(&dt) )
	{
		tz =applyTZ(dt);
//	os_printf("##Time: isdst: %d %02d:%02d:%02d\n",dt->tm_isdst, dt->tm_hour, dt->tm_min, dt->tm_sec);		
//	os_printf("##Date: %02d-%02d-%04d\n", dt->tm_mday, dt->tm_mon+1, dt->tm_year+1900);	
		strftime(msg, 48, "%Y-%m-%dT%H:%M:%S", dt);
//	ISO-8601 local time   https://www.w3.org/TR/NOTE-datetime
//  YYYY-MM-DDThh:mm:ssTZD (eg 1997-07-16T19:20:30+01:00)
		if (tz >=0)
			kprintf("##SYS.DATE#: %s+%02d:00\n",msg,tz);
		else
			kprintf("##SYS.DATE#: %s%03d:00\n",msg,tz);
	}
		
}
