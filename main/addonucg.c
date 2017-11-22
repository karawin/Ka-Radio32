/******************************************************************************
 * 
 * Copyright 2017 karawin (http://www.karawin.fr)
 *
*******************************************************************************/

#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "driver\gpio.h"
#include "esp_heap_trace.h"
#include "gpio.h"
#include "addon.h"
#include "ucg_esp32_hal.h"
#include "app_main.h"
#include <time.h>
#include "esp_log.h"
#include "logo.h"

#define TAG  "addonucg"


#define ucg_SetColori(a,b,c,d) ucg_SetColor(a,0,b,c,d)

// TOP Background & str  COLOR
#define CTBACK 50,50,100
#define CTTFONT 200,200,0
// Body font color
#define CBODY 110,255,110

#define CBLACK 0,0,0
#define CWHITE 255,255,255
 

// nams <--> num of line
#define STATIONNAME 0
#define STATION1  1
#define STATION2  2
#define IP        3
#define GENRE     2
#define TITLE1    3
#define TITLE11   4
#define TITLE2    5
#define TITLE21   6
#define VOLUME    7
#define TIME      8

#define BUFLEN  256
#define LINES	9

static uint16_t y ;		//Height of a line
static uint16_t yy;		//Height of screen
static uint16_t x ;		//Width
static uint16_t z ;		// an internal offset for y

//static struct tm *dt;
static char strsec[30]; 
static uint16_t volume;

static char station[BUFLEN]; //received station
static char title[BUFLEN];	// received title
static char nameset[BUFLEN]; // the local name of the station

static char* lline[LINES] ; // array of ptr of n lines 
static uint8_t  iline[LINES] ; //array of index for scrolling
static uint8_t  tline[LINES] ;
static uint8_t  mline[LINES] ; // mark to display

static char nameNum[5] ; // the number of the current station
static char genre[BUFLEN/2]; // the local name of the station

static char TTitleStr[15];
static char TTimeStr[15];


////////////////////////////////////////
char* getNameNumUcg()
{
	return nameNum;
}	

void setVolumeUcg(uint16_t vol){ volume = vol;}

////////////////////////////////////////
// Clear all buffers and indexes
void clearAllUcg()
{
      title[0] = 0;
      station[0]=0;
    for (int i=1;i<LINES;i++) {lline[i] = NULL;iline[i] = 0;tline[i] = 0;;mline[i]=1;}
}
////////////////////////////////////////
void cleartitleUcg(uint8_t froml)
{
     title[0] = 0;
     for (int i = froml;i<LINES;i++)  // clear lines
     {
		lline[i] = NULL;
		iline[i] = 0;
		tline[i] = 0;
		mline[i] = 1;
     }  
}

////////////////////////////////////////
void removeUtf8(char *characters)
{
  int Rindex = 0;
  while (characters[Rindex])
  {
    if ((characters[Rindex] >= 0xc2)&&(characters[Rindex] <= 0xc3)) // only 0 to FF ascii char
    {
      characters[Rindex+1] = ((characters[Rindex]<<6)&0xFF) | (characters[Rindex+1] & 0x3F);
      int sind = Rindex+1;
      while (characters[sind]) { characters[sind-1] = characters[sind];sind++;}
      characters[sind-1] = 0;
    }
    Rindex++;
  }
}

// Mark the lines to draw
void markDrawUcg(int i)
{
  mline[i] = 1;
}


////////////////////////////////////////
// scroll each line
void scrollUcg()
{
int16_t len;

	for (int i = 0;i < LINES;i++)
	{  
		if (lline[i] != NULL)
		{	
			if (tline[i]>0) 
			{
				if (tline[i] == 3) 
				{
					iline[i]= 0;
					if (ucg_GetStrWidth(&ucg,lline[i]) > x) markDrawUcg(i);//draw(i);
				}
				tline[i]--;		 
			} 
			else
			{
				if (i == 0)
					len = ucg_GetStrWidth(&ucg,nameNum) + ucg_GetStrWidth(&ucg,lline[i]+iline[i]);
				else
					len = ucg_GetStrWidth(&ucg,lline[i]+iline[i]);
				if (len > x)
				{      
					iline[i] += x/6;
					len = iline[i];
					while ((*(lline[i]+iline[i])!=' ')&&(*(lline[i]+iline[i])!='-')&&(iline[i]!= 0))iline[i]--;
					if (iline[i]==0) iline[i]=len;     
					markDrawUcg(i); //draw(i);
				}
				else 
					{tline[i] = 4;}
			}
		}
	}
}


