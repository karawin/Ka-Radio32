/*
 * Copyright 2016 karawin (http://www.karawin.fr)
*/
#define TAG "Webclient"
#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE

#include "webclient.h"
#include "webserver.h"
#include <string.h>
#include "lwip/sockets.h"
#include "lwip/api.h"
#include "lwip/netdb.h"
#include "esp_wifi.h"
#include "freertos/semphr.h"

/* wolfSSL */
#include "wolfssl/wolfcrypt/settings.h"
#include "user_settings.h"
#include "wolfssl/ssl.h"
#include "wolfssl/certs_test.h"


#include "vs1053.h"
#include "eeprom.h"
#include "interface.h"
#include "gpio.h"
#include "audio_player.h"
#include "spiram_fifo.h"
#include "app_main.h"

extern player_t* player_config;
#define min(a, b) (((a) < (b)) ? (a) : (b))
//2000 1440 1460 1436
//#define RECEIVE 1440 2144
#define RECEIVE 1440
enum clientStatus cstatus;
//static uint32_t metacount = 0;
//static uint16_t metasize = 0;

extern bool ledStatus;

xSemaphoreHandle sConnect, sConnected, sDisconnect, sHeader;

static uint8_t once = 0;
static uint8_t playing = 0;
static bool https = false;

static const char* icyHeaders[] = { "icy-name:", "icy-notice1:", "icy-notice2:",  "icy-url:", "icy-genre:", "icy-br:","icy-description:","ice-audio-info:", "icy-metaint:" };
contentType_t contentType;

static const char notfound[]={"Not Found"};
static const char nodata[]={"No Data"};
static char parEmpty[] = {" "};
static char CLIPLAY[]  = {"##CLI.PLAYING#%c%c"};
static char CLISTOP[]  = {"##CLI.STOPPED# from %s\n"};

#define strcMALLOC  	"Client: incmalloc fails for %d"
#define strcMALLOC1  	"%s kmalloc fails"

#define URLMAX	256
#define PATHMAX	512

static struct icyHeader header = {{{NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, NULL}}};

static char metaint[10];
static char clientURL[URLMAX]= {0,0};
static char clientPath[PATHMAX] = {0,0};
static uint16_t clientPort = 80;

/* declare wolfSSL objects */
    WOLFSSL_CTX *ctx ;
    WOLFSSL *ssl ;

static const struct hostent *serverInfo = NULL;
static char* pseudoUtf8(char* str,int *len);

void *incmalloc(size_t n)
{
	void* ret;
//printf ("Client kmalloc of %d %d,  Heap size: %d\n",n,((n / 32) + 1) * 32,xPortGetFreeHeapSize( ));
	ret = kmalloc(n);
	if (ret == NULL) ESP_LOGV(TAG,strcMALLOC,n);
//	if (n <4) printf("Client: incmalloc size:%d\n",n);
	ESP_LOGV(TAG,"Client kmalloc after of %d bytes ret:%x  Heap size: %d",n,(int)ret,xPortGetFreeHeapSize( ));
	return ret;
}
void incfree(void *p,const char* from)
{
	if (p != NULL) free(p);
//	else printf ("Client incfree from %s NULL\n",from);
	ESP_LOGV(TAG,"Client incfree of %x, from %s           Heap size: %d",(int)p,from,xPortGetFreeHeapSize( ));
}


// is it a https one?
void test_https()
{
	if (strstr(clientURL,"https://"))
	https = true;
	else https = false;
}

//compute the size of the audio buffer for https or http
void ramSinit()
{
	test_https();
	if (https && !bigSram())
	{
		if (get_audio_output_mode() == VS1053)
		{
			if (getSPIRAMSIZE() == HTTPSVSRAM*1024) return; // no need
			setSPIRAMSIZE(HTTPSVSRAM*1024);
		}
		else
		{
			if (getSPIRAMSIZE() == HTTPSRAM*1024) return; // no need
			setSPIRAMSIZE(HTTPSRAM*1024);
		}	
	}
	else //ramInit();
	//compute the size of the audio buffer for http
	{
		if (bigSram())
		{
			if (getSPIRAMSIZE() == BIGRAM*1024) return; // no need
			setSPIRAMSIZE(BIGRAM*1024);		// more free heap
		}
		else
		{
			if (get_audio_output_mode() == VS1053)
			{
				if (getSPIRAMSIZE() == SMALLRAM*1024) return; // no need
				setSPIRAMSIZE(SMALLRAM*1024);		// more free heap
			}		
			else
			{
				if (getSPIRAMSIZE() == DEFAULTRAM*1024) return; // no need
				setSPIRAMSIZE(DEFAULTRAM*1024);		// more free heap	
			}
		}
	}
	spiRamFifoDestroy();
	ESP_LOGI(TAG, "Set Song buffer to %dk",getSPIRAMSIZE()/1024);
	if (!spiRamFifoInit())
	{
		vTaskDelay(100);
		ESP_LOGE(TAG, "SPIRAM fail for %dK",getSPIRAMSIZE()/1024);
		setSPIRAMSIZE(getSPIRAMSIZE() - 10240);
		ESP_LOGI(TAG, "Set Song buffer to %dk",getSPIRAMSIZE()/1024);
		if (!spiRamFifoInit())
		{
			ESP_LOGE(TAG, "SPIRAM fail for %dK",getSPIRAMSIZE()/1024);
			ESP_LOGE(TAG,"%sHEAPd0: %d #\n","##SYS.",xPortGetFreeHeapSize( ));	
			ESP_LOGE(TAG, "REBOOT");
			esp_restart();
		}
	}
}


bool getState()
{
	 return playing;
}

void clientPrintState()
{
	if (playing)
		kprintf(CLIPLAY,0x0d,0x0a);
	else
		kprintf(CLISTOP,"State");
}
void clientInit() {
	vSemaphoreCreateBinary(sHeader);
	vSemaphoreCreateBinary(sConnect);
	vSemaphoreCreateBinary(sConnected);
	vSemaphoreCreateBinary(sDisconnect);
	xSemaphoreTake(sConnect, portMAX_DELAY);
	xSemaphoreTake(sConnected, portMAX_DELAY);
	xSemaphoreTake(sDisconnect, portMAX_DELAY);
}

uint8_t clientIsConnected() {
	if(xSemaphoreTake(sConnected, 0)) {
		xSemaphoreGive(sConnected);
		return 0;
	}
	return 1;
}

// for debug only

void dump(uint8_t* from, uint32_t len )
{
	uint32_t i ;
	uint8_t* addr ;
	addr =  from;
	for (i=0;i<len;i+=16){
		printf("\n%x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x    \t\
		%c %c %c %c %c %c %c %c %c %c %c %c %c %c %c %c",(unsigned int)addr,(unsigned int)addr[0],(unsigned int)addr[1],(unsigned int)addr[2],(unsigned int)addr[3],(unsigned int)addr[4],(unsigned int)addr[5],(unsigned int)addr[6],(unsigned int)addr[7],(unsigned int)addr[8],(unsigned int)addr[9],(unsigned int)addr[10],(unsigned int)addr[11],(unsigned int)addr[12],(unsigned int)addr[13],(unsigned int)addr[14],(unsigned int)addr[15],addr[0],addr[1],addr[2],addr[3],addr[4],addr[5],addr[6],addr[7],addr[8],addr[9],addr[10],addr[11],addr[12],addr[13],addr[14],addr[15]);
		addr+=16;
	}
	printf("\n");
}

struct icyHeader* clientGetHeader()
{
	return &header;
}


