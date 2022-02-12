/* (c)jp cocatrix May 2016 
 *
 * Copyright 2016 karawin (http://www.karawin.fr)

	quick and dirty websocket inplementation for wifi webradio
	minimal implementaion for short data messages
*/
#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include <string.h>
#include "esp_system.h"
#include "lwip/api.h"
#include "lwip/sockets.h"
#include "cencode_inc.h"
#include "websocket.h"
#include "interface.h"
#include "webserver.h"
#include "cencode_inc.h"
#include "libsha1.h"
//#include <stddef.h> /* for size_t */

#define TAG	"websocket"

char strwMALLOC[]  = {"inwmalloc fails for %d\n"};
char strwMALLOC1[]  = {"Websocket %s malloc fails\n"};
char strwSOCKET[]  = {"Websocket socket fails %s errno: %d\n"};

client_t webserverclients[NBCLIENT];
//set of socket descriptors
fd_set readfds;

void base64_encode_local(uint8_t * data, size_t length, char* output) {
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
	
    SHA1_CTX ctx;
	
    SHA1IInit(&ctx);
    SHA1IUpdate(&ctx, (const unsigned char*)clientKey, strlen(clientKey));
    SHA1IFinal(&sha1HashBin[0], &ctx);
    base64_encode_local(sha1HashBin, 20,Output);
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
	websocketacceptKey(key,encodedSha1);
	//Fill Output Buffer
	encodedLength = strlen(encodedSha1);
	outputLength = encodedLength + strlen(str1) + 2*strlen(s);
	
	strcpy(outputMessage,str1);
	strcat(outputMessage,encodedSha1);
	strcat(outputMessage,s);
	strcat(outputMessage,s);
	//Add extra /n/r at the end
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

    // calculate header Size
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
	header.maskKey = 0;
	if (!iswebsocket(socket)) return;
	while(headerLen > recbytes) recbytes += read(socket , buf+recbytes, MAXDATA-recbytes);
	header.fin = ((*payload >> 7) & 0x01);
	header.opCode = (wsopcode_t) (*payload & 0x0F);
	payload++; // second bytes
    header.mask = ((*payload >> 7) & 0x01);
    header.payloadLen = (wsopcode_t) (*payload & 0x7F);
    payload++;	
	
	if(header.payloadLen == 126) {
		headerLen += 2;
		while(headerLen > recbytes) recbytes += read(socket , buf+recbytes, MAXDATA-recbytes);
        header.payloadLen = payload[0] << 8 | payload[1];
        payload += 2;
    } else if(header.payloadLen == 127) {
		headerLen += 8;
		while(headerLen > recbytes) recbytes += read(socket , buf+recbytes, MAXDATA-recbytes);		
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
		header.maskKey = payload;
        payload += 4;
    }	
	 headerLen += header.payloadLen;	
	while(headerLen > recbytes) recbytes += read(socket , buf+recbytes, MAXDATA-recbytes);
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
	sendFrame(socket, WSop_text, (uint8_t *)buf , len );
}	
//broadcast a txt data to all clients
void websocketbroadcast(char* buf, int len)
{
	int i ;
	ESP_LOGV(TAG,"websocketbroadcast: %s",buf);
	for (i = 0;i<NBCLIENT;i++)	
		if (iswebsocket( webserverclients[i].socket))
		{
			websocketwrite( webserverclients[i].socket,  buf, len);
		}
}	
//broadcast a txt data to all clients but the sender
void websocketlimitedbroadcast(int socket,char* buf, int len)
{
	int i ;
	ESP_LOGV(TAG,"websocketlimitedbroadcast: %s",buf);
	for (i = 0;i<NBCLIENT;i++)	
		if (iswebsocket( webserverclients[i].socket))
		{
			if (webserverclients[i].socket != socket) websocketwrite( webserverclients[i].socket,  buf, len);
		}
}	


void websocketAccept(int wsocket,char* bufin,int buflen)
{
int32_t recbytes = 0;
	char buf[150];
	bufin[buflen] = 0;
		if ((!iswebsocket(wsocket ))&&(websocketnewclient(wsocket))) 
		{
			recbytes = decodeHttpMessage (bufin, buf);
			buf[recbytes+1] = 0;
			write(wsocket, buf, strlen(buf));  // reply to accept	
		}
}

int websocketRead(int conn)
{
	char buf[MAXDATA];
	int32_t recbytes = 0;
	if (buf != NULL)
	{
		recbytes = read(conn , buf, MAXDATA);
		if (recbytes < 0) {
			if ((errno != EAGAIN )&&(errno != 0 ))
			{
				if ((errno != 104 /*ECONNRESET*/ )&&(errno != 113 /*EHOSTUNREACH*/ ))
				{
					printf (strwSOCKET,"read", errno);
					wsclientDisconnect(conn, 500,NULL,0);		
				}
				return recbytes;
			}
		}
		if (recbytes > 0)
		{
			websocketparsedata(conn, buf, recbytes);
		}
	}
	return recbytes;
}