//////////////////////////
// set color of font per line
void setColor(int i)
{
        switch(i){
          case STATIONNAME: ucg_SetColori(&ucg,0,0,0); break;
          case STATION1: ucg_SetColori(&ucg,255,255,255); break;
          case STATION2: ucg_SetColori(&ucg,255,200,200);  break;
          case TITLE1:
          case TITLE11: ucg_SetColori(&ucg,255,255,0);  break;
          case TITLE2:
          case TITLE21: ucg_SetColori(&ucg,0,255,255); break; 
          case VOLUME:  ucg_SetColori(&ucg,200,200,255); break; 
          default:ucg_SetColor(&ucg,0,CBODY);  
        }  
}

////////////////////
// draw one line
void draw(int i)
{
	uint16_t len,xpos,yyy;
	 
    if ( mline[i]) mline[i] =0;
    if (i >=3) z = y/2 ; else z = 0;
    switch (i) {
        case STATIONNAME:
		ucg_SetFont(&ucg,ucg_font_6x13_tf);
        ucg_SetColori(&ucg,255,255,255);  
        ucg_DrawBox(&ucg,0,0,x,13-ucg_GetFontDescent(&ucg));  
        ucg_SetColori(&ucg,0,0,0);  
		if (lline[i] != NULL)
		{
			if (nameNum[0] ==0)  ucg_DrawString(&ucg,1,2,0,lline[i]+iline[i]);
			else 
			{
			ucg_DrawString(&ucg,1,2,0,nameNum);
			ucg_DrawString(&ucg,ucg_GetStrWidth(&ucg,nameNum)-2,2,0,lline[i]+iline[i]);
			}
		}
        break;
        case VOLUME:
          ucg_SetColori(&ucg,0,0,200);   
          ucg_DrawFrame(&ucg,0,yy-10,x/2,8); 
          ucg_SetColori(&ucg,255,0,0); 
          ucg_DrawBox(&ucg,1,yy-9,((uint16_t)(x/2*volume)/255),6);                  
        break;
        case TIME:
          ucg_SetFont(&ucg,ucg_font_5x8_mf);
          len = ucg_GetStrWidth(&ucg,strsec);
          xpos = (3*x/4)-(len/2);
          yyy = yy -10;
          ucg_SetColori(&ucg,250,250,255); 
          ucg_SetColor(&ucg,1,CBLACK); 
          ucg_SetFontMode(&ucg,UCG_FONT_MODE_SOLID);
          ucg_DrawString(&ucg,xpos,yyy,0,strsec); 
          ucg_SetFontMode(&ucg,UCG_FONT_MODE_TRANSPARENT);
        break;
        default:
          ucg_SetColori(&ucg,0,0,0); 
          ucg_DrawBox(&ucg,0,y*i+z,x,13-ucg_GetFontDescent(&ucg)); 
          setColor(i);
          if (lline[i] != NULL) ucg_DrawString(&ucg,0,y*i+z+1,0,lline[i]+iline[i]);                
   }      
}


////////////////////////////////////////
// draw the full screen
void drawLinesUcg()
{
	ucg_SetFont(&ucg,ucg_font_6x13_tf);
    for (int i=0;i<LINES;i++)
    {
        if (mline[i]) draw(i); 
    }
}



////////////////////////////////////////
// draw all
void drawFrameUcg(uint8_t mTscreen,struct tm *dt)
{
//printf("drawFrameUcg, mTscreen: %d\n",mTscreen);
int i;
    switch (mTscreen){
    case 1: 
		ucg_ClearScreen(&ucg);
		TTitleStr[0] = 0;   
		ucg_SetFont(&ucg,ucg_font_6x13_tf);
		ucg_SetColor(&ucg,0,255,255,0);  
		ucg_SetColor(&ucg,1,0,255,255);  
		ucg_DrawGradientLine(&ucg,0,(4*y) - (y/2)-5,x,0);
		ucg_SetColor(&ucg,0,CBLACK);  
		ucg_DrawBox(&ucg,0,0,x-1,15);  
		for (i=0;i<LINES;i++) draw(i);
		// no break
	case 2:	  
		sprintf(strsec,"%02d-%02d  %02d:%02d:%02d",dt->tm_mon+1,dt->tm_mday,dt->tm_hour, dt->tm_min,dt->tm_sec);
		markDrawUcg(TIME);
		drawLinesUcg();
		break;
	 default:;
	}
	
	//screenBottomUcg();    
}