//------------------------------------------------------------------------------//
void Unicode_decoding(char *string){ //
union { //
	struct { //
		unsigned char t_LOW; //
		unsigned char t_HIG; //
		}; //
	uint16_t T_t; //
}T_t; //
uint16_t ss = 0;
uint16_t sss = 0;
size_t len = 0;
uint8_t l = 0;
char * string_rec ;

if (strstr(string,"&#") != NULL)
{
string_rec  = kcalloc(strlen(string)+1, sizeof(uint8_t));
  while (strstr(string,"&#") != NULL){
    len = strcspn(string, "&#");
    if(len == 0){l=1;}
    else{    
        for(uint16_t s=sss;s<len;s++){
           string_rec[ss++] = string[s];
           sss++;
        } 
    }
    string[len++] = ' ';
    string[len++] = ' ';

    uint8_t p_s[4];
    for(uint8_t a=0;a<4;a++){
       p_s[a] = string[len++];
    }
    
    T_t.T_t = atol((const char *)p_s);    
    T_t.t_HIG = T_t.t_HIG << 2;
    T_t.t_HIG = (T_t.t_HIG & 0x3F) ^ (  T_t.t_LOW & 0xC0 );
    T_t.t_LOW = (T_t.t_LOW & 0x3F) ^ 0x80;
    T_t.t_HIG = (T_t.t_HIG & 0x1F) ^ 0xC0;
    
    string_rec[ss++] = T_t.t_HIG;
    string_rec[ss++] = T_t.t_LOW;
    sss = sss + 7;
//    if(len>=  sizeof(string)){break;}
    if(len>=  strlen(string))
	{break;}
  }

//  if(len < sizeof(string)){
  if(len < strlen(string)){
    l = 1;
  }

  if(l){
//    len =  sizeof(string);
    len =  strlen(string);
    for(uint16_t s=sss;s<len;s++){
        string_rec[ss++] = string[s];
        sss++;
    }
  }
  strcpy(string,string_rec);
  free(string_rec);
}
}
//------------------------------------------------------------------------------


// extract the url from a playlist m3u pls etc....
bool clientParsePlaylist(char* s)
{
  char* str;
  char* ns;
  char path[PATHMAX] = "/";
  char url[URLMAX] = "";
  char port[6] = "80";
//  int remove = 0;
  int i = 0; int j = 0;

  ESP_LOGV(TAG,"clientParsePlaylist\n%s",s);
// for extm3u skip line with #EXTINF
  str = strstr(s,"#EXTINF");
  if (str != NULL) //skip to next line
  {
	ns = str;
    while ((strlen(ns) > 0) && (ns[0]!=0x0A)) ns++;
//	ESP_LOGV(TAG,"EXTM3U: %s",ns);
	if (strlen(ns)>0) s= ns+1;// skip \n
  }
// skip if icy lines
  if (strstr(s,"icy-") != NULL)
  {
	clientSetPath((char*)"/;");
	return true;
  }	
  
  str = strstr(s,"<location>");  //for xspf
  if (str != NULL) s= str+10;
  str = strstr(s,"<REF href = ");  //for asx
  if (str != NULL) s=str+11;
  
	
  str = strstr(s,"http://");
  if (str ==NULL) str = strstr(s,"HTTP://");
  if (str != NULL)   {s= str+7; j = 7; strcpy (url,"http://"); }
  else
  {
	str = strstr(s,"https://");
	if (str == NULL) str = strstr(s,"HTTPS://");
	if (str != NULL) {s= str+8; j = 8; strcpy (url,"https://");strcpy(port,"443");}
	else {
		j = 7;
		strcpy (url,"http://");
	} // no http found
  } 
  
  if (str != NULL)
  {
	str = s;
	ESP_LOGD(TAG,"parse str %s",str);
	while ((str[i] != '/')&&(str[i] != ':')&&(str[i] != 0x0a)&&(str[i] != 0x0d)&&(j<77)) {url[j] = str[i]; i++ ;j++;}
	url[j] = 0;
	ESP_LOGD(TAG,"parse str url %s",url);
	j = 0;
	if (str[i] == ':')  //port
	{
		i++;
		while ((str[i] != '/')&&(str[i] != 0x0a)&&(str[i] != 0x0d)&&(j<5)) {port[j] = str[i]; i++ ;j++;}
		port[j] = 0;
	}
//	ESP_LOGV(TAG,"parse str port %s",port);
	j = 0;
	if (str[i] == '/')  //path
	{
		if ((str[i] != 0x0a)&&(str[i] != 0x0d)&&(str[i] != 0)&&(str[i] != '"')&&(str[i] != '<')&&(j<PATHMAX))
		{
			while ((str[i] != 0x0a)&&(str[i] != 0x0d)&&(str[i] != 0)&&(str[i] != '"')&&(str[i] != '<')&&(j<PATHMAX)) {path[j] = str[i]; i++; j++;}
			path[j] = 0;
		}
	}
//	ESP_LOGV(TAG,"parse str path %s",path);

	if (strncmp(url,"localhost",9)!=0) clientSetURL(url);
	clientSetPath(path);
	clientSetPort(atoi(port));
	ESP_LOGV(TAG,"clientParsePlaylist: url: %s, path: %s, port: %s",url,path,port);
	return true;
  }
  else
  {
   cstatus = C_DATA;
   return false;
  }
}

//---------------------------------------
// add escape char to special char of the string  json constructor
static char* stringify(char* str,int len)
{
#define MORE	20
//		if ((strchr(str,'"') == NULL)&&(strchr(str,'/') == NULL)) return str;
        if (len == 0) return str;
		char* new = incmalloc(len+MORE);
		int nlen = len+MORE;
		if (new != NULL)
		{
			ESP_LOGV(TAG,"stringify: enter: len:%d  \"%s\"",len,str);
			int i=0 ,j =0;
			for (i = 0;i< len+10;i++) new[i] = 0;
			for (i=0;i< len;i++)
			{
				if (str[i] == '"') {
					new[j++] = '\\';
					new[j++] =(str)[i] ;
				} else
				if (str[i] == '/') {
					new[j++] = '\\';
					new[j++] =(str)[i] ;
				}
				else
				if (str[i] == '\\') {
					new[j++] = '\\';
					new[j++] =(str)[i] ;
				}
				else 
				if (str[i] == 0x09) {  // TAB
					new[j++] = '\\';
					new[j++] ='t' ;
				}
				else
 				new[j++] =(str)[i] ;

				if ( j+MORE> nlen)
				{
					nlen +=MORE;
					new = realloc(new,nlen); // some room
				}
			}
			incfree(str,"str");

			new = realloc(new,j+1); // adjust
			ESP_LOGV(TAG,"stringify: exit: len:%d  \"%s\"",j,new);
			return new;
		} else
		{
			ESP_LOGV(TAG,strcMALLOC1,"stringify");
		}
		return str;
}

bool clientPrintMeta()
{
	if (header.members.mArr[METADATA] != NULL)
		kprintf("##CLI.META#: %s\n",header.members.mArr[METADATA]);
	else
		kprintf("##CLI.META#:%c", 0x0D);

	return true;
}

char* getMeta()
{
	return (header.members.mArr[METADATA] == NULL)?parEmpty:header.members.mArr[METADATA];
}

static void removePartOfString(char* origine, const char* remove)
{
	if (strlen(origine) == 0) return;
	char* copy = incmalloc(strlen(origine));
	char* t_end;
	if (copy != NULL)
	{
		while ( (t_end = strstr(origine,remove))!= NULL)
		{
			*t_end = 0;
			strcpy(copy,origine);
			strcat(copy,t_end+(strlen(remove)));
			strcpy(origine,copy);
		}
		incfree(copy,"removePt");
	}
}

