/******************************************************************************
 * 
 * Copyright 2017 karawin (http://www.karawin.fr)
 *
*******************************************************************************/

#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "u8g2_esp32_hal.h"
#include "addon.h"
#include "app_main.h"
#include "gpio.h"
#include <time.h>
#include "esp_log.h"
#include "logo.h"

#define TAG  "addonu8g2"

// nams <--> num of line
#define STATIONNAME 0
#define STATION1  1
#define STATION2  2
#define IP        3
#define GENRE     2
#define TITLE1    3
#define TITLE2    4
#define VOLUME    5
#define TIME      6

#define BUFLEN  256
#define LINES	5

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

////////////////////////////////////////
char* getNameNumU8g2()
{
	return nameNum;
}	

void setVolumeU8g2(uint16_t vol){ volume = vol;}

static uint8_t getFontLineSpacing()
{
	return (u8g2_GetAscent(&u8g2) - u8g2_GetDescent(&u8g2));
}
////////////////////////////////////////
// Clear all buffers and indexes
void clearAllU8g2()
{
      title[0] = 0;
      station[0]=0;
    for (int i=1;i<LINES;i++) {lline[i] = NULL;iline[i] = 0;tline[i] = 0;;mline[i]=1;}
}
////////////////////////////////////////
void cleartitleU8g2(uint8_t froml)
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

// Mark the lines to draw
void markDrawU8g2(int i)
{
  mline[i] = 1;
}


////////////////////////////////////////
// scroll each line
void scrollU8g2()
{
unsigned len;
	for (int i = 0;i < LINES;i++)
	{
	   if (tline[i]>0) 
	   {
	     if (tline[i] == 4) {iline[i]= 0;markDrawU8g2(i);}
	     tline[i]--;		 
	   } 
	   else
	   {
		   if ((lline[i] != NULL))
		   {
				len = u8g2_GetUTF8Width(&u8g2,lline[i]+iline[i]);
				if (i == 0)	 len += u8g2_GetUTF8Width(&u8g2,nameNum) ;
				if (len >= x-20) 
				{iline[i]++;markDrawU8g2(i);}
				else 
					tline[i] = 6;
		   }
	   }
	}
}

// Bottom of screens
static void screenBottomU8g2()
{
//VOLUME
    u8g2_DrawFrame(&u8g2,0,yy-3,x-1,3);
    u8g2_DrawHLine(&u8g2,0,yy-2,((uint16_t)(x*volume)/255));                         
//TIME
//  if ((lline[4] == NULL)||(x==84))
    u8g2_SetFont(&u8g2, u8g2_font_5x8_tf);
    u8g2_DrawUTF8(&u8g2,x/2-(u8g2_GetUTF8Width(&u8g2,strsec)/2),yy-y-4,strsec);  	
}

// draw the screen from buffer
void drawLinesU8g2()
{
u8g2_SendBuffer(&u8g2); 
}
////////////////////////////////////////
// draw all lines
void drawFrameU8g2(uint8_t mTscreen,struct tm *dt)
{
//  if (mTscreen == MTNEW) 
	  u8g2_ClearBuffer(&u8g2);
  if (x==84)
	sprintf(strsec,"%02d-%02d  %02d:%02d:%02d",dt->tm_mon+1,dt->tm_mday,dt->tm_hour, dt->tm_min,dt->tm_sec);
  else
	sprintf(strsec,"%02d-%02d-%04d  %02d:%02d:%02d",dt->tm_mon+1,dt->tm_mday,dt->tm_year+1900, dt->tm_hour, dt->tm_min,dt->tm_sec);
  if (u8g2.width == 84)
    u8g2_SetFont(&u8g2, u8g2_font_5x8_tf);
  else 
    u8g2_SetFont(&u8g2, u8g2_font_6x10_tf);
  
    u8g2_SetDrawColor(&u8g2, 1);
    y = getFontLineSpacing();
    u8g2_SetFontRefHeightText(&u8g2); 
//    if (mTscreen == MTNEW) 
	{
		u8g2_DrawHLine(&u8g2,0,(4*y) - (y/2)-1,x);
		u8g2_DrawBox(&u8g2,0,0,x-1,y);
	}
    for (int i = 0;i < LINES;i++)
    {
//	  if (mline[i])
	  {	  
		if (i == 0){
//			u8g2_DrawBox(&u8g2,0,0,x,y+1);
			u8g2_SetDrawColor(&u8g2, 0);
		}
		else {
//			u8g2_SetDrawColor(&u8g2, 0);
			if (i >=3) z = y/2+2 ; else z = 1;
//			u8g2_DrawBox(&u8g2,0,y*i+z,x,y*i+z+y);
			u8g2_SetDrawColor(&u8g2, 1);
		}
		
		if (lline[i] != NULL)
		{
			if (i == 0) 
			{       
				if (nameNum[0] ==0)  u8g2_DrawUTF8(&u8g2,1,0,lline[i]+iline[i]);
				else 
				{
					u8g2_DrawUTF8(&u8g2,1,0,nameNum);
					u8g2_DrawUTF8(&u8g2,u8g2_GetUTF8Width(&u8g2,nameNum)-2,0,lline[i]+iline[i]);
				}
			}      
			else u8g2_DrawUTF8(&u8g2,0,y*i+z,lline[i]+iline[i]);
		}
	  }

    }
    screenBottomU8g2();    
}


