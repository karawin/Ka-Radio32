/******************************************************************************
 * 
 * Copyright 2018 karawin (http://www.karawin.fr)
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
#include "interface.h"
#include "eeprom.h"
#include "addoncommon.h"
/*==========================================*/
//#include "u8g2-karadio32_fonts.h"
extern const uint8_t u8g2_font_4x6_t_latcyr[] U8G2_FONT_SECTION("u8g2_font_4x6_t_latcyr");
extern const uint8_t u8g2_font_5x7_t_latcyr[] U8G2_FONT_SECTION("u8g2_font_5x7_t_latcyr");
extern const uint8_t u8g2_font_5x8_t_latcyr[] U8G2_FONT_SECTION("u8g2_font_5x8_t_latcyr");
extern const uint8_t u8g2_font_6x12_t_latcyr[] U8G2_FONT_SECTION("u8g2_font_6x12_t_latcyr");
extern const uint8_t u8g2_font_6x13_t_latcyr[] U8G2_FONT_SECTION("u8g2_font_6x13_t_latcyr");
extern const uint8_t u8g2_font_7x13_t_latcyr[] U8G2_FONT_SECTION("u8g2_font_7x13_t_latcyr");
extern const uint8_t u8g2_font_8x13_t_latcyr[] U8G2_FONT_SECTION("u8g2_font_8x13_t_latcyr");
extern const uint8_t u8g2_font_9x15_t_latcyr[] U8G2_FONT_SECTION("u8g2_font_9x15_t_latcyr");
extern const uint8_t u8g2_font_10x20_t_latcyr[] U8G2_FONT_SECTION("u8g2_font_10x20_t_latcyr");
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

#undef LINES
#define LINES	5


////////////////////////////////////////
typedef enum sizefont  {small, text,middle,large} sizefont;
void setfont8(sizefont size)
{
//	printf("setfont8 size: %d, yy: %d\n",size,yy);
	switch(size)
	{
		case small:
		switch(yy)
		{
			case 200:
			u8g2_SetFont(&u8g2,u8g2_font_6x12_t_latcyr);
			break;
			case 128:
			u8g2_SetFont(&u8g2,u8g2_font_6x12_t_latcyr);
			break;
			case 32:
			u8g2_SetFont(&u8g2,u8g2_font_4x6_t_latcyr);
			break;
			case 64:
			default: // 
			u8g2_SetFont(&u8g2, u8g2_font_5x8_t_latcyr);
			;
		}
		break;
		case text:
		switch(yy)
		{
			/*
			case 200:
			charset?u8g2_SetFont(&u8g2,u8g2_font_7x13_t_cyrillic):u8g2_SetFont(&u8g2,u8g2_font_7x14_tf);//
			break;
			case 128:
			charset?u8g2_SetFont(&u8g2,u8g2_font_7x13_t_cyrillic):u8g2_SetFont(&u8g2, u8g2_font_7x14_tf);//
			break;
			case 32:
			charset?u8g2_SetFont(&u8g2,u8g2_font_5x7_t_cyrillic):u8g2_SetFont(&u8g2,u8g2_font_5x7_tf);//
			break;
			case 64:
			default: // 
			charset?u8g2_SetFont(&u8g2, u8g2_font_haxrcorp4089_t_cyrillic ):u8g2_SetFont(&u8g2, u8g2_font_6x12_tf);
			*/
			case 200:
			u8g2_SetFont(&u8g2, u8g2_font_7x13_t_latcyr);//
			break;
			case 128:
			u8g2_SetFont(&u8g2, u8g2_font_7x13_t_latcyr);//
			break;
			case 32:
			u8g2_SetFont(&u8g2, u8g2_font_5x7_t_latcyr);//
			break;
			case 64:
			default: // 
			u8g2_SetFont(&u8g2, u8g2_font_6x12_t_latcyr);
		}
		break;
		case middle:
		switch(yy)
		{
			case 200:
			u8g2_SetFont(&u8g2, u8g2_font_9x15_t_latcyr);
			break;
			case 128:
			u8g2_SetFont(&u8g2, u8g2_font_9x15_t_latcyr);
			break;
			case 32:
			u8g2_SetFont(&u8g2, u8g2_font_5x8_t_latcyr);
			break;
			case 64:
			default: // 
			u8g2_SetFont(&u8g2, u8g2_font_7x13_t_latcyr);
			;			

		}
		break;
		case large:
		switch(yy)
		{
			case 200:
			u8g2_SetFont(&u8g2, u8g2_font_10x20_t_latcyr);
			break;
			case 128:
			if (x == 296)
				u8g2_SetFont(&u8g2, u8g2_font_inr46_mn );
			else
				u8g2_SetFont(&u8g2, u8g2_font_10x20_t_latcyr);
			break;
			case 32:
			u8g2_SetFont(&u8g2,  u8g2_font_8x13_t_latcyr);
			break;
			case 64:
			default: // 
			u8g2_SetFont(&u8g2, u8g2_font_10x20_t_latcyr);
			;		
		}
		break;
		default:
		ESP_LOGE(TAG,"Default for size %d",size);
	}
}




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
void markDrawResetU8g2(int i)
{
  mline[i] = 1;
  iline[i] = 0;
  tline[i] = 0;
}