// A metadata found. Extract the Stream title
static void clientSaveMetadata(char* s,int len)
{
	char* t_end = NULL;
	char* t ;
	int ilen ;
	bool found = false;
	if ((len > 256) ||(s == NULL) || (len == 0)) // if not valid
	{
		if (header.members.mArr[METADATA] != NULL)
		incfree(header.members.mArr[METADATA],"metad");  // clear the old one
		header.members.mArr[METADATA] = NULL;  // and exit
		ESP_LOGV(TAG,"clientSaveMetadata:  len:%d",len);
		return;
	}
	ilen = len;
	//remove all but title
	t = s;
	ilen = strlen(t);
	ESP_LOGV(TAG,"clientSaveMetadata:  len:%d ilen:%d  char:%s",len,ilen,s);
	t_end = strstr(t,"song_spot=");
	if (t_end != NULL)
	{
		*t_end = 0;
		found = true;
		removePartOfString(t, "text=");
		removePartOfString(t, "\"");
	}
	else
	{
		t_end = strstr(t,";StreamUrl='");
		if (t_end != NULL)
		{
			*t_end = 0;found = true;
		}
	}
	t = strstr(t,"StreamTitle='");
	if (t!= NULL) 
	{
		t += 13;found = true;
		len -=13;
	} 
	else { 
		t = s;
	}
	ilen = strlen(t) ;
	if (ilen > len)
	{
		ESP_LOGD(TAG,"clientSaveMetadata:  bug len:%d ilen:%d  char:%s",len,ilen,s);
		ilen = len;
		t[len+1]=0;
	}
	if ((t_end != NULL)&&(ilen >=3)) t_end -= 3;
	else {
		if (t_end != NULL) t_end -=1;
		else
		if (ilen >=2) {t_end = t+ilen-2;found = true;}
		else t_end = t+ilen;
	}
	if (found)
	{
		t_end = strstr(t_end,"'");
		if (t_end !=NULL)
		*t_end = 0;
		if (t!=NULL)
		{
			t_end = strstr(t,"||");
			if (t_end !=NULL)
			*t_end = 0;
		}
	}
	else
	{
		if (ilen >=2) ilen-=2;
	}
	// the expurged str
	ESP_LOGD(TAG,"clientSaveMetadata0:  len:%d   char:%s",strlen(t),t);
	ilen = strlen(t) ;
// see if meta is != of the old one
	char* tt;
	tt = incmalloc((ilen+5)*sizeof(char));
	if (tt != NULL)
	{
		strcpy(tt,t);
		tt = stringify(tt,ilen); // to compare we need to stringify
	}
	if  ((header.members.mArr[METADATA] == NULL)||
		((header.members.mArr[METADATA] != NULL)&&(t!= NULL)&&(strcmp(tt,header.members.mArr[METADATA]) != 0)))
	{
		if (header.members.mArr[METADATA] != NULL)
			incfree(header.members.mArr[METADATA],"metad"); //clear the old one
		header.members.mArr[METADATA] = (char*)incmalloc((ilen+3)*sizeof(char));
		if(header.members.mArr[METADATA] == NULL)
		{	ESP_LOGV(TAG,strcMALLOC1,"metad");
			return;
		}

		strcpy(header.members.mArr[METADATA], t);
//		dump((uint8_t*)(header.members.mArr[METADATA]),strlen(header.members.mArr[METADATA]));
		header.members.mArr[METADATA] = stringify(header.members.mArr[METADATA],len);
		Unicode_decoding(header.members.mArr[METADATA]);
		clientPrintMeta();
		while ((header.members.mArr[METADATA][strlen(header.members.mArr[METADATA])-1] == ' ')||
			(header.members.mArr[METADATA][strlen(header.members.mArr[METADATA])-1] == '\r')||
		(header.members.mArr[METADATA][strlen(header.members.mArr[METADATA])-1] == '\n')
		)
		{
			header.members.mArr[METADATA][strlen(header.members.mArr[METADATA])-1] = 0; // avoid blank at end
		}

// send station name if no metadata
		if (strlen(header.members.mArr[METADATA])!=0)
			t_end = header.members.mArr[METADATA];
		else
			t_end = (header.members.single.name ==NULL)?(char*)"":header.members.single.name;
//
		char* title = incmalloc(strlen(t_end)+15);
		if (title != NULL) // broadcast to all websockets
		{
			sprintf(title,"{\"meta\":\"%s\"}",t_end);
			int blen;
			title = pseudoUtf8(title,&blen);
			websocketbroadcast(title, blen);
			incfree(title,"title");
		} else ESP_LOGV(TAG,strcMALLOC1,"Title");
	}
	incfree(tt,"");
}

// websocket: next station
void wsStationNext()
{
	struct shoutcast_info* si =NULL;
	do {
		if (si != NULL) incfree(si,"wsstationN");
		setCurrentStation(getCurrentStation()+1);
		if (getCurrentStation() >= 255)
			setCurrentStation(0);
		si = getStation(getCurrentStation());
	}
	while (si == NULL || ((si != NULL)&&(strcmp(si->domain,"")==0)) || ((si != NULL)&&(strcmp( si->file,"")== 0)));

	playStationInt(getCurrentStation());
	incfree(si,"wsstation");
}
// websocket: previous station
void wsStationPrev()
{
	struct shoutcast_info* si = NULL;
	do {
		if (si != NULL) incfree(si,"wsstationP");
		if (getCurrentStation() >0)
		{
			setCurrentStation(getCurrentStation()-1);
			si = getStation(getCurrentStation());
		}
		else return;
	}
	while (si == NULL || ((si != NULL)&&(strcmp(si->domain,"")==0)) || ((si != NULL)&&(strcmp( si->file,"")== 0)));

	playStationInt	(getCurrentStation());
	incfree(si,"wsstation");
}

// websocket: broadcast volume to all client
void wsVol(char* vol)
{
	char answer[21];
	if (vol != NULL)
	{
		sprintf(answer,"{\"wsvol\":\"%s\"}",vol);
		websocketbroadcast(answer, strlen(answer));
	}
}
// websocket: broadcast monitor url
void wsMonitor()
{
	char *answer;
	uint16_t len;
	len = strlen(clientURL)+strlen(clientPath)+30;
	answer= kmalloc(len);
	if (answer)
	{
		memset(answer,0,len);
		if ((clientPath[0]!= 0))
		{
			sprintf(answer,"{\"monitor\":\"%s:%d%s\"}",clientURL,clientPort,clientPath);
			websocketbroadcast(answer, strlen(answer));
		}
		free(answer);
	}
}


// websocket cannot send other char than utf8
static char* pseudoUtf8(char* str, int* len) //,int len)
{
	#define MOREU	20
 //       if (len == 0) return str;
	*len = strlen(str);
	char* new = incmalloc(strlen(str)+MOREU);
	if (new != NULL)
	{
		ESP_LOGV(TAG,"pseudoUtf8: enter: \"%s\"",str);
		int i=0 ,j =0;
		for (i = 0;i< *len+10;i++) new[i] = 0;
		for (i=0;i< *len;i++)
		{
			if ((str[i] > 192) && (str[i+1] < 0x80)){ // 128 = 0x80
				new[j++] = 195; // 192 = 0xC0   195 = 0xC3
				new[j++] =(str)[i]-64 ; // 64 = 0x40
			} 
			else new[j++] =(str)[i] ;				
		}
		incfree(str,"str");
		new = realloc(new,j+1); // adjust
		*len = strlen(new);
		ESP_LOGV(TAG,"pseudoUtf8: exit: \"%s\"",new);
		return new;
	} else
	{
		ESP_LOGV(TAG,strcMALLOC1,"pseudoUtf8");
	}
	*len = strlen(str);
	return str;
}