//////////////////////////
void drawTTitleU8g2(char* ttitle)
{ 
	u8g2_SetFont(&u8g2, u8g2_font_8x13B_tf);
    uint16_t xxx = (x/2)-(u8g2_GetUTF8Width(&u8g2,ttitle)/2);
    u8g2_SetDrawColor(&u8g2, 1);
    u8g2_DrawBox(&u8g2,0,0,x,getFontLineSpacing()+1); 
    u8g2_SetDrawColor(&u8g2, 0);
    u8g2_DrawUTF8(&u8g2,xxx,1,ttitle);
	u8g2_SetFont(&u8g2, u8g2_font_7x14_tf);
    u8g2_SetDrawColor(&u8g2, 1);
}
//////////////////////////
void drawNumberU8g2(uint8_t mTscreen,char* irStr)
{
  char ststr[] = {"Number"};
  u8g2_ClearBuffer(&u8g2);
  drawTTitleU8g2(ststr);   
  u8g2_SetFont(&u8g2, u8g2_font_ncenR18_tf );
  uint16_t xxx = (x/2)-(u8g2_GetUTF8Width(&u8g2,irStr)/2); 
  u8g2_DrawUTF8(&u8g2,xxx,yy/3, irStr);        
  screenBottomU8g2();  
}
//////////////////////////
void drawStationU8g2(uint8_t mTscreen,char* snum,char* ddot)
{
  int16_t len;
  char ststr[] = {"Station"};
  u8g2_ClearBuffer(&u8g2);
  drawTTitleU8g2(ststr);   
  if (ddot != NULL)
  {
        u8g2_DrawUTF8(&u8g2,(x/2)-(u8g2_GetUTF8Width(&u8g2,snum)/2),yy/3-2, snum);
        len = (x/2)-(u8g2_GetUTF8Width(&u8g2,ddot)/2);
        if (len <0) len = 0;
        u8g2_DrawUTF8(&u8g2,len,yy/3+4+y, ddot);
  }
  screenBottomU8g2(); 	
}


void drawVolumeU8g2(uint8_t mTscreen,char* aVolume)
{
  char vlstr[] = {"Volume"}; 
  volume = atoi(aVolume);
  u8g2_ClearBuffer(&u8g2);
  drawTTitleU8g2(vlstr) ;  
  u8g2_SetFont(&u8g2, u8g2_font_ncenR18_tf );	
  uint16_t xxx = (x/2)-(u8g2_GetUTF8Width(&u8g2,aVolume)/2);     
  u8g2_DrawUTF8(&u8g2,xxx,yy/3,aVolume);
  screenBottomU8g2(); 
}

void drawTimeU8g2(uint8_t mTscreen,struct tm *dt,unsigned timein)
{
  char strdate[23];
  char strtime[20];
	u8g2_ClearBuffer(&u8g2);
 //   dt=localtime(&timestamp);
    sprintf(strdate,"%02d-%02d-%04d", dt->tm_mon+1, dt->tm_mday, dt->tm_year+1900);
    sprintf(strtime,"%02d:%02d:%02d", dt->tm_hour, dt->tm_min,dt->tm_sec);
    drawTTitleU8g2(strdate); 
//u8g2_SetFont(&u8g2, u8g2_font_9x15_tf);		
	u8g2_SetFont(&u8g2, u8g2_font_ncenR18_tf );		
    u8g2_DrawUTF8(&u8g2,(x/2)-(u8g2_GetUTF8Width(&u8g2,strtime)/2),(yy/3)+4,strtime); 
    // draw ip
	u8g2_SetFont(&u8g2, u8g2_font_5x8_tf);
	sprintf(strdate,"IP: %s", getIp());
	u8g2_DrawUTF8(&u8g2,(x/2)-(u8g2_GetUTF8Width(&u8g2,strdate)/2),yy-getFontLineSpacing(),strdate);   
}


