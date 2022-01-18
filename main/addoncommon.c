// common data for ucg or u8g
// to avoid double space (only one type of screen per conf.

#include "addoncommon.h"
#include "stdlib.h"

  uint16_t y ;		//Height of a line
  uint16_t yy;		//Height of screen
  uint16_t x ;		//Width
  uint16_t z ;		// an internal offset for y

  struct tm *dt;
  uint16_t volume;

  char station[BUFLEN]; //received station
  char title[BUFLEN];	// received title
  char nameset[BUFLEN]; // the local name of the station

  char* lline[LINES] ; // array of ptr of n lines 
  uint8_t  iline[LINES] ; //array of index for scrolling
  uint8_t  tline[LINES] ;
  uint8_t  mline[LINES] ; // mark to display


  char nameNum[5] ; // the number of the current station
  char genre[BUFLEN/2]; // the local name of the station

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
string_rec  = calloc(strlen(string)+1, sizeof(uint8_t));
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