//websocket: broadcast all icy and meta info to web client.
static void wsHeaders()
{
//remove	uint8_t header_num;
	char currentSt[6];
	sprintf(currentSt,"%d",getCurrentStation());
	char* not2;
	not2 = header.members.single.notice2;
	if (not2 ==NULL) not2=header.members.single.audioinfo;
	if ((header.members.single.notice2 != NULL)&&(strlen(header.members.single.notice2)==0)) not2=header.members.single.audioinfo;
	
	int json_length ;
	json_length =104+ //93
		strlen(currentSt)+
		((header.members.single.description ==NULL)?0:strlen(header.members.single.description)) +
		((header.members.single.name ==NULL)?0:strlen(header.members.single.name)) +
		((header.members.single.bitrate ==NULL)?0:strlen(header.members.single.bitrate)) +
		((header.members.single.url ==NULL)?0:strlen(header.members.single.url))+
		((header.members.single.notice1 ==NULL)?0:strlen(header.members.single.notice1))+
		((not2 ==NULL)?0:strlen(not2))+
		((header.members.single.genre ==NULL)?0:strlen(header.members.single.genre))+
		((header.members.single.metadata ==NULL)?0:strlen(header.members.single.metadata))
		;
	char* wsh = incmalloc(json_length+1);
	if (wsh == NULL) {ESP_LOGV(TAG,strcMALLOC1,"wsHeader");return;}
	sprintf(wsh,"{\"wsicy\":{\"curst\":\"%s\",\"descr\":\"%s\",\"meta\":\"%s\",\"name\":\"%s\",\"bitr\":\"%s\",\"url1\":\"%s\",\"not1\":\"%s\",\"not2\":\"%s\",\"genre\":\"%s\"}}",
			currentSt,
			(header.members.single.description ==NULL)?"":header.members.single.description,
			(header.members.single.metadata ==NULL)?"":header.members.single.metadata,
			(header.members.single.name ==NULL)?"":header.members.single.name,
			(header.members.single.bitrate ==NULL)?"":header.members.single.bitrate,
			(header.members.single.url ==NULL)?"":header.members.single.url,
			(header.members.single.notice1 ==NULL)?"":header.members.single.notice1,
			(not2 ==NULL)?"":not2 ,
			(header.members.single.genre ==NULL)?"":header.members.single.genre);
	ESP_LOGV(TAG,"WSH: len:%d  \"%s\"",strlen(wsh),wsh);
	int len;
	wsh = pseudoUtf8(wsh, &len);
	websocketbroadcast(wsh, len);
	incfree (wsh,"wsh");
}

//Clear all ICY and META infos
static void clearHeaders()
{
	uint8_t header_num;
	for(header_num=0; header_num<ICY_HEADER_COUNT; header_num++) {
		if(header_num != METAINT)
			if(header.members.mArr[header_num] != NULL) {
				incfree(header.members.mArr[header_num],"header" );
				header.members.mArr[header_num] = NULL;
			}
	}
	header.members.mArr[METAINT] = 0;
	wsHeaders();
}

bool clientPrintOneHeader(uint8_t header_num)
{
	if (header.members.mArr[header_num] != NULL)
	kprintf("##CLI.ICY%d#: %s\n",header_num,header.members.mArr[header_num]);
return true;
}

bool clientPrintHeaders()
{
	uint8_t header_num;
	for(header_num=0; header_num<ICY_HEADER_COUNT; header_num++) {
		if((header_num != METAINT) && (header_num != METADATA))
			if(header.members.mArr[header_num] != NULL) {
				kprintf("##CLI.ICY%d#: %s\n",header_num,header.members.mArr[header_num]);
			}
	}
	clientPrintMeta();
	return true;
}

bool clientSaveOneHeader(const char* t, uint16_t len, uint8_t header_num)
{
	char* tt;
	int i;
	if(header.members.mArr[header_num] != NULL)
		incfree(header.members.mArr[header_num],"headernum");
	tt = incmalloc((len+1)*sizeof(char));
	if(tt == NULL)
	{
		ESP_LOGV(TAG,strcMALLOC1,"clientSOneH");
		return false;
	}

	for(i = 0; i<len+1; i++) tt[i] = 0;
	strncpy(tt, t, len);
	header.members.mArr[header_num] = stringify(tt,len); //tt is freed here
	Unicode_decoding(header.members.mArr[header_num]);
	vTaskDelay(1);
	clientPrintOneHeader(header_num);
	ESP_LOGV(TAG,"Header after num:%d addr:0x%x  cont:\"%s\"",header_num,(int)header.members.mArr[header_num],header.members.mArr[header_num]);
	return true;
}


bool clientParseHeader(char* s)
{
	// icy-notice1 icy-notice2 icy-name icy-genre icy-url icy-br
	uint8_t header_num;
	char *t;
	bool ret = false;
	ESP_LOGV(TAG,"ParseHeader: %s",s);
	xSemaphoreTake(sHeader,portMAX_DELAY);
	if ((cstatus != C_HEADER1)&& (cstatus != C_PLAYLIST))// not ended. dont clear
	{
		clearHeaders();
	}

	t = strstr(s,"Content-Type:");
	if (t == NULL) t = strstr(s,"content-type:");
	if (t != NULL)
	{
		contentType = KMIME_UNKNOWN;
		if (strstr(t, "application/octet-stream")) contentType = KOCTET_STREAM;
		if (strstr(t, "audio/aac")) contentType = KAUDIO_AAC;
		if (strstr(t, "audio/mp4")) contentType = KAUDIO_MP4;
		if (strstr(t, "audio/x-m4a")) contentType = KAUDIO_MP4;
		if (strstr(t, "audio/mpeg")) contentType = KAUDIO_MPEG;
		if (strstr(t, "application/ogg")) contentType = KAUDIO_OGG;
		if (strstr(t, "audio/ogg")) contentType = KAUDIO_OGG;

		if(contentType == KMIME_UNKNOWN) {
			ESP_LOGD(TAG, "unknown contentType: %s", t);
			clientSaveOneHeader("unknown contentType",19,METANAME);
			wsHeaders(); // update all server
			vTaskDelay(10);
			clientDisconnect("unknown contentType");
			cstatus = C_HEADER;		
		}
		ESP_LOGD(TAG, "contentType: %d", contentType);
		player_config->media_stream->content_type = contentType;
	}

	for(header_num=0; header_num<ICY_HEADERS_COUNT; header_num++)
	{
		ESP_LOGV(TAG,"icy deb: %d",header_num);
		t = strstr(s, icyHeaders[header_num]);
		if( t != NULL )
		{
			t += strlen(icyHeaders[header_num]);
			char *t_end = strstr(t, "\r\n");
			if(t_end != NULL)
			{
				ESP_LOGV(TAG,"icy in: %d",header_num);
				uint16_t len = t_end - t;
				if(header_num != METAINT) // Text header field
				{
					ret = clientSaveOneHeader(t, len, header_num);
				}
				else // Numerical header field
				{
						int i;
						for(i = 0; i<len+1; i++) metaint[i] = 0;
						strncpy(metaint, t, len);
						header.members.single.metaint = atoi(metaint);
						ESP_LOGV(TAG,"len = %d,MetaInt= %s, Metaint= %d",len, metaint,header.members.single.metaint);
						ret = true;
						ESP_LOGV(TAG,"icy: %s, %d",icyHeaders[header_num],header.members.single.metaint);
				}
			}
		}
	}
	if (ret == true)
	{
		wsHeaders(); // update all server
	}
	xSemaphoreGive(sHeader);
	return ret;
}


void clientSetName(const char* name,uint16_t index)
{
	kprintf("##CLI.NAMESET#: %d %s\n",index,name);
}

// remove http(s)://
char* cleanURL()
{
	char* ret ;
	ret = strstr(clientURL,"http://");
	if (ret != 0) return (clientURL+7);
	ret = strstr(clientURL,"https://");
	if (ret != 0) return (clientURL+8);
	return clientURL;
}


void clientSetURL(char* url)
{
	clientURL[0] = 0;
	if (strstr(url,"http") == NULL) strcpy(clientURL,"http://");
	if (url[0] == 0xff) return; // wrong url
	if (strlen(url) > URLMAX)
		strncat(clientURL,url,URLMAX-9);
	else 
		strcat(clientURL, url);
	kprintf("##CLI.URLSET#: %s\n",clientURL);
}

void clientSetPath(char* path)
{
	if (path[0] == 0xff) return; // wrong path
	if (strlen(path) > PATHMAX)
		strncpy(clientPath,path,PATHMAX-1);
	else 
		strcpy(clientPath, path);
	kprintf("##CLI.PATHSET#: %s\n",clientPath);
}