////////////////////////////////////////
// scroll each line
void scrollU8g2()
{
unsigned len ;
	setfont8(text);
	for (int i = 0;i < LINES;i++)
	{
	   if (tline[i]>0) 
	   {
	     if (tline[i] == 4) {iline[i]= 0;
		 mline[i] = 1;;}
	     tline[i]--;		 
	   } 
	   else
	   {
		   if ((lline[i] != NULL))
		   {
				len = u8g2_GetUTF8Width(&u8g2,lline[i]+iline[i]);
				if (i == 0)	 len += u8g2_GetUTF8Width(&u8g2,nameNum);
				if (len >= x) 
				{
					iline[i]++;
					//Max
					while (((*(lline[i]+iline[i])) & 0xc0) == 0x80) {
						iline[i]++;
					}
					mline[i] = 1;;
				}
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
	if (yy != 32) // not enough room
	{
		char strsec[30]; 		
		if (getDdmm())
			sprintf(strsec,"%02d-%02d-%04d  %02d:%02d:%02d",dt->tm_mday,dt->tm_mon+1,dt->tm_year+1900, dt->tm_hour, dt->tm_min,dt->tm_sec);
		else 
			sprintf(strsec,"%02d-%02d-%04d  %02d:%02d:%02d",dt->tm_mon+1,dt->tm_mday,dt->tm_year+1900, dt->tm_hour, dt->tm_min,dt->tm_sec);	
		setfont8(small);
		u8g2_DrawUTF8(&u8g2,x/2-(u8g2_GetUTF8Width(&u8g2,strsec)/2),yy-y-3,strsec);  
	}	
}

// draw the screen from buffer
void drawLinesU8g2()
{
//u8g2_SendBuffer(&u8g2); 
}


//Thanks to Max
void eraseSlashes(char * str) {
	//Symbols: \" \' \\ \? \/
	char * sym = str, * sym1;
	if (str != NULL) {
		while (*sym != 0) {
			if (*sym == 0x5c) {
				sym1 = sym + 1;
				if (*sym1 == 0x22 || *sym1 == 0x27 || *sym1 == 0x5c || *sym1 == 0x3f || *sym1 == 0x2f) {
					*sym = 0x1f; //Erase \ to non-printable symbol
					sym++;
				}	
			} 
			sym++;
		}
	} 	
}
//-Max


////////////////////////////////////////
// draw all lines
void drawFrameU8g2(uint8_t mTscreen)
{
	if (dt == NULL) {dt = getDt();}
	u8g2_ClearBuffer(&u8g2);
	u8g2_FirstPage(&u8g2);
	do {	
		setfont8(text);
		u8g2_SetDrawColor(&u8g2, 1);
		y = getFontLineSpacing();
		u8g2_SetFontRefHeightText(&u8g2); 
		{
			u8g2_DrawHLine(&u8g2,0,((yy==32)?3:4*y) - (y/2)-1,x);
			u8g2_DrawBox(&u8g2,0,0,x-1,y);
		}
		for (int i = 0;i < LINES;i++)
		{
			if (i == 0){
				u8g2_SetDrawColor(&u8g2, 0);
			}
			else {
				if (i >=3) z = y/2+2 ; else z = 1;
				u8g2_SetDrawColor(&u8g2, 1);
			}		
			int zz = y*i;
			if (yy==32)
			{
				if ((i==STATION2)||(i==TITLE2)) continue;
				if (i==TITLE1) zz = y*GENRE;
			}		
			if (lline[i] != NULL)
			{
				//Max
				eraseSlashes(lline[i]);
				if (i == 0) 
				{      
//					printf("DRAW: len= %d,STR= %s\n",u8g2_GetUTF8Width(&u8g2,lline[i]+iline[i]),lline[i]+iline[i]);		
					if (nameNum[0] ==0)  u8g2_DrawUTF8(&u8g2,1,0,lline[i]+iline[i]);
					else 
					{
						u8g2_DrawUTF8(&u8g2,1,0,nameNum);
						u8g2_DrawUTF8(&u8g2,u8g2_GetUTF8Width(&u8g2,nameNum)-1,0,lline[i]+iline[i]);
					}
				}      
				else u8g2_DrawUTF8(&u8g2,0,zz+z,lline[i]+iline[i]);
			}
			vTaskDelay(1);
		}
		screenBottomU8g2();
	} while ( u8g2_NextPage(&u8g2) );	   
}


//////////////////////////
void drawTTitleU8g2(char* ttitle)
{ 
  char strIp[23];
	setfont8(middle);
    uint16_t xxx = (x/2)-(u8g2_GetUTF8Width(&u8g2,ttitle)/2);
    u8g2_SetDrawColor(&u8g2, 1);
    u8g2_DrawBox(&u8g2,0,0,x,getFontLineSpacing()+1); 
    u8g2_SetDrawColor(&u8g2, 0);
    u8g2_DrawUTF8(&u8g2,xxx,1,ttitle);	
    u8g2_SetDrawColor(&u8g2, 1);
	
    // draw ip 
	setfont8(small);
	sprintf(strIp,"IP: %s", getIp());
//	u8g2_DrawUTF8(&u8g2,(x/2)-(u8g2_GetUTF8Width(&u8g2,strIp)/2),yy-getFontLineSpacing(),strIp);
	u8g2_DrawUTF8(&u8g2,(x/2)-(u8g2_GetUTF8Width(&u8g2,strIp)/2),yy-(2*getFontLineSpacing()),strIp);
	// Rssi
	sprintf(strIp,"%d dBm", get_rssi());
	u8g2_DrawUTF8(&u8g2,4,yy-(getFontLineSpacing()),strIp);
	
	// Battery
	if (getBatPercent() != -1)
	{	
		sprintf(strIp,"Batt: %d%%",getBatPercent());
		uint16_t len = u8g2_GetUTF8Width(&u8g2,strIp);
		u8g2_DrawUTF8(&u8g2,x-len-8,yy-(getFontLineSpacing()),strIp); 
	}
	
}
//////////////////////////
void drawNumberU8g2(uint8_t mTscreen,char* irStr)
{
  char ststr[] = {"Number"};
  u8g2_ClearBuffer(&u8g2);
  u8g2_FirstPage(&u8g2);
  do {	
	drawTTitleU8g2(ststr);   
	setfont8(large);
	uint16_t xxx = (x/2)-(u8g2_GetUTF8Width(&u8g2,irStr)/2); 
	u8g2_DrawUTF8(&u8g2,xxx,yy/3, irStr); 
	vTaskDelay(1);
  } while ( u8g2_NextPage(&u8g2) );	     
}
//////////////////////////
void drawStationU8g2(uint8_t mTscreen,char* snum,char* ddot)
{
  int16_t len;
  char ststr[] = {"Station"};
  u8g2_ClearBuffer(&u8g2);
  u8g2_FirstPage(&u8g2);
  do {	
	drawTTitleU8g2(ststr);   
	if (ddot != NULL)
	{
		setfont8(middle);
		u8g2_DrawUTF8(&u8g2,(x/2)-(u8g2_GetUTF8Width(&u8g2,snum)/2),yy/3-2, snum);
		len = (x/2)-(u8g2_GetUTF8Width(&u8g2,ddot)/2);
		if (len <0) len = 0;
        u8g2_DrawUTF8(&u8g2,len,yy/3+4+y, ddot);
		vTaskDelay(1);
	}	
  } while ( u8g2_NextPage(&u8g2) );	     
}


//void drawVolumeU8g2(uint8_t mTscreen,char* aVolume)
void drawVolumeU8g2(uint8_t mTscreen)
{
  char vlstr[] = {"Volume"}; 
  char aVolume[4];
//  volume = atoi(aVolume);
  sprintf(aVolume,"%d",volume);
  
  u8g2_ClearBuffer(&u8g2);
  u8g2_FirstPage(&u8g2);
  do {	
	drawTTitleU8g2(vlstr) ;  
	setfont8(large);  
	uint16_t xxx = (x/2)-(u8g2_GetUTF8Width(&u8g2,aVolume)/2);     
	u8g2_DrawUTF8(&u8g2,xxx,(yy/3)+6,aVolume);
	vTaskDelay(1);
  } while ( u8g2_NextPage(&u8g2) );	     
}

void drawTimeU8g2(uint8_t mTscreen,unsigned timein)
{
  char strdate[23];
  char strtime[20];
//  printf("DRAW TIME U8G2  mtscreen : %d\n",mTscreen);
	u8g2_ClearBuffer(&u8g2);
  u8g2_FirstPage(&u8g2);
  do {	
	if (getDdmm())
		sprintf(strdate,"%02d-%02d-%04d", dt->tm_mday, dt->tm_mon+1,  dt->tm_year+1900);
    else
		sprintf(strdate,"%02d-%02d-%04d", dt->tm_mon+1, dt->tm_mday, dt->tm_year+1900);
    sprintf(strtime,"%02d:%02d:%02d", dt->tm_hour, dt->tm_min,dt->tm_sec);
    drawTTitleU8g2(strdate); 
    setfont8(large);	
    u8g2_DrawUTF8(&u8g2,(x/2)-(u8g2_GetUTF8Width(&u8g2,strtime)/2),(yy/3)+4,strtime); 
	vTaskDelay(1);
  } while ( u8g2_NextPage(&u8g2) );	     
}


////////////////////////////////////////
void separatorU8g2(char* from)
{
    char* interp;
    while (from[strlen(from)-1] == ' ') from[strlen(from)-1] = 0; // avoid blank at end
    while ((from[0] == ' ') ){ strcpy( from,from+1); }
    interp=strstr(from," - ");
  if (from == nameset) {lline[0] = nameset;lline[1] = NULL;lline[2] = NULL;return;}
  if ((interp != NULL) &&  (yy != 32)) 
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
	char newstation[BUFLEN];
	 //move the STATION2 to STATION1S
	 if ((station!= NULL)&& (lline[STATION2] != NULL))
	 {  strcpy(newstation,lline[STATION1]);strcat(newstation," - ");  strcat(newstation,lline[STATION2]);
		strcpy(lline[STATION1],newstation);
		markDrawResetU8g2(STATION1);
	 }
	 
     strcpy(genre,ici+7);
     lline[GENRE] = genre;
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
void statusU8g2( const char* label)
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
	char nameseti[BUFLEN];
	strcpy(nameseti,nameset+strlen(nameNum));
    strcpy(nameset,nameseti);
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
	const u8g2_cb_t *rotat;
	
	uint8_t spi_no;
	gpio_num_t miso;
	gpio_num_t mosi;
	gpio_num_t sclk;
	gpio_num_t scl;
	gpio_num_t sda;
	gpio_num_t rsti2c;
	gpio_num_t cs;
	gpio_num_t a0;
	gpio_num_t rstlcd;
	
	if (*lcd_type == LCD_NONE) return;
	
	u8g2_esp32_hal_t u8g2_esp32_hal = U8G2_ESP32_HAL_DEFAULT;
	if (*lcd_type & LCD_SPI) // BW SPI
	{
		gpio_get_spi_bus(&spi_no,&miso,&mosi,&sclk);
		gpio_get_spi_lcd(&cs ,&a0,&rstlcd);
		u8g2_esp32_hal.spi_no   = spi_no;
		u8g2_esp32_hal.clk   = sclk;
		u8g2_esp32_hal.mosi  = mosi;
		u8g2_esp32_hal.cs    = cs;
		u8g2_esp32_hal.dc    = a0;
		u8g2_esp32_hal.reset = rstlcd;
	} else //BW I2C
	{
		gpio_get_i2c(&scl,&sda,&rsti2c);
		u8g2_esp32_hal.sda  = sda;
		u8g2_esp32_hal.scl  = scl;
		u8g2_esp32_hal.reset = rsti2c;
		if ((sda == GPIO_NONE)||(scl == GPIO_NONE)) {*lcd_type = LCD_NONE; return;}
	}
	u8g2_esp32_hal_init(u8g2_esp32_hal);		
	
	if (getRotat())
		rotat = U8G2_R2;
	else
		rotat = U8G2_R0;
	
	switch (*lcd_type){
	case LCD_I2C_SH1106:
		u8g2_Setup_sh1106_i2c_128x64_noname_2(
			&u8g2,
			rotat,
			u8g2_esp32_i2c_byte_cb,
			u8g2_esp32_gpio_and_delay_cb); // init u8g2 structure
		break;
	case LCD_I2C_SSD1306NN:
		u8g2_Setup_ssd1306_i2c_128x64_noname_2(
			&u8g2,
			rotat,
			u8g2_esp32_i2c_byte_cb,
			u8g2_esp32_gpio_and_delay_cb); // init u8g2 structure
		break;		
	case LCD_I2C_SSD1306:
		u8g2_Setup_ssd1306_i2c_128x64_vcomh0_2(
			&u8g2,
			rotat,
			u8g2_esp32_i2c_byte_cb,
			u8g2_esp32_gpio_and_delay_cb); // init u8g2 structure
		break;		
	case LCD_I2C_SSD1309:	
		u8g2_Setup_ssd1309_i2c_128x64_noname2_2(
			&u8g2,
			rotat,
			u8g2_esp32_i2c_byte_cb,
			u8g2_esp32_gpio_and_delay_cb); // init u8g2 structure
		break;	
	case LCD_I2C_SSD1325:	
		u8g2_Setup_ssd1325_i2c_nhd_128x64_2(
			&u8g2,
			rotat,
			u8g2_esp32_i2c_byte_cb,
			u8g2_esp32_gpio_and_delay_cb); // init u8g2 structure

		break;	
	case LCD_I2C_SSD1309NN:	
		u8g2_Setup_ssd1309_i2c_128x64_noname0_2(
			&u8g2,
			rotat,
			u8g2_esp32_i2c_byte_cb,
			u8g2_esp32_gpio_and_delay_cb); // init u8g2 structure
		break;		
	case LCD_I2C_SSD1306UN:
		u8g2_Setup_ssd1306_i2c_128x32_univision_2(
			&u8g2,
			rotat,
			u8g2_esp32_i2c_byte_cb,
			u8g2_esp32_gpio_and_delay_cb); // init u8g2 structure
		break;
	case LCD_I2C_ST7567:
		u8g2_Setup_st7567_i2c_64x32_2(
			&u8g2,
			rotat,
			u8g2_esp32_i2c_byte_cb,
			u8g2_esp32_gpio_and_delay_cb); // init u8g2 structure
		break;
//B/W spi
	case LCD_SPI_SSD1306NN:	
		u8g2_Setup_ssd1306_128x64_noname_2(
			&u8g2,
			rotat,
			u8g2_esp32_spi_byte_cb,
			u8g2_esp32_gpio_and_delay_cb); // init u8g2 structure			
		break;			
	case LCD_SPI_SSD1306:	
		u8g2_Setup_ssd1306_128x32_univision_2(
			&u8g2,
			rotat,
			u8g2_esp32_spi_byte_cb,
			u8g2_esp32_gpio_and_delay_cb); // init u8g2 structure			
		break;	
	case LCD_SPI_SSD1309:	
		u8g2_Setup_ssd1309_128x64_noname2_2(
			&u8g2,
			rotat,
			u8g2_esp32_spi_byte_cb,
			u8g2_esp32_gpio_and_delay_cb); // init u8g2 structure			
		break;	
	case LCD_SPI_SSD1309NN:
		u8g2_Setup_ssd1309_128x64_noname0_2(
			&u8g2,
			rotat,
			u8g2_esp32_spi_byte_cb,
			u8g2_esp32_gpio_and_delay_cb); // init u8g2 structure			
		break;		
	case LCD_SPI_ST7565_ZOLEN:	
		u8g2_Setup_st7565_zolen_128x64_2(
			&u8g2,
			rotat,
			u8g2_esp32_spi_byte_cb,
			u8g2_esp32_gpio_and_delay_cb); // init u8g2 structure			
		break;		
	case LCD_SPI_SSD1322_NHD:	
		u8g2_Setup_ssd1322_nhd_256x64_2(
			&u8g2,
			rotat,
			u8g2_esp32_spi_byte_cb,
			u8g2_esp32_gpio_and_delay_cb); // init u8g2 structure			
		break;	
	case LCD_SPI_IL3820_V2:	//E Paper
		u8g2_Setup_il3820_v2_296x128_2(
			&u8g2,
			rotat,
			u8g2_esp32_spi_byte_cb,
			u8g2_esp32_gpio_and_delay_cb); // init u8g2 structure			
		break;	
	case LCD_SPI_SSD1607:	//E Paper
		u8g2_Setup_ssd1607_200x200_2(
			&u8g2,
			rotat,
			u8g2_esp32_spi_byte_cb,
			u8g2_esp32_gpio_and_delay_cb); // init u8g2 structure			
		break;	
	case LCD_SPI_LS013B7DH03:	
		u8g2_Setup_ls013b7dh03_128x128_2(
			&u8g2,
			rotat,
			u8g2_esp32_spi_byte_cb,
			u8g2_esp32_gpio_and_delay_cb); // init u8g2 structure			
		break;	
	case LCD_SPI_ST7920:	
		u8g2_Setup_st7920_s_128x64_2(
			&u8g2,
			rotat,
			u8g2_esp32_spi_byte_cb,
			u8g2_esp32_gpio_and_delay_cb); // init u8g2 structure			
		break;
	case LCD_SPI_ST7565_NHD_C12864:	
		u8g2_Setup_st7565_nhd_c12864_2(
			&u8g2,
			rotat,
			u8g2_esp32_spi_byte_cb,
			u8g2_esp32_gpio_and_delay_cb); // init u8g2 structure			
		break;	case LCD_SPI_ST7567_pi:	
		u8g2_Setup_st7567_pi_132x64_2(
			&u8g2,
			rotat,
			u8g2_esp32_spi_byte_cb,
			u8g2_esp32_gpio_and_delay_cb); // init u8g2 structure			
		break;
	case LCD_SPI_ST7567:	
		u8g2_Setup_st7567_64x32_2(
			&u8g2,
			rotat,
			u8g2_esp32_spi_byte_cb,
			u8g2_esp32_gpio_and_delay_cb); // init u8g2 structure			
		break;		
	case LCD_SPI_ST7565_64128N:
		u8g2_Setup_st7565_64128n_2(
			&u8g2,
			rotat,
			u8g2_esp32_spi_byte_cb,
			u8g2_esp32_gpio_and_delay_cb); // init u8g2 structure			
		break;

		default:
		ESP_LOGE(TAG,"UNKNOWN LCD lcd_type %d. Fall back to type \"LCD_NONE\"",*lcd_type);
		*lcd_type = LCD_NONE;
/*		u8g2_esp32_hal_t u8g2_esp32_hal = U8G2_ESP32_HAL_DEFAULT;
		u8g2_esp32_hal.sda  = sda;
		u8g2_esp32_hal.scl  = scl;
		u8g2_esp32_hal_init(u8g2_esp32_hal);
		u8g2_Setup_sh1106_128x64_noname_2(
			&u8g2,
			rotat,
			u8g2_esp32_i2c_byte_cb,
			u8g2_esp32_gpio_and_delay_cb); // init u8g2 structure
*/			
	}
	if (*lcd_type != LCD_NONE)
	{
		ESP_LOGD(TAG,"lcd init BW type: %d",*lcd_type);
		if (*lcd_type < LCD_SPI) u8x8_SetI2CAddress(&u8g2.u8x8,0x78);
		u8g2_InitDisplay(&u8g2); // send init sequence to the display, display is in sleep mode after this,
		u8g2_SetPowerSave(&u8g2, 0); // wake up display
		u8g2_ClearBuffer(&u8g2);
		u8g2_ClearDisplay(&u8g2);
		yy = u8g2.height;
		x  = u8g2.width;
		z = 0;
  u8g2_FirstPage(&u8g2);
  do {	
		u8g2_SetFontPosTop(&u8g2);
		setfont8(text);
		y = getFontLineSpacing();
		if (yy>= logo_height)
			 u8g2_DrawXBM( &u8g2,x/2-logo_width/2, yy/2-logo_height/2, logo_width, logo_height, logo_bits);
		else u8g2_DrawXBM( &u8g2,x/2-logo_width/2, 0, logo_width, logo_height, logo_bits);
 } while ( u8g2_NextPage(&u8g2) );	    
// u8g2_SendBuffer(&u8g2);
		ESP_LOGI(TAG,"X: %d, YY: %d, Y: %d\n",x,yy,y);
		vTaskDelay(100);
//		z = 0; 	
	}
}