//////////////////////////
void drawTTitleUcg(char* ttitle)
{ 

	if (strcmp(ttitle,TTitleStr) != 0)
	{
		ucg_SetFont(&ucg, ucg_font_helvB18_tf);
		uint16_t xxx = (x/2)-(ucg_GetStrWidth(&ucg,ttitle)/2);
		ucg_SetColor(&ucg,0,CTBACK);  
		ucg_DrawBox(&ucg,0,0,x,41); 
		ucg_SetColor(&ucg,0,CTTFONT);  
		ucg_DrawString(&ucg,xxx,(40-ucg_GetFontAscent(&ucg))>>1,0,ttitle);
		strcpy(TTitleStr,ttitle);
	}
}
//////////////////////////
void drawNumberUcg(uint8_t mTscreen,char* irStr)
{
  uint16_t xxx ;
  char ststr[] = {"Number"};
    switch (mTscreen){
      case 1:     
		TTitleStr[0] = 0;   
        drawTTitleUcg(ststr);   
      // no break
      case 2:  
        xxx = (x/2)-(ucg_GetStrWidth(&ucg,irStr)/2); 
        ucg_SetColor(&ucg,0,CBLACK);  
        ucg_DrawBox(&ucg,0,40,x,yy);     
        ucg_SetFont(&ucg,ucg_font_inr38_tf); 
        ucg_SetColor(&ucg,0,CBODY);  
        ucg_DrawString(&ucg,xxx,60,0, irStr);
        break;
      default:; 
    }  

//  screenBottomUcg();  
}
//////////////////////////
void drawStationUcg(uint8_t mTscreen,char* snum,char* ddot)
{
	
  char ststr[] = {"Station"};
  int16_t len;
    switch (mTscreen){
      case 1:  
		TTitleStr[0] = 0;        
        drawTTitleUcg(ststr);
      // no break
      case 2:   
        ucg_SetColor(&ucg,0,CBLACK); 
        ucg_DrawBox(&ucg,0,40,x,yy);     
        ucg_SetFont(&ucg,ucg_font_fur14_tf);
        ucg_SetColor(&ucg,0,CBODY);
//        ddot = strstr(sline,":");
        if (ddot != NULL)
        {
          ucg_DrawString(&ucg,(x/2)-(ucg_GetStrWidth(&ucg,snum)/2),55,0,snum);
          len = (x/2)-(ucg_GetStrWidth(&ucg,ddot)/2);
          if (len <0) len = 0;
          ucg_DrawString(&ucg,len,90,0, ddot);
        }
        break;
      default:; 
    } 	

//  screenBottomUcg(); 	
}


void drawVolumeUcg(uint8_t mTscreen,char* aVolume)
{
  char vlstr[] = {"Volume"};
  volume = atoi(aVolume);
    switch (mTscreen){
      case 1: 
//		ucg_ClearScreen(&ucg);
		TTitleStr[0] = 0;
        drawTTitleUcg(vlstr) ;		
      // no break
      case 2:
//        ucg_SetFont(&ucg,ucg_font_inr49_tf);
        ucg_SetFont(&ucg,ucg_font_inr38_mf);  
        uint16_t xxx;
        xxx = (x/2)-(ucg_GetStrWidth(&ucg,aVolume)/2);
        ucg_SetColor(&ucg,0,CBLACK);  
        ucg_DrawBox(&ucg,0,40,x,yy);     
        ucg_SetColor(&ucg,0,CBODY);  
        ucg_DrawString(&ucg,xxx,60,0,aVolume); 
        break;
      default:; 
    }

//  screenBottomUcg(); 
}

static void drawSecond(struct tm *dt,unsigned timein)
{
  static unsigned insec;
  if (insec != timein)
  {
  char strseco[3]; 
  uint16_t len;
  sprintf(strseco,":%02d",dt->tm_sec);
//  ucg_SetFont(&ucg,ucg_font_5x8_mf);
  ucg_SetFont(&ucg,ucg_font_6x13_mf);
  len = ucg_GetStrWidth(&ucg,strseco);
//  ucg_SetColor(&ucg,0,0,0,0);  
//  ucg_DrawBox(&ucg,x-len-8,yy-18,x,yy);  
  
  ucg_SetColor(&ucg,1,CBLACK); 
  ucg_SetFontMode(&ucg,UCG_FONT_MODE_SOLID); 
  //ucg_SetColor(&ucg,0,CBLACK);
  //if ((strseco[1] == '1')||(strseco[2] == '1'))ucg_DrawString(&ucg,x-len-8,yy-18,0," 88"); 
  ucg_SetColor(&ucg,0,CBODY);
  ucg_DrawString(&ucg,x-len-8,yy-18,0,strseco); 
  ucg_SetFontMode(&ucg,UCG_FONT_MODE_TRANSPARENT);
  insec = timein; //to avoid redisplay
  }    
}