////////////////////////////////////////
void separatorU8g2(char* from)
{
    char* interp;
    while (from[strlen(from)-1] == ' ') from[strlen(from)-1] = 0; // avoid blank at end
    while ((from[0] == ' ') ){ strcpy( from,from+1); }
    interp=strstr(from," - ");
  if (from == nameset) {lline[0] = nameset;lline[1] = NULL;lline[2] = NULL;return;}
  if (interp != NULL)
  {
    from[interp-from]= 0;
    lline[(from==station)?1:3] = from;
    lline[(from==station)?2:4] = interp+3;
  } else
  {
    lline[(from==station)?1:3] = from;
  }
}

//cli.meta
void metaU8g2(char* ici)
{
     cleartitleU8g2(3); 
     strcpy(title,ici+7);    
     separatorU8g2(title); 	
}

//cli.icy4
void icy4U8g2(char* ici)
{
     strcpy(genre,ici+7);
     lline[2] = genre;
}
//cli.icy0
void icy0U8g2(char* ici)
{
      clearAllU8g2();
      if (strlen(ici+7) == 0) strcpy (station,nameset);
      else strcpy(station,ici+7);
      separatorU8g2(station);	
}

//cli.stopped or label
void statusU8g2(char* label)
{
     cleartitleU8g2(3);
     strcpy(title,label);
     lline[TITLE1] = title;	
}
//cli.nameset
void namesetU8g2(char* ici)
{
	strcpy(nameset,ici+8);
    ici = strstr(nameset," ");
    if (ici != NULL)
    {
       clearAllU8g2();
       strncpy(nameNum,nameset,ici-nameset+1);
       nameNum[ici - nameset+1] = 0; 
	   setFuturNum(atoi(nameNum));     
    }
    strcpy(nameset,nameset+strlen(nameNum));
    lline[STATIONNAME] = nameset;
}

// cli.playing
void playingU8g2()
{
	if (strcmp(title,"STOPPED") == 0)
    {
        cleartitleU8g2(3);
        separatorU8g2(title);
    }
}

