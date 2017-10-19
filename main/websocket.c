/* (c)jp cocatrix May 2016 
 *
 * Copyright 2016 karawin (http://www.karawin.fr)

	quick and dirty websocket inplementation for wifi webradio
	minimal implementaion for short data messages
*/
#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "esp_system.h"
#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"
#include "cencode_inc.h"
#include "websocket.h"
#include "interface.h"
#include "webserver.h"
#include "cencode_inc.h"
#include <stddef.h> /* for size_t */

#define TAG	"websocket"

char strwMALLOC[]  = {"inwmalloc fails for %d\n"};
char strwMALLOC1[]  = {"Websocket %s malloc fails\n"};
char strwSOCKET[]  = {"Websocket socket fails %s errno: %d\n"};

client_t webserverclients[NBCLIENT];
//set of socket descriptors
fd_set readfds;

/**
 * base64_encode
 * @param data uint8_t *
 * @param length size_t
 * @param output char*
 */
 
void *inwmalloc(size_t n)
{
	void* ret;
//printf ("ws Malloc of %d,  Heap size: %d\n",n,xPortGetFreeHeapSize( ));
	ret = malloc(n);
		if (ret == NULL) printf(strwMALLOC,n);
//	printf ("ws Malloc after of %d bytes ret:%x  Heap size: %d\n",n,ret,xPortGetFreeHeapSize( ));
	return ret;
}	
void inwfree(void *p,char* from)
{
	if (p != NULL) free(p);
//	printf ("ws free of %x,  from %s             Heap size: %d\n",p,from,xPortGetFreeHeapSize( ));
} 
 
void base64_encode(uint8_t * data, size_t length, char* output) {
//    size_t size = ((length * 1.6f) + 1);
    if(output) {
        base64_encodestate _state;
        base64_init_encodestate(&_state);
        int len = base64_encode_block((const char *) data, length, output, &_state);
        len = base64_encode_blockend((output + len), &_state);
    }
}


/**
 * generate the key for Sec-WebSocket-Accept
 * @param clientKey char*
 * @param Output char*
 */
void  websocketacceptKey(char* clientKey,char* Output) {
    uint8_t sha1HashBin[20] = { 0 };
    strcat(clientKey ,"258EAFA5-E914-47DA-95CA-C5AB0DC85B11");
	
    struct SHA1Context ctx;
	
    SHA1Init(&ctx);
    SHA1Update(&ctx, clientKey, strlen(clientKey));
    SHA1Final(&sha1HashBin[0], &ctx);
    base64_encode(sha1HashBin, 20,Output);
//    key.trim();
//	printf ("ws key: \"%s\"  output:\"%s\"\n",clientKey,Output);
}

void wsclientDisconnect(int socket, uint16_t code, char * reason, size_t reasonLen) {
	if(reason) {
         sendFrame(socket, WSop_close, (uint8_t *) reason, reasonLen);
    } else {
         uint8_t buffer[2];
         buffer[0] = ((code >> 8) & 0xFF);
         buffer[1] = (code & 0xFF);
         sendFrame(socket, WSop_close, &buffer[0], 2);
    }
    websocketremoveclient(socket);
}