void clientSetPort(uint16_t port)
{
	clientPort = port;
	kprintf("##CLI.PORTSET#: %d\n",port);
}


void clientConnect()
{
	cstatus = C_HEADER;
	once = 0;
	if((serverInfo = (struct hostent*)gethostbyname(cleanURL()))) {
		xSemaphoreGive(sConnect);
//		esp_wifi_set_ps (WIFI_PS_MIN_MODEM);
	} else {
		clientDisconnect("clientConnect");
		clientSaveOneHeader("No ip found",11,METANAME);
		wsHeaders();
		vTaskDelay(1);
	}
}
void clientConnectOnce()
{
	cstatus = C_HEADER;
	if((serverInfo = (struct hostent*)gethostbyname(cleanURL()))) {
		xSemaphoreGive(sConnect);
//		esp_wifi_set_ps (WIFI_PS_MIN_MODEM);
	} else {
		clientDisconnect("clientConnectOnce");
	}
	once = 1; // play one time
}
void clientSilentConnect()
{
	cstatus = C_HEADER;
	once = 0;
	if(serverInfo != NULL) {
		xSemaphoreGive(sConnect);
//		esp_wifi_set_ps (WIFI_PS_MIN_MODEM);
	} else {
		clientSilentDisconnect();
	}
}
void clientSilentDisconnect()
{
	xSemaphoreGive(sDisconnect);
	if (get_player_status()!=STOPPED)
		audio_player_stop();
	for (int i = 0;i<100;i++)
	{
		if(!clientIsConnected())break;
		vTaskDelay(1);
	}
//	esp_wifi_set_ps(WIFI_PS_MAX_MODEM);

}

void clientDisconnect(const char* from)
{
	extern bool ledPolarity;
	kprintf(CLISTOP,from);
	xSemaphoreGive(sDisconnect);
	if (get_player_status()!=STOPPED)
		audio_player_stop();
	for (int i = 0;i<100;i++)
	{
		if(!clientIsConnected())break;
		vTaskDelay(1);
	}
	if ((from[0]!='C') || (from[1]!='_'))
		if (!ledStatus){ 
			if (getLedGpio() != GPIO_NONE) gpio_set_level(getLedGpio(), ledPolarity ? 1 : 0);	
		}		
//	esp_wifi_set_ps(WIFI_PS_MAX_MODEM);
	vTaskDelay(1);
	// save the volume if needed on stop state
	if (g_device->vol != getIvol())
	{ 			
		g_device->vol = getIvol();
		saveDeviceSettingsVolume(g_device);
	}
}