void drawTimeUcg(uint8_t mTscreen,struct tm *dt,unsigned timein)
{
  char strdate[23];
  char strtime[20];
    sprintf(strtime,"%02d:%02d", dt->tm_hour, dt->tm_min);
    switch (mTscreen){
      case 1:
//		ucg_ClearScreen(&ucg);
		TTitleStr[0] = 0;
		TTimeStr[0] = 0;
        ucg_SetColor(&ucg,0,CBLACK);  
        ucg_DrawBox(&ucg,0,40,x,yy);     		
        // draw ip
        ucg_SetFont(&ucg,ucg_font_6x13_tf);		
		sprintf(strdate,"IP: %s", getIp());
        ucg_SetColor(&ucg,0,255,128,255);  
        ucg_DrawString(&ucg,4,yy-18,0,strdate);		
      case 2:
	    sprintf(strdate,"%02d-%02d-%04d", dt->tm_mon+1, dt->tm_mday, dt->tm_year+1900);
		drawTTitleUcg(strdate);
		if (strcmp(TTimeStr,strtime)!= 0)
		{	
			ucg_SetFont(&ucg,ucg_font_inr38_mf); 
			ucg_SetColor(&ucg,0,CBODY);		
			ucg_SetFontMode(&ucg,UCG_FONT_MODE_SOLID); 
			ucg_DrawString(&ucg,(x/2)-(ucg_GetStrWidth(&ucg,strtime)/2),55,0,strtime); 
			strcpy(TTimeStr,strtime);
			ucg_SetFontMode(&ucg,UCG_FONT_MODE_TRANSPARENT);
		}

		break;
      default:;
    }
	drawSecond(dt,timein);;     	
}


////////////////////////////////////////
void separatorUcg(char* from)
{
    char* interp;
//    len = strlen(from);
    ucg_SetFont(&ucg,ucg_font_6x13_tf);
    while (from[strlen(from)-1] == ' ') from[strlen(from)-1] = 0; // avoid blank at end
    while ((from[0] == ' ') ){ strcpy( from,from+1); }
    interp=strstr(from," - ");
	if (from == nameset) {/*lline[0] = nameset;*/lline[1] = NULL;lline[2] = NULL;return;}
	if (interp != NULL)
	{
	  from[interp-from]= 0;
	  lline[(from==station)?STATION1:TITLE1] = from;
	  lline[(from==station)?STATION2:TITLE2] = interp+3;
    mline[(from==station)?STATION1:TITLE1]=1;
    mline[(from==station)?STATION2:TITLE2]=1;
	} else
	{
	  lline[(from==station)?STATION1:TITLE1] = from;
    mline[(from==station)?STATION1:TITLE1]=1;
	}

// 2 lines for Title
 if ((lline[TITLE1]!= NULL)&&(from == title)&&(ucg_GetStrWidth(&ucg,lline[TITLE1]) > x))
 {
    int idx = strlen(lline[TITLE1]);
    *(lline[TITLE1]+idx) = ' ';
    *(lline[TITLE1]+idx+1) = 0;
    while ((ucg_GetStrWidth(&ucg,lline[TITLE1]) > x)&&(idx !=0))
    {
      *(lline[TITLE1]+idx--)= ' ';
      while ((*(lline[TITLE1]+idx)!= ' ')&&(idx !=0)) idx--;
      if (idx != 0) *(lline[TITLE1]+idx)= 0;
    }
    lline[TITLE11] = lline[TITLE1]+idx+1;
    mline[TITLE11]=1; 
 }
 
 if ((lline[TITLE2]!= NULL)&&(from == title)&&(ucg_GetStrWidth(&ucg,lline[TITLE2]) > x))
 {
    int idx = strlen(lline[TITLE2]);
    *(lline[TITLE2]+idx) = ' ';
    *(lline[TITLE2]+idx+1) = 0;
    while ((ucg_GetStrWidth(&ucg,lline[TITLE2]) > x)&&(idx !=0))
    {
      *(lline[TITLE2]+idx--)= ' ';
      while ((*(lline[TITLE2]+idx)!= ' ')&&(idx !=0)) idx--;
      if (idx != 0) *(lline[TITLE2]+idx)= 0;
    }
    lline[TITLE21] = lline[TITLE2]+idx+1;
    mline[TITLE21]=1; 
 }
}

//cli.meta
void metaUcg(char* ici)
{
     cleartitleUcg(3); 
     strcpy(title,ici+7);    
	 removeUtf8(title);
     separatorUcg(title); 	
}