///////////////////////
// init some data
void websocketinit(void)
{
	int i;
	for (i = 0;i<NBCLIENT;i++) 
	{
		webserverclients[i].socket = -1;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////
// decode and build the accept answer to open the websocket
uint32_t decodeHttpMessage (char * inputMessage, char * outputMessage)
{
	const char str1[98] = "HTTP/1.1 101 Switching Protocols\r\nUpgrade: websocket\r\nConnection: Upgrade\r\nSec-WebSocket-Accept: ";
	const char s[3] = "\r\n";
//	const char str2[5] = "\r\n\r\n";
	char *tokens[12];
	uint32_t index = 1;
//remove	uint32_t i;
	char key [24+36+1]; //24 bytes
	uint32_t outputLength;
	char encodedSha1 [41];
	uint32_t encodedLength;
//	printf("ws decode entry outputMessage: %x\n",outputMessage);
	//Split the message into substrings to identify it
	tokens[0] = strtok(inputMessage, s);
	while( (tokens[index-1] != NULL)&& (index < 12) )
	{
		tokens[index] = strtok(NULL, s);
		index ++;
	}
		//It's a websocket request
	for (index = 1; index < 12; index++)
	{
		if (strncmp(tokens[index], "Sec-WebSocket-Key: ", 19) == 0)
		{
			//assuming key of fixed length (that's how it is supposed to be)
			strncpy(key, tokens[index] + 19, 24);
			key[24] = 0;
			break;
		}
	}
	//compute the accept key
//	printf("ws decode entry3 outputMessage: %x\n",outputMessage);
	websocketacceptKey(key,encodedSha1);
	//Fill Output Buffer
	encodedLength = strlen(encodedSha1);
	outputLength = encodedLength + strlen(str1) + 2*strlen(s);
//	printf("ws decode entry4 outputMessage: %x\n",outputMessage);
	
	strcpy(outputMessage,str1);
	strcat(outputMessage,encodedSha1);
	strcat(outputMessage,s);
	strcat(outputMessage,s);
	//Add extra /n/r at the end
//	printf("ws decode HTTP: %x \"%s\"\n",outputMessage,outputMessage);
	return outputLength;
}
/////////////////////////////////////////////////////////////////////
// a socket with a websocket request. Note it and answer to the client
bool websocketnewclient(int socket)
{
	int i ;
//	printf("ws newclient:%d\n",socket);
	for (i = 0;i<NBCLIENT;i++) if (webserverclients[i].socket == socket) return true;
	else
	for (i = 0;i<NBCLIENT;i++) if (webserverclients[i].socket == -1) 
	{
		webserverclients[i].socket = socket;
		return true;
	}	
	return false; // no more room
}
/////////////////////////////////////////////////////////////////////
// remove the client in the list of clients
void websocketremoveclient(int socket)
{
	int i ;
//	printf("ws removeclient:%d\n",socket);
	for (i = 0;i<NBCLIENT;i++) 
		if (webserverclients[i].socket == socket) 
		{
			webserverclients[i].socket = -1;
//			printf("ws removeclient:%d removed\n",socket);
			close(socket);
			return;
		}
}
////////////////////////
// is socket a websocket?
bool iswebsocket( int socket)
{
	int i ;
	for (i = 0;i<NBCLIENT;i++) 
		if ((webserverclients[i].socket!= -1)&&(webserverclients[i].socket == socket)) return true;
	return false;
}
///////////////////////////
// send a message to client
bool sendFrame(int socket, wsopcode_t opcode, uint8_t * payload , size_t length )
{
//remove    uint8_t maskKey[4] = { 0x00, 0x00, 0x00, 0x00 };
    uint8_t buffer[WEBSOCKETS_MAX_HEADER_SIZE] = { 0 };
    uint8_t headerSize;
    uint8_t * headerPtr;
    uint8_t * payloadPtr = payload;
//remove    bool useInternBuffer = false;
//remove    bool ret = true;

    // calculate header Size
//	printf("websocket len: %d  payload: %s\n",length,payload);
    if(length < 126) {
        headerSize = 2;
    } else if(length < 0xFFFF) {
        headerSize = 4;
    } else {
        headerSize = 10;
    }
    	headerPtr = &buffer[0];
    // create header
    // byte 0
    *headerPtr = 0x00;
    *headerPtr |= 1<<7;    ///< set Fin
    *headerPtr |= opcode;        ///< set opcode
    headerPtr++;
    // byte 1
    *headerPtr = 0x00;
    if(length < 126) {
        *headerPtr |= length;
        headerPtr++;
    } else if(length < 0xFFFF) {
        *headerPtr |= 126;
        headerPtr++;
        *headerPtr = ((length >> 8) & 0xFF);
        headerPtr++;
        *headerPtr = (length & 0xFF);
        headerPtr++;
    } else {
        // Normally we never get here (to less memory)
        *headerPtr |= 127;
        headerPtr++;
        *headerPtr = 0x00;
        headerPtr++;
        *headerPtr = 0x00;
        headerPtr++;
        *headerPtr = 0x00;
        headerPtr++;
        *headerPtr = 0x00;
        headerPtr++;
        *headerPtr = ((length >> 24) & 0xFF);
        headerPtr++;
        *headerPtr = ((length >> 16) & 0xFF);
        headerPtr++;
        *headerPtr = ((length >> 8) & 0xFF);
        headerPtr++;
        *headerPtr = (length & 0xFF);
        headerPtr++;
    }

    // send header
    write(socket,buffer, headerSize) ;

    if(payloadPtr && length > 0) {
    // send payload
        write(socket,payloadPtr, length) ;
    }
//	printf("websocket len: %d  payloadPtr: %s\n",length,payloadPtr);
    return true;
}

/////////////////////////////////////////////
//read a txt data. close the socket if errno
void websocketparsedata(int socket, char* buf, int len)
{
	int recbytes = len;
	wsMessageHeader_t header;
	uint8_t * payload = (uint8_t *)buf;
	uint8_t headerLen = 2;
	if (!iswebsocket(socket)) return;
//	printf("ws parsedata entry1  recbytes:%d\n",recbytes);
	while(headerLen > recbytes) recbytes += read(socket , buf+recbytes, MAXDATA-recbytes);
//	printf("ws parsedata entry11  recbytes:%d\n",recbytes);
	header.fin = ((*payload >> 7) & 0x01);
	header.opCode = (wsopcode_t) (*payload & 0x0F);
	payload++; // second bytes
    header.mask = ((*payload >> 7) & 0x01);
    header.payloadLen = (wsopcode_t) (*payload & 0x7F);
    payload++;	
	
	if(header.payloadLen == 126) {
		headerLen += 2;
		while(headerLen > recbytes) recbytes += read(socket , buf+recbytes, MAXDATA-recbytes);
//	printf("ws parsedata entry2 recbytes:%d\n",recbytes);
        header.payloadLen = payload[0] << 8 | payload[1];
        payload += 2;
    } else if(header.payloadLen == 127) {
		headerLen += 8;
		while(headerLen > recbytes) recbytes += read(socket , buf+recbytes, MAXDATA-recbytes);		
// 	printf("ws parsedata entry3 recbytes:%d\n",recbytes);
       if(payload[0] != 0 || payload[1] != 0 || payload[2] != 0 || payload[3] != 0) {
            // really to big!
            header.payloadLen = 0xFFFFFFFF;
        } else {
            header.payloadLen = payload[4] << 24 | payload[5] << 16 | payload[6] << 8 | payload[7];
        }
        payload += 8;
    }		
	if(header.payloadLen > MAXDATA-WEBSOCKETS_MAX_HEADER_SIZE) {	// we must be in one buf max for payload
	// disconnect
	return;
	}
	
    if(header.mask) {
	    headerLen += 4;	
		while(headerLen > recbytes) recbytes += read(socket , buf+recbytes, MAXDATA-recbytes);
//	printf("ws parsedata entry4 recbytes:%d\n",recbytes);
		header.maskKey = payload;
        payload += 4;
    }	
	 headerLen += header.payloadLen;	
	while(headerLen > recbytes) recbytes += read(socket , buf+recbytes, MAXDATA-recbytes);
//	printf("ws parsedata entry5 recbytes:%d\n",recbytes);
//
	if(header.payloadLen > 0) {		
		if(header.mask) {
			size_t i ;
            //decode XOR
            for(i = 0; i < header.payloadLen; i++) {
               payload[i] = (payload[i] ^ header.maskKey[i % 4]);
            }
        }
    }
	payload[header.payloadLen] = 0x00;	   
	
/*	
	if (header.opCode == WSop_text)
		printf("ws parsedata data  socket:%d, opcode: %d,  payload:%s   len:%d\n",socket,header.opCode,payload,header.payloadLen);
*/
// ok payload is unmasked now.	
        switch(header.opCode) {
            case WSop_text:
                // no break here!
            case WSop_binary:
			websockethandle(socket, header.opCode, payload, header.payloadLen);
                break;
            case WSop_ping:
                // send pong back
                sendFrame(socket, WSop_pong, payload, header.payloadLen);
                break;
            case WSop_pong:
                break;
            case WSop_close: 
				websocketremoveclient(socket);
                break;
            case WSop_continuation:
                wsclientDisconnect(socket, 1003,NULL,0);
                break;
            default:
                wsclientDisconnect(socket, 1002,NULL,0);
                break;
        }
}	
	
//write a txt data
void websocketwrite(int socket, char* buf, int len)
{
	//bool sendFrame(int socket, wsopcode_t opcode, uint8_t * payload , size_t length )
	sendFrame(socket, WSop_text, (uint8_t *)buf , len );
}	
//broadcast a txt data to all clients
void websocketbroadcast(char* buf, int len)
{
	int i ;
	ESP_LOGD(TAG,"websocketbroadcast: %s",buf);
	for (i = 0;i<NBCLIENT;i++)	
		if (iswebsocket( webserverclients[i].socket))
		{
//			printf("ws broadcast to %d, freeheap:%d, msg:\"%s\"\n",webserverclients[i].socket,xPortGetFreeHeapSize( ),buf);
			websocketwrite( webserverclients[i].socket,  buf, len);
		}
}	
//broadcast a txt data to all clients but the sender
void websocketlimitedbroadcast(int socket,char* buf, int len)
{
	int i ;
	ESP_LOGD(TAG,"websocketlimitedbroadcast: %s",buf);
	for (i = 0;i<NBCLIENT;i++)	
		if (iswebsocket( webserverclients[i].socket))
		{
//			printf("ws broadcast to %d omit %d,freeheap:%d,  msg:\"%s\"\n",webserverclients[i].socket,socket,xPortGetFreeHeapSize( ),buf);
			if (webserverclients[i].socket != socket) websocketwrite( webserverclients[i].socket,  buf, len);
		}
}	


void websocketAccept(int wsocket,char* bufin,int buflen)
{
int32_t recbytes = 0;
char *buf = NULL;
	struct timeval timeout;      
    timeout.tv_sec = 1; 
    timeout.tv_usec = 0;	
	buf = (char *)inwmalloc(MAXDATA);	
	bufin[buflen] = 0;
//printf("ws write accept request entry soc: %d\n",wsocket);
    if (buf == NULL)
	{
		vTaskDelay(100); // wait a while and retry
		buf = (char *)inwmalloc(MAXDATA);	
	}
	if (buf != NULL)
	{
/*		if (setsockopt (wsocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
				printf(strwSOCKET,"setsockopt",errno);*/
		if ((!iswebsocket(wsocket ))&&(websocketnewclient(wsocket))) 
		{
			recbytes = decodeHttpMessage (bufin, buf);
			buf[recbytes+1] = 0;
//printf("ws write accept request:\n \"%s\" len:%d  socket: %d\n",buf,recbytes,wsocket);
			write(wsocket, buf, strlen(buf));  // reply to accept	
		}
		inwfree(buf,"websAccept");
	} 
//else printf("ws write accept request fails\n");
		
}

int websocketRead(int conn)
{
	char *buf = NULL;
	buf = (char *)inwmalloc(MAXDATA);
	int32_t recbytes = 0;
    if (buf == NULL)
	{
		vTaskDelay(100); // wait a while and retry
		buf = (char *)inwmalloc(MAXDATA);	
	}	
	if (buf != NULL)
	{
		recbytes = read(conn , buf, MAXDATA);
		if (recbytes < 0) {
			if ((errno != EAGAIN )&&(errno != 0 ))
			{
				inwfree(buf,"websRead");
				if (errno != ECONNRESET )
				{
					printf (strwSOCKET,"read", errno);
					wsclientDisconnect(conn, 500,NULL,0);		
				} // else websocketremoveclient(conn);
				return recbytes;
			} //else printf("ws try again\n");
		}
		if (recbytes > 0)
		{
			buf = realloc(buf,recbytes+1);
			websocketparsedata(conn, buf, recbytes);
		}
		inwfree(buf,"websRead");	
	}
	return recbytes;
}