void clientReceiveCallback(int sockfd, char *pdata, int len)
{
	extern bool ledPolarity;
	static int metad ;
	static int rest ;
	static uint16_t dloop;
	static IRAM_ATTR  uint32_t chunked;
	static IRAM_ATTR  uint32_t cchunk;
	static char* metadata = NULL;
	uint16_t l =0;
	uint32_t lc;
	char *inpdata;
	char* inpchr;
	uint32_t clen;
	int bread;
	char* t1;
	char* t2;
	bool  icyfound;

//	if (cstatus != C_DATA) {printf("cstatus= %d\n",cstatus);  printf("Len=%d, Byte_list = %s\n",len,pdata);}
	if (cstatus != C_DATA)
	{
		t1 = strstr(pdata, "404");
		if (t1 != NULL)
		{
			t1 = strstr(pdata, notfound);
			if (t1 == NULL) t1 = strstr(pdata,"not be found");
		}
		if (t1 != NULL) { //
			kprintf(CLIPLAY,0x0d,0x0a);
			clientSaveOneHeader(notfound, 9,METANAME);
			wsHeaders();
			vTaskDelay(1);
			cstatus = C_HEADER;
			clientDisconnect("C_LIST"); 
			return;
		}
	}
	switch (cstatus)
	{
	case C_PLAYLIST:
         if (!clientParsePlaylist(pdata)) //need more
		  cstatus = C_PLAYLIST1;
		else {clientDisconnect("C_PLIST");  }
    break;
	case C_PLAYLIST1:
       clientDisconnect("C_PLIST1");
        clientParsePlaylist(pdata) ;//more?
		cstatus = C_PLAYLIST;
	break;
	case C_HEADER0:
	case C_HEADER:
		clearHeaders();
		metad = -1;
		t1 = strstr(pdata, "302 ");
		if (t1 ==NULL) t1 = strstr(pdata, "301 ");
		if (t1 != NULL) 
		{ // moved to a new address
			if( strcmp(t1,"Found")||strcmp(t1,"Temporarily")||strcmp(t1,"Moved"))
			{
				ESP_LOGV(TAG,"Header Len=%d,\n %s",len,pdata);
				ESP_LOGI(TAG,"Header: Moved");
				clientDisconnect("C_HDER");
				clientParsePlaylist(pdata);
				cstatus = C_PLAYLIST;

			}
			break;
		}
		//no break here
	case C_HEADER1:  // not ended
		{
			int i = 0;
			cstatus = C_HEADER1;
			do {
				t1 = strstr(pdata, "\r\n\r\n"); // END OF HEADER
				ESP_LOGV(TAG,"Header1 len: %d,  Header: %s",len,pdata);
				if ((t1 != NULL) && (t1 <= pdata+len-4))
				{
						t2 = strstr(pdata, "Internal Server Error");
						if (t2 != NULL)
						{
							ESP_LOGV(TAG,"Internal Server Error");
							clientDisconnect("Internal Server Error");
							cstatus = C_HEADER;

						}
						icyfound = 	clientParseHeader(pdata);
						if(header.members.single.metaint > 0)
							metad = header.members.single.metaint;
						ESP_LOGD(TAG,"t1: 0x%x, cstatus: %d, icyfound: %d  metad:%d Metaint:%d\n", (int) t1,cstatus, icyfound,metad,  (header.members.single.metaint));
						cstatus = C_DATA;	// a stream found
						setVolumei(1);
/////////////////////////////////////////////////////////////////////////////////////////////////
						player_config->media_stream->eof = false;
						audio_player_start();
/////////////////////////////////////////////////////////////////////////////////////////////////


						t2 = strstr(pdata, "Transfer-Encoding: chunked"); // chunked stream?
						chunked = 0;
						t1+= 4;
						if ( t2 != NULL)
						{
							while (len -(t1-pdata)<8) {
								vTaskDelay(1);
								int ilen;
								if (https)
								{
									ilen = wolfSSL_read(ssl, pdata+len, RECEIVE+8-len);
									if (ilen >0) len += ilen;
								}
								else
								{
									ilen = recv(sockfd, pdata+len, RECEIVE+8-len, 0); 
									if (ilen >0) len += ilen; 
								}
								if (ilen <0) {clientDisconnect("chunk2");break;}							
							}
							chunked = (uint32_t) strtol(t1, NULL, 16) +2;
							if (strchr((t1),0x0A) != NULL)
								*strchr(t1,0x0A) = 0;

							ESP_LOGD(TAG,"chunked: %d,  strlen: %d  \"%s\"",chunked,strlen(t1)+1,t1);
							t1 +=strlen(t1)+1; //+1 for char 0,
						}

						int newlen = len - (t1-pdata) ;
						cchunk = chunked;
						ESP_LOGD(TAG,"newlen: %d   len: %d   chunked:%d  pdata:%x",newlen,len,chunked,(int)pdata);
						if(newlen > 0) clientReceiveCallback(sockfd,t1, newlen);
				} else
				{
					t1 = NULL;
					if (i++ > 20) {clientDisconnect("header1");break;}
					vTaskDelay(1); //avoid watchdog is infernal loop
					
					if (https)
						bread = wolfSSL_read(ssl, pdata+len, RECEIVE-len);
					else
						bread = recvfrom(sockfd, pdata+len, RECEIVE-len, 0, NULL, NULL);					
					if (bread <0) {clientDisconnect("header11");break;}
					if (bread >0) len += bread;
				}
			} while (t1 == NULL);
		}
	break;
	default:
// -----------
//ESP_LOGD(TAG,"LenIn: %d",len);
// Chunk computing
		lc = len; // lc rest after chunk
//	 printf("CDATAIN: chunked: %d, cchunk: %d, len: %d\n",chunked,cchunk,len);
		if((chunked != 0)&&((cchunk ==0)||(len >= cchunk-1)))  //if in chunked mode and chunk received or complete in data
		{
			if ((len ==1)&&(cchunk==1))
			{
				 len -=1;
				 cchunk = 0;
//				 ESP_LOGD(TAG,"Len00: %d  cchunk: %d",len,cchunk);
			} else
			{
//	 printf("CDATA1: chunked: %d, cchunk: %d, len: %d\n",chunked,cchunk,len);
				if (len == cchunk) // if a complete chunk in pdata, remove crlf
				{
					len -= 2;
					cchunk = 0;
//					ESP_LOGD(TAG,"Len0: %d  cchunk: %d",len,cchunk);
//	printf("lenoe:%d, chunked:%d  cchunk:%d, lc:%d, metad:%d\n",len,chunked,cchunk, lc,metad );
				} else  // an incomplete chunk in progress
				{
					if (len == cchunk-1) // missing lf: remove cr only, wait lf in next data
					{
						len -= 1;
						cchunk = 1;
//						ESP_LOGD(TAG,"Len1: %d ",len);
//	printf("leno1:%d, chunked:%d  cchunk:%d, lc:%d, metad:%d\n",len,chunked,cchunk, lc,metad );
					}
					else		// a part of end of chunk 	and beginnining of a new one
					{
						inpdata = pdata;

						while (lc != 0)
						{
							while (lc < cchunk+9)
							{
								vTaskDelay(1);
							
								if (https)
									bread = wolfSSL_read(ssl, pdata+len, 9);
								else
									bread = recvfrom(sockfd, pdata+len, 9, 0, NULL, NULL);
								if (bread <0) {clientDisconnect("chunk1");break;}
								if (bread >0) clen = bread;
								else clen = 0;
								lc+=clen;len+=clen;
								//ESP_LOGV(TAG,"more:%d, lc:%d\n",clen,lc);
							} //security to be sure to receive the new length

//	printf("leni0:%d, inpdata:%x, chunked:%d  cchunk:%d, lc:%d, \n",len,inpdata,chunked,cchunk, lc );
							inpchr=strchr(inpdata+cchunk,0x0D) ;
							if ((inpchr != NULL) &&(inpchr- (inpdata+cchunk) <16))
								*inpchr = 0; // replace lf by a end of string
							else {
								clientDisconnect("chunk"); clientConnect();
								lc = 0;
								break;
							}
							chunked = (uint32_t) strtol(inpdata+cchunk, NULL, 16)+2;  // new chunk lenght including cr lf
							clen = strlen(inpdata+cchunk)  +2;
							lc = lc -cchunk  -clen; // rest after
//	printf("leni:%d, inpdata:%x, chunked:%d  cchunk:%d, lc:%d, clen:%d, str: %s\n",len,inpdata,chunked,cchunk, lc,clen,inpdata+cchunk );
						// compact data without chunklen and crlf
							if (cchunk >1){
								memcpy (inpdata+cchunk-2,pdata+len-lc, lc);
//	printf("lenm:%d, inpdata:%x, chunked:%d  cchunk:%d, lc:%d\n",len,inpdata,chunked,cchunk, lc);
								len -= (clen +2);
								inpdata +=   (cchunk -2);
								//if (len <0) ESP_LOGD(TAG,"Len2: %d",len);
//	printf("memcpy1 at %x from %x, lc:%d\n",inpdata+cchunk-2,pdata+len-lc,lc);
							}
							else{
								memcpy (inpdata,inpdata+cchunk+clen, lc);
//	printf("lenm:%d, inpdata:%x, chunked:%d  cchunk:%d, lc:%d\n",len,inpdata,chunked,cchunk, lc);
								len -= (clen + cchunk);
								//if (len <0) ESP_LOGD(TAG,"Len3: %d",len);
//	printf("memcpy2 at %x from %x, lc:%d, len:%d\n",inpdata,inpdata+cchunk+clen,lc,len);
							}

							if (chunked > lc)
							{
								cchunk = chunked - lc ;
								if (cchunk ==1) len --;
								if (cchunk ==0) len -=2;
								//if (len <0) ESP_LOGD(TAG,"Len4: %d",len);
								lc = 0;
							}
							else
							{
								cchunk = chunked;
							}
//	printf("leniout:%d, inpdata:%x, chunked:%d  cchunk:%d, lc:%d, metad:%d  clen:%d \n",len,inpdata,chunked,cchunk, lc,metad,clen );
						}
					}
				}
			}
		}
		else
		{
			if (chunked != 0) cchunk -= len;
			lc = 0;
		}

// printf("CDATAOUT: chunked: %d, cchunk: %d, len: %d\n",chunked,cchunk,len);
//		if (len <0) ESP_LOGD(TAG,"Len: %d",len);
// meta data computing
		if (rest <0)
		{
			ESP_LOGD(TAG,"clientReceiveCallback: pdata: %x, pdataend: %x, len: %d",(int)pdata,(int)pdata+len,len);
			ESP_LOGD(TAG,"Negative enter len= %d, metad= %d  rest= %d   pdata= %x :\"%s\"",len,metad,rest,(int)pdata,pdata);
			if (len>-rest)
				*(pdata-rest) = 0; //truncated
			else
				*(pdata+len) = 0; //truncated
			if (metadata != NULL) strcat(metadata,pdata);
			if (len >= -rest)
			{
				ESP_LOGD(TAG,"Negaposi   len= %d, metad= %d  rest= %d   pdata= %x :\"%s\"",len,metad,rest,(int)pdata,pdata);
				if (metadata != NULL) clientSaveMetadata(metadata,strlen(metadata));
				metad = header.members.single.metaint ;
				pdata -= rest;
				len += rest;
				rest = 0;
			}
			else
			{
				ESP_LOGD(TAG,"Negative   len= %d, metad= %d  rest= %d   pdata= %x :\"%s\"",len,metad,rest,(int)pdata,pdata);
				pdata += len;
				rest += len;
				len = 0;
//				ESP_LOGD(TAG,"Negatafter len= %d, metad= %d  rest= %d   pdata= %x :\"%s\"",len,metad,rest,(int)pdata,pdata);
			}
//printf("Negative len out = %d, pdata: %x,metad= %d  rest= %d \n",len,pdata,metad,rest);

		}
		inpdata = pdata;
		clen = len;
		if((header.members.single.metaint != 0)&&(clen > metad))
		{
//			ESP_LOGD(TAG,"clientReceiveCallback: pdata: %x, pdataend: %x, len: %d",(int)pdata,(int)pdata+len,len);

//			ESP_LOGD(TAG,"metain len:%d, clen:%d, metad:%d, l:%d, inpdata:%x, rest:%d\n",len,clen,metad, l,(int)inpdata,rest );
			int jj = 0;
			while ((clen > metad)&&(header.members.single.metaint != 0)) // in buffer
			{
//				ESP_LOGD(TAG,"metainb len:%d, clen:%d, metad:%d, l:%d, inpdata:%x, rest:%d",len,clen,metad, l,(int)inpdata,rest );
				jj++;
				l = inpdata[metad]*16;	//new meta length
				rest = clen - metad  -l -1;

//if (l ==0){
//	printf("mt len:%d, clen:%d, metad:%d,&l:%x, l:%d, rest:%d\n",len,clen,metad,inpdata+metad, l,rest );
//if (l > 80) dump(inpdata,len);

				if (l !=0)
				{
ESP_LOGD(TAG,"clientReceiveCallback: pdata: %x, pdataend: %x, len: %d",(int)pdata,(int)pdata+len,len);
//ESP_LOGD(TAG,"mt len:%d, clen:%d, metad:%d ,&l:%x, l:%d, inpdata:%x, rest:%d, str: %s",len,clen,metad,(int)inpdata+metad, l,(int)inpdata,rest,inpdata+metad+1 );
					if (rest <0)
					{
						*(inpdata+clen) = 0; //truncated
ESP_LOGD(TAG,"mtlen len:%d, clen:%d, metad:%d, l:%d, inpdata:%x,  rest:%d",len,clen,metad, l,(int)inpdata,rest );

						if (metadata != NULL) incfree(metadata,"meta");
						metadata = incmalloc(l+1);
						strcpy(metadata,inpdata+metad+1);
					}
					else clientSaveMetadata(inpdata+metad+1,l); // just in case....
				}
				if (metad >0)
				{
//					if (spiRamFifoFree() < metad) ESP_LOGV(TAG,"metaout2 wait metad: %d, bufferfree: %d",metad,spiRamFifoFree());
//					while(spiRamFifoFree()<metad)	 // wait some room
//						vTaskDelay(20);
					if (audio_stream_consumer((char*)inpdata, metad)== -1)
					{
						playing=1;
						clientSaveOneHeader("Cannot decode",13,METANAME);
						wsHeaders();
						vTaskDelay(100);
					}
				}
				metad  = header.members.single.metaint;
				inpdata = inpdata+clen-rest;
if (rest <0) ESP_LOGD(TAG,"mt1 len:%d, clen:%d, metad:%d, l:%d, inpdata:%x,  rest:%d",len,clen,metad, l,(int)inpdata,rest );
				clen = rest;
				if (rest <0)
				{
ESP_LOGD(TAG,"mt2 len:%d, clen:%d, metad:%d, l:%d, inpdata:%x,  rest:%d",len,clen,metad, l,(int)inpdata,rest );
					clen = 0;
					break;
				}
			}	// while in buffer
			if (rest >=0)
			{
				metad = header.members.single.metaint - rest ; //until next
				if (rest >0)
				{
//					if (spiRamFifoFree() < rest) ESP_LOGV(TAG,"metaout3 wait rest: %d, bufferfree: %d",rest,spiRamFifoFree());
//					while(spiRamFifoFree()<rest)	 // wait some room
//						vTaskDelay(20);//
					if (audio_stream_consumer((char*)inpdata, rest)== -1)
					{
						playing=1;
						clientSaveOneHeader("Cannot decode",13,METANAME);
						wsHeaders();
						vTaskDelay(100);
					}
				}
				rest = 0;
			}
//ESP_LOGD(TAG,"metaout len:%d, clen:%d, metad:%d, l:%d, inpdata:%x, rest:%d",len,clen,metad, l,(int)inpdata,rest );
		} else
		{

			if (header.members.single.metaint != 0) metad -= len;
//printf("out len = %d, metad = %d  metaint= %d, rest:%d\n",len,metad,header.members.single.metaint,rest);
			if (len >0)
			{
//				if (spiRamFifoFree() < len) ESP_LOGV(TAG,"metaout1 wait len: %d, bufferfree: %d",len,spiRamFifoFree());
//				while(spiRamFifoFree()<len)	 // wait some room
//						vTaskDelay(20);
				if (audio_stream_consumer((char*)(pdata+rest), len)== -1)
				{
					playing=1;
					clientSaveOneHeader("Cannot decode",13,METANAME);
					wsHeaders();
					vTaskDelay(100);
				}
			}
		}
// ---------------

		if ((!playing )  && (((++dloop) % 40)==0)) 
		{
			kprintf(CLIPLAY,0x0d,0x0a);
			playing=1;
			if (!ledStatus){ 
			if (getLedGpio() != GPIO_NONE) gpio_set_level(getLedGpio(), ledPolarity ? 0 : 1);	
			}				
			setVolumei(getVolume());
		}
	} // switch
}