void lcd_initU8g2(uint8_t *lcd_type)
{
		u8g2_esp32_hal_t u8g2_esp32_hal = U8G2_ESP32_HAL_DEFAULT;
		if (*lcd_type & LCD_SPI) // BW SPI
		{
			u8g2_esp32_hal.clk   = PIN_NUM_CLK;
			u8g2_esp32_hal.mosi  = PIN_NUM_MOSI;
			u8g2_esp32_hal.cs    = PIN_LCD_CS;
			u8g2_esp32_hal.dc    = PIN_LCD_A0;
			u8g2_esp32_hal.reset = PIN_LCD_RST;
		} else //BW I2C
		{
			u8g2_esp32_hal.sda  = PIN_I2C_SDA;
			u8g2_esp32_hal.scl  = PIN_I2C_SCL;
			u8g2_esp32_hal.reset = PIN_LCD_RST;
		}
		u8g2_esp32_hal_init(u8g2_esp32_hal);		
	
	
	switch (*lcd_type){
	case LCD_I2C_SH1106:
		u8g2_Setup_sh1106_128x64_noname_f(
			&u8g2,
			U8G2_R0,
			u8g2_esp32_msg_i2c_cb,
			u8g2_esp32_msg_i2c_and_delay_cb);  // init u8g2 structure
		break;
	case LCD_I2C_SSD1306NN:
		u8g2_Setup_ssd1306_128x64_noname_f(
			&u8g2,
			U8G2_R0,
			u8g2_esp32_msg_i2c_cb,
			u8g2_esp32_msg_i2c_and_delay_cb);  // init u8g2 structure	
		break;		
	case LCD_I2C_SSD1306:
		u8g2_Setup_ssd1306_128x64_vcomh0_f(
			&u8g2,
			U8G2_R0,
			u8g2_esp32_msg_i2c_cb,
			u8g2_esp32_msg_i2c_and_delay_cb);  // init u8g2 structure	
		break;		
	case LCD_I2C_SSD1309:	
		u8g2_Setup_ssd1309_i2c_128x64_noname2_f(
			&u8g2,
			U8G2_R0,
			u8g2_esp32_msg_i2c_cb,
			u8g2_esp32_msg_i2c_and_delay_cb);  // init u8g2 structure	
		break;	
	case LCD_I2C_SSD1325:	
		u8g2_Setup_ssd1325_nhd_128x64_f(
			&u8g2,
			U8G2_R0,
			u8g2_esp32_msg_i2c_cb,
			u8g2_esp32_msg_i2c_and_delay_cb);  // init u8g2 structure	
		break;	
	case LCD_I2C_SSD1309NN:	
		u8g2_Setup_ssd1309_i2c_128x64_noname0_f(
			&u8g2,
			U8G2_R0,
			u8g2_esp32_msg_i2c_cb,
			u8g2_esp32_msg_i2c_and_delay_cb);  // init u8g2 structure	
		break;			

//B/W spi
	case LCD_SPI_SSD1306NN:	
		u8g2_Setup_ssd1306_128x64_noname_f(
			&u8g2,
			U8G2_R0,
			u8g2_esp32_msg_comms_cb,
			u8g2_esp32_msg_gpio_and_delay_cb);  // init u8g2 structure	
		break;			
	case LCD_SPI_SSD1306:	
		u8g2_Setup_ssd1306_128x32_univision_f(
			&u8g2,
			U8G2_R0,
			u8g2_esp32_msg_comms_cb,
			u8g2_esp32_msg_gpio_and_delay_cb);  // init u8g2 structure	
		break;	
	case LCD_SPI_SSD1309:	
		u8g2_Setup_ssd1309_128x64_noname2_f(
			&u8g2,
			U8G2_R0,
			u8g2_esp32_msg_comms_cb,
			u8g2_esp32_msg_gpio_and_delay_cb);  // init u8g2 structure	
		break;	
	case LCD_SPI_SSD1309NN:
		u8g2_Setup_ssd1309_128x64_noname0_f(
			&u8g2,
			U8G2_R0,
			u8g2_esp32_msg_comms_cb,
			u8g2_esp32_msg_gpio_and_delay_cb);  // init u8g2 structure	
		break;		
	case LCD_SPI_ST7565_ZOLEN:	
		u8g2_Setup_st7565_zolen_128x64_f(
			&u8g2,
			U8G2_R0,
			u8g2_esp32_msg_comms_cb,
			u8g2_esp32_msg_gpio_and_delay_cb);  // init u8g2 structure	
		break;		
	case LCD_SPI_SSD1322_NHD:	
		u8g2_Setup_ssd1322_nhd_256x64_f(
			&u8g2,
			U8G2_R0,
			u8g2_esp32_msg_comms_cb,
			u8g2_esp32_msg_gpio_and_delay_cb);  // init u8g2 structure	
		break;	
	case LCD_SPI_IL3820_V2:	//E Paper
		u8g2_Setup_il3820_v2_296x128_f(
			&u8g2,
			U8G2_R0,
			u8g2_esp32_msg_comms_cb,
			u8g2_esp32_msg_gpio_and_delay_cb);  // init u8g2 structure	
		break;	
	case LCD_SPI_SSD1607:	//E Paper
		u8g2_Setup_ssd1607_200x200_f(
			&u8g2,
			U8G2_R0,
			u8g2_esp32_msg_comms_cb,
			u8g2_esp32_msg_gpio_and_delay_cb);  // init u8g2 structure	
		break;	
	case LCD_SPI_LS013B7DH03:	
		u8g2_Setup_ls013b7dh03_128x128_f(
			&u8g2,
			U8G2_R0,
			u8g2_esp32_msg_comms_cb,
			u8g2_esp32_msg_gpio_and_delay_cb);  // init u8g2 structure	
		break;	
	default:
		ESP_LOGE(TAG,"Unknown lcd lcd_type %d. Fall back to type 0",*lcd_type);
		*lcd_type = 0;
		u8g2_esp32_hal_t u8g2_esp32_hal = U8G2_ESP32_HAL_DEFAULT;
		u8g2_esp32_hal.sda  = PIN_I2C_SDA;
		u8g2_esp32_hal.scl  = PIN_I2C_SCL;
		u8g2_esp32_hal_init(u8g2_esp32_hal);
		u8g2_Setup_sh1106_128x64_noname_f(
			&u8g2,
			U8G2_R0,
			u8g2_esp32_msg_i2c_cb,
			u8g2_esp32_msg_i2c_and_delay_cb);  // init u8g2 structure	
	}
	
		ESP_LOGD(TAG,"lcd init BW type: %d",*lcd_type);
		if (*lcd_type < LCD_SPI) u8x8_SetI2CAddress(&u8g2.u8x8,0x78);
		u8g2_InitDisplay(&u8g2); // send init sequence to the display, display is in sleep mode after this,
		u8g2_SetPowerSave(&u8g2, 0); // wake up display
		u8g2_ClearBuffer(&u8g2);
		u8g2_ClearDisplay(&u8g2);
		yy = u8g2.height;
		x  = u8g2.width;
		z = 0;
		u8g2_SetFontPosTop(&u8g2);
		if (x == 84) u8g2_SetFont(&u8g2, u8g2_font_5x8_tf);
		else u8g2_SetFont(&u8g2, u8g2_font_6x10_tf);
		y = getFontLineSpacing();
		u8g2_DrawXBM( &u8g2,x/2-logo_width/2, yy/2-logo_height/2, logo_width, logo_height, logo_bits);
		u8g2_SendBuffer(&u8g2);
		vTaskDelay(100);
		z = 0; 	
	
	
}