//cli.icy4
void icy4Ucg(char* ici)
{
	 strcpy(genre,ici+7);
     removeUtf8(genre); 
     lline[2] = genre;
}
//cli.icy0
void icy0Ucg(char* ici)
{
      clearAllUcg();
      if (strlen(ici+7) == 0) strcpy (station,nameset);
      else strcpy(station,ici+7);
	  removeUtf8(station);
      separatorUcg(station);	
}

//cli.stopped or label
void statusUcg(char* label)
{
     cleartitleUcg(3);
     strcpy(title,label);
     lline[TITLE1] = title;	
}
//cli.nameset
void namesetUcg(char* ici)
{
	strcpy(nameset,ici+8);
    ici = strstr(nameset," ");
    if (ici != NULL)
    {
       clearAllUcg();
       strncpy(nameNum,nameset,ici-nameset+1);
       nameNum[ici - nameset+1] = 0; 
	   setFuturNum(atoi(nameNum));     
    }
    strcpy(nameset,nameset+strlen(nameNum));
	removeUtf8(nameset);
    lline[STATIONNAME] = nameset;
}

// cli.playing
void playingUcg()
{
	if (strcmp(title,"STOPPED") == 0)
    {
        cleartitleUcg(3);
        separatorUcg(title);
    }
}

void lcd_initUcg(uint8_t *lcd_type)
{
	ESP_LOGI(TAG,"lcd init  type: %d",*lcd_type);
	
		ucg_esp32_hal_t ucg_esp32_hal = UCG_ESP32_HAL_DEFAULT;
		if (*lcd_type & LCD_SPI) // Color SPI
		{
			ucg_esp32_hal.clk   = PIN_NUM_CLK;
			ucg_esp32_hal.mosi  = PIN_NUM_MOSI;
			ucg_esp32_hal.cs    = PIN_LCD_CS;
			ucg_esp32_hal.dc    = PIN_LCD_A0;
			ucg_esp32_hal.reset = PIN_LCD_RST;
		} else //Color I2c
		{
			ucg_esp32_hal.sda  = PIN_I2C_SDA;
			ucg_esp32_hal.scl  = PIN_I2C_SCL;
			ucg_esp32_hal.reset = PIN_LCD_RST;
		}
		
		ucg_esp32_hal_init(ucg_esp32_hal);	
		
	switch (*lcd_type){		
// Color spi
	case LCD_SPI_SSD1351:	
		ucg_Init(&ucg, ucg_dev_ssd1351_18x128x128_ilsoft, ucg_ext_ssd1351_18, ucg_com_hal);
		break;
	case LCD_SPI_ST7735:
		ucg_Init(&ucg, ucg_dev_st7735_18x128x160, ucg_ext_st7735_18, ucg_com_hal);
		break;
	case LCD_SPI_ILI9341:
		ucg_Init(&ucg, ucg_dev_ili9341_18x240x320, ucg_ext_ili9341_18, ucg_com_hal);
		break;
	case LCD_SPI_ILI9163:
		ucg_Init(&ucg, ucg_dev_ili9163_18x128x128, ucg_ext_ili9163_18, ucg_com_hal);
		break;	
	case LCD_SPI_PCF8833:
		ucg_Init(&ucg, ucg_dev_pcf8833_16x132x132, ucg_ext_pcf8833_16, ucg_com_hal);
		break;	
	case LCD_SPI_SSD1331:
		ucg_Init(&ucg, ucg_dev_ssd1331_18x96x64_univision, ucg_ext_ssd1331_18, ucg_com_hal);
		break;	
	case LCD_SPI_SEPS225:
		ucg_Init(&ucg, ucg_dev_seps225_16x128x128_univision, ucg_ext_seps225_16, ucg_com_hal);
		break;	
	default: 
		ESP_LOGE(TAG,"lcd invalid type: %d",*lcd_type);
		return;
	}	
		
		ESP_LOGI(TAG,"lcd init Color type: %d",*lcd_type);
		// define prefered font rendering method (no text will be visibile, if this is missing 
		ucg_SetFontMode(&ucg, UCG_FONT_MODE_TRANSPARENT); 
		ucg_ClearScreen(&ucg);		
		ucg_SetRotate90(&ucg);
		ucg_SetFont(&ucg,ucg_font_6x13_tf);
		ucg_SetFontPosTop(&ucg);
		y = - ucg_GetFontDescent(&ucg)+ ucg_GetFontAscent(&ucg) +4; //interline
		yy = ucg_GetHeight(&ucg);
		x  = ucg_GetWidth(&ucg);
		z = 0; 
}