uint8_t bufrec[RECEIVE+20];
    /* declare wolfSSL objects */
    WOLFSSL_CTX *ctx;
    WOLFSSL *ssl;

void wolfSSL_log_function(const int logLevel, const char *const logMessage){
//    ESP_LOGD(TAG,"WOLFSSL:%s\n",logMessage);
if (logLevel <= wolfSSL_getLogState())
	kprintf("WOLFSSL:%d %s\n",logLevel,logMessage);
}

uint8_t wolfSSL_getLogState()
{
	uint8_t level[4]= {0,1,3,4};
	return (level[(g_device->options&T_WOLFSSL)>>S_WOLFSSL]);
}
	
void clientTask(void *pvParams) {
	portBASE_TYPE uxHighWaterMark;
	struct timeval timeout;
    timeout.tv_usec = 0;
	timeout.tv_sec = 6;
	int sockfd;
	int bytes_read;
	uint8_t cnterror;
	char userAgent[40];
	struct sockaddr_in dest;
	int ret;

	vTaskDelay(200);
	spiRamFifoInit();	

	if (strlen(g_device->ua) == 0) strcpy(g_device->ua,"Karadio32/2.0");
	strcpy(userAgent, g_device->ua);
//----------------------------------------------------------------------
	/* Initialize wolfSSL */
//	wolfSSL_getLogState()?wolfSSL_Debugging_ON():wolfSSL_Debugging_OFF();
	wolfSSL_Debugging_ON();
	if (wolfSSL_Init() != WOLFSSL_SUCCESS) {
		ESP_LOGE(TAG,"Failed to init WOLFSSL");}
	/* Create and initialize WOLFSSL_CTX */
	if ((ctx = wolfSSL_CTX_new(wolfSSLv23_client_method())) == NULL) {
		ESP_LOGE(TAG,"Failed to create WOLFSSL_CTX");
	}
    wolfSSL_SetLoggingCb(wolfSSL_log_function);	
	/* Load client certificates into WOLFSSL_CTX */
	if ((ret = wolfSSL_CTX_load_verify_buffer(ctx, client_cert_der_1024,
		sizeof_client_cert_der_1024, WOLFSSL_FILETYPE_ASN1)) != SSL_SUCCESS) {
		ESP_LOGE(TAG,"Failed to load %d, please check the file.",ret);
	}
	/* not peer check */
	wolfSSL_CTX_set_verify(ctx, WOLFSSL_VERIFY_NONE, 0);
//----------------------------------------------------------------------
					
//	portBASE_TYPE uxHighWaterMark;
//	uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
//	printf("watermark webclient:%d  heap:%d\n",uxHighWaterMark,xPortGetFreeHeapSize( ));

	while(1) {
		xSemaphoreGive(sConnected);
		if(xSemaphoreTake(sConnect, portMAX_DELAY)) 
		{		
			if (get_audio_output_mode() == VS1053)  VS1053_HighPower();
			xSemaphoreTake(sDisconnect, 0);
			sockfd = socket(AF_INET, SOCK_STREAM, 0);
			ESP_LOGD(TAG,"Socket: %d", sockfd);
			if(sockfd < 0)
			{
				ESP_LOGE(TAG,"Socket create, errno: %d", errno);
				xSemaphoreGive(sDisconnect);
				continue;
			}
			bzero(&dest, sizeof(dest));
			dest.sin_family = AF_INET;
			dest.sin_port = htons(clientPort);
			dest.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)(serverInfo->h_addr_list[0])));
			ESP_LOGI(TAG,"IP: %x   ADDR:%s", dest.sin_addr.s_addr, inet_ntoa(*(struct in_addr*)(serverInfo-> h_addr_list[0])));
			bytes_read = 0;
			/*---Connect to server---*/
			ssl = NULL;
			if(connect(sockfd, (struct sockaddr*)&dest, sizeof(dest)) >= 0)
			{
				test_https();
				if (https)
				{
					spiRamFifoDestroy();
					setSPIRAMSIZE(128); // need heap for ssl connect
					spiRamFifoInit();
					vTaskDelay(1);
//					wolfSSL_getLogState()?wolfSSL_Debugging_ON():wolfSSL_Debugging_OFF();
					/* Create a WOLFSSL object */
					if ((ssl = wolfSSL_new(ctx)) == NULL) {
						ESP_LOGE(TAG,"Failed to create WOLFSSL ssl object");
						goto NotConnected;
					}
					wolfSSL_set_using_nonblock(ssl, 1);    
					/* Attach wolfSSL to the socket */
					wolfSSL_set_fd(ssl, sockfd);
				
					/* Connect to wolfSSL on the server side */
					if (wolfSSL_connect(ssl) != SSL_SUCCESS) {
						int err=wolfSSL_get_error(ssl, 0);
						ESP_LOGE(TAG,"WolfSSL_connect error: %d",err);
						goto NotConnected;
					}				
				}

//				printf("WebClient Socket connected\n");
				memset(bufrec,0, RECEIVE+20);

				char *t0 = strstr(clientPath, ".m3u");
				if (t0 == NULL)  t0 = strstr(clientPath, ".pls");
				if (t0 == NULL)  t0 = strstr(clientPath, ".xspf");
				if (t0 == NULL)  t0 = strstr(clientPath, ".m3u8");
				if (t0 == NULL)  t0 = strstr(clientPath, ".asx");
				if (t0 != NULL)  // a playlist asked
				{
				  cstatus = C_PLAYLIST;

				  sprintf((char*)bufrec, "GET %s HTTP/1.1\r\nHOST: %s\r\nUser-Agent: %s\r\n\r\n", clientPath,cleanURL(),g_device->ua); //ask for the playlist
			    }
				else
				{
					if (strcmp(cleanURL(),"stream.pcradio.biz") ==0)
						strcpy(userAgent,"pcradio");
						
					sprintf((char*)bufrec, "GET %s HTTP/1.1\r\nHost: %s\r\nicy-metadata: 1\r\nUser-Agent: %s\r\n\r\n", clientPath,cleanURL(),userAgent);
				}
//printf("st:%d, url: %s\nClient Sent:\n%s\n",cstatus,cleanURL(),bufrec);
				xSemaphoreTake(sConnected, 0);
				if (https)
				{
					if (wolfSSL_write(ssl, bufrec, strlen((char*)bufrec)) != strlen((char*)bufrec)) {
						ESP_LOGE(TAG,"wolfSSL_write");
						goto clearAll;
					}
				}
				else
					send(sockfd, (char*)bufrec, strlen((char*)bufrec), 0);

				ESP_LOGD(TAG,"\nSent: %s\n",bufrec);
				if (setsockopt (sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
					ESP_LOGE(TAG,"Socket: %d  setsockopt: %d  errno:%d ",sockfd, SO_RCVTIMEO,errno);

/// Wi-Fi QoS
				const int ip_precedence_vi = 4;
				const int ip_precedence_offset = 5;
				int priority = (ip_precedence_vi << ip_precedence_offset);
				if (setsockopt(sockfd, IPPROTO_IP, IP_TOS, &priority, sizeof(priority))< 0)
					ESP_LOGE(TAG,"Socket: %d  setsockopt: %d  errno:%d ",sockfd, IP_TOS,errno);
//////
				cnterror = 0;			
				wsMonitor();
				ramSinit();
				do
				{
					if (https)
					{
//						int incr = 0;
//						bytes_read = 0;
//						while (( bytes_read <= 0 )&& (incr++ <2))
						{	
							bytes_read = wolfSSL_read(ssl, bufrec, RECEIVE);							
							if ( bytes_read < 0 )
							{   					    
								int err;
								char buffer[80];
								err = wolfSSL_get_error(ssl, 0);
								wolfSSL_ERR_error_string(err, buffer);
								ESP_LOGW(TAG,"wolfSSL_read: %d, read: %s",err, buffer);
								if (wolfSSL_want_read(ssl) == 1) bytes_read = 0;
								vTaskDelay(10);
							}	
						}						
					}	
					else
					{
						bytes_read = recvfrom(sockfd, bufrec,RECEIVE, 0, NULL, NULL);						
						if ( bytes_read < 0 )
						{
							ESP_LOGE(TAG,"Socket: %d, read: %d, errno:%d ",sockfd, bytes_read,errno);
							if (errno == 11) bytes_read = 0;
						}
					}
//if (bytes_read < 100 ) ESP_LOGD(TAG,"\nReceived: %s\n",bufrec);
//	printf("Rec:%d\n%s\n",bytes_read,bufrec);
//	printf(" %d ",bytes_read);	fflush(stdout);
					if ( bytes_read > 0 )
					{
						cnterror = 0;
						clientReceiveCallback(sockfd,(char*)bufrec, bytes_read);
					}
					else
					{
						ESP_LOGW(TAG,"No data in recv. Errno = %d, error count: %d",errno,++cnterror);
						vTaskDelay(10);
						if ((errno == 128)||(cnterror >= 10 )) break;
					}
					vTaskDelay(2); // >1 mandatory
					// if a stop is asked
					if(xSemaphoreTake(sDisconnect, 0))
					{ clearHeaders(); break;}
				}
				while (( bytes_read > 0 )||(playing && (bytes_read == 0)));
			} else
			{
				NotConnected:
				ESP_LOGE(TAG,"Socket: %d  connect errno:%d ",sockfd,errno);
				clientSaveOneHeader("Connection error",16,METANAME);
				wsHeaders();
				shutdown(sockfd,SHUT_RDWR); // stop the socket
				vTaskDelay(1);
				clientDisconnect("Invalid");
				if (https){
					if (ssl) wolfSSL_free(ssl);     /* Free the wolfSSL object */
					ESP_LOGI(TAG,"SSL Cleanup Socket: %d",sockfd);
				}
				close(sockfd);
				continue;
			}
			/*---Clean up---*/
			if (bytes_read <= 0 )  //nothing received or error or disconnected
			{
					if ((playing)&&(once == 0))  // try restart
					{
						clientDisconnect("try restart");
						vTaskDelay(1);
						clientConnect();
						playing=1; // force
					}
					else if ((!playing)&&(once == 1)){ // nothing played. Force the read of the buffer
						// some data not played
						if ((!playing )&& (spiRamFifoFill())) {
							playing=1;
							vTaskDelay(1);
							setVolumei(getVolume());
							kprintf(CLIPLAY,0x0d,0x0a);
							while (spiRamFifoFill()) vTaskDelay(200);
//							vTaskDelay(100);
							playing=0;
							clientDisconnect("Data not played");
						}
					}
						//
					else if ((!playing)&&(once == 0)) {  // nothing received
							clientDisconnect(nodata);
							clientSaveOneHeader(nodata,7,METANAME);
							wsHeaders();
							vTaskDelay(1);
					}
					else{  //playing & once=1 and no more received stream
						while (spiRamFifoFill()) vTaskDelay(200);
						vTaskDelay(100);
						clientDisconnect("once");
					}
			}//jpc

			if (playing)  // stop clean
			{
				if (get_player_status() != STOPPED)
					audio_player_stop();
				player_config->media_stream->eof = true;
				if (get_audio_output_mode() == VS1053) VS1053_flush_cancel();
				playing = 0;
				if (get_audio_output_mode() == VS1053) VS1053_LowPower();
				strcpy(userAgent,g_device->ua);
			}
			
			clearAll:
			spiRamFifoReset();
			if (https){
				if (ssl) wolfSSL_free(ssl);    // Free the wolfSSL object 
				ESP_LOGI(TAG,"SSL Cleanup 1 Socket: %d",sockfd);
			}
			shutdown(sockfd,SHUT_RDWR); // stop the socket
			vTaskDelay(10);
			close(sockfd);
			if (cstatus == C_PLAYLIST)
			{
			  clientConnect();
			}
			vTaskDelay(2);
			uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
			ESP_LOGI(TAG,"watermark : %x  %d",uxHighWaterMark,uxHighWaterMark);
		}
	}
}
