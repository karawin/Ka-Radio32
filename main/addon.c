/******************************************************************************
 * 
 * Copyright 2017 karawin (http://www.karawin.fr)
 *
*******************************************************************************/

#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include "ClickEncoder.h"
#include "app_main.h"
#include "gpio.h"
#include "webclient.h"
#include "webserver.h"
#include "interface.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "addon.h"
#include "u8g2_esp32_hal.h"
#include <time.h>
#include "ntp.h"


#define TAG  "addon"

// nams <--> num of line
#define STATIONNAME 0
#define STATION1  1
#define STATION2  2
#define IP        3
#define GENRE     2
#define TITLE1    3
#define TITLE2    4

// second before time display in stop state
#define DTIDLE  60
#define BUFLEN  180
#define LINES	5


u8g2_t u8g2; // a structure which will contain all the data for one display
uint8_t lcd_type;
uint8_t lcd_family;
uint16_t y ;		//Height of a line
uint16_t yy;		//Height of screen
uint16_t x ;		//Width
uint16_t z ;		// an internal offset for y

// list of screen
typedef  enum typeScreen {smain,smain0,svolume,sstation,snumber,stime} typeScreen ;
typeScreen stateScreen = smain;
// state of the transient screen
uint8_t mTscreen = 1; // 0 dont display, 1 display full, 2 display variable part

uint8_t highlight=0;// index in sline of the highlighted station
char sline[BUFLEN] ; // station 
bool playable = true;

char* lline[LINES] ; // array of ptr of n lines 
uint8_t  iline[LINES] ; //array of index for scrolling
uint8_t  tline[LINES] ;

char nameNum[5] ; // the number of the current station
char futurNum[5] = {"0"}; // the number of the wanted station
char genre[BUFLEN/2]; // the local name of the station

unsigned timerScreen = 0;
unsigned timerScroll = 0;
unsigned timer1s = 0;

unsigned timein = 0;
struct tm *dt;
time_t timestamp = 0;
static bool syncTime = false;
static bool itAskTime = true; // update time with ntp if true
static bool itAskStime = false; // start the time display
static bool state = false; // start stop on Ok key

// svolume: display the volume
char aVolume[4] = {"0"}; 
// time string
char strsec[30]; 


 // ----------------------------------------------------------------------------
// call this every 1 millisecond via timer ISR
//
void (*serviceAddon)() = NULL;
void ServiceAddon(void)
{
	timer1s++;
	if (timer1s >=1000)
	{
		if (state) timein = 0; // only on stop state
         else timein++;
		 
		if (((timein % DTIDLE)==0)&&(!state)  ) {
            if ((timein % (30*DTIDLE))==0){ itAskTime=true;timein = 0;} // synchronise with ntp every x*DTIDLE
            if (stateScreen != stime) {itAskStime=true;} // start the time display
        } 
		
		
		timestamp++;  // time update  
		timer1s = 0;
	}
}

////////////////////////////////////////
// scroll each line
void scroll()
{
unsigned len;
	for (int i = 0;i < LINES;i++)
	{
	   if (tline[i]>0) 
	   {
	     if (tline[i] == 4) iline[i]= 0;
	     tline[i]--;		 
	   } 
	   else
	   {
       len = u8g2_GetStrWidth(&u8g2,lline[i]+iline[i]);
		   if (i == 0)	 len += u8g2_GetStrWidth(&u8g2,nameNum) ;
		   if (len > x) 
		    {iline[i]++;}
		   else 
			  tline[i] = 6;
	   }
	}	
}


////////////////////////////
// Change the current screen
////////////////////////////
void Screen(typeScreen st){
  if (stateScreen != st)
  {
#ifdef IR
// if a number is entered, play it.
    if (strlen(irStr) >0)
       playStation(irStr);
// clear the number       
    irStr[0] = 0;
#endif
  }
  else
    if (mTscreen == 0) mTscreen = 2;
  stateScreen = st;  
  timein = 0;
  mTscreen = 1;
}

/*
// Bottom of screens
void screenBottom()
{
//VOLUME
    u8g2_DrawFrame(&u8g2,0,yy-3,x-1,3);
    u8g2_DrawHLine(&u8g2,0,yy-2,((uint16_t)(x*volume)/255));                         
//TIME
//  if ((lline[4] == NULL)||(x==84))
    setFont(u8g_font_5x8);
    u8g2_DrawStr(&u8g2,x/2-(u8g2.getStrWidth(strsec)/2),yy-y-4,strsec);   
}
*/
/*
////////////////////////////////////////
// draw all lines
void drawFrame()
{
  dt=gmtime(&timestamp);
  if (x==84)
  sprintf(strsec,"%02d-%02d  %02d:%02d:%02d",dt->tm_mon,dt->tm_mday, dt->tm_hour, dt->tm_min,dt->tm_sec);
  else
  sprintf(strsec,"%02d-%02d-%04d  %02d:%02d:%02d",dt->tm_mon,dt->tm_mday,dt->tm_year+1900, dt->tm_hour, dt->tm_min,dt->tm_sec);
  if (u8g2.width() == 84)
    setFont(u8g_font_5x8);
  else 
    setFont(u8g_font_6x10);
  u8g2.setColorIndex(1); 

//    y = u8g2.getFontLineSpacing();
//    u8g2.setFontRefHeightText(); 
  
  do {
    u8g2.drawHLine(0,(4*y) - (y/2)-1,x);
    u8g2.drawBox(0,0,x-1,y);
    for (int i = 0;i < LINES;i++)
    {
      if (i == 0)u8g2.setColorIndex(0);
      else u8g2.setColorIndex(1);
      if (i >=3) z = y/2+2 ; else z = 1;
      if ((lline[i] != NULL))
      {
//Serial.print("Liney: ");Serial.println(y);  
        if (i == 0) 
        {       
          if (nameNum[0] ==0)  u8g2.drawStr(1,0,lline[i]+iline[i]);
          else 
          {
            u8g2.drawStr(1,0,nameNum);
            u8g2.drawStr(u8g2.getStrPixelWidth(nameNum)-2,0,lline[i]+iline[i]);
          }
        }      
        else u8g2.drawStr(0,y*i+z,lline[i]+iline[i]);
      }

    }
    screenBottom();    
  } while( u8g2_NextPage(&u8g2); );
   mTscreen = 0;
}

//////////////////////////
void drawTTitle(char* ttitle)
{
        setFont(u8g_font_9x15); 
        uint16_t xxx = (x/2)-(u8g2.getStrWidth(ttitle)/2);
        u8g2.setColorIndex(1);  
        u8g2.drawBox(0,0,x,u8g2.getFontLineSpacing()+1); 
        u8g2.setColorIndex(0);  
        u8g2.drawStr(xxx,1,ttitle);
        u8g2.setColorIndex(1);  
}
#ifdef IR
////////////////////
// draw the number entered from IR
void drawNumber()
{
  char ststr[] = {"Number"};
  if(mTscreen)
  {
     
     do {  
        drawTTitle(ststr);   
        uint16_t xxx ;
        xxx = (x/2)-(u8g2.getStrWidth(irStr)/2); 
        u8g2.drawStr(xxx,yy/3, irStr);        
        screenBottom();  
     } 
  }      
  mTscreen = 0;    
}
#endif
////////////////////
// draw the station screen
void drawStation()
{
  char ststr[] = {"Station"};
  char* ddot;
  int16_t len;
  if (mTscreen)
  { 
    ddot = strstr(sline,":");
    if (ddot != NULL)
    {
      *ddot=0; 
      char* ptl = sline+1;
Serial.print("Station: ");Serial.println(sline);        
      while ( *ptl == 0x20){*ptl = '0';ptl++;}
      ptl = ++ddot;
      while ( *ptl == 0x20){ddot++;ptl++;}
      if (strcmp(ddot,"not defined")==0) // don't start an undefined station
          playable = false; 
      else 
        playable = true;             
      strcpy (futurNum,sline+1);       
    }      
    
    do {  
        drawTTitle(ststr);        
        if (ddot != NULL)
        {
          u8g2.drawStr((x/2)-(u8g2.getStrWidth(sline+1)/2),yy/3, sline+1);
          len = (x/2)-(u8g2.getStrWidth(ddot)/2);
          if (len <0) len = 0;
          u8g2.drawStr(len,yy/3+y, ddot);
        }
        screenBottom();  
     }  
  }        
  mTscreen = 0;    
}
////////////////////
// draw the volume screen
void drawVolume()
{
  char vlstr[] = {"Volume"}; 
   if (mTscreen){
      
      do { 
        drawTTitle(vlstr) ;  
        uint16_t xxx;
        xxx = (x/2)-(u8g2.getStrWidth(aVolume)/2);     
        u8g2.drawStr(xxx,yy/3,aVolume);
        screenBottom();   
      }             
    }      
    mTscreen = 0; 
}

void drawTime()
{
  char strdate[23];
  char strtime[20];
  char strsec[3]; 
  unsigned len;
  if (mTscreen)
  {
    
    do {   
        dt=gmtime(&timestamp);
        sprintf(strdate,"%02d-%02d-%04d", dt->tm_mon, dt->tm_mday, dt->tm_year+1900);
        sprintf(strtime,"%02d:%02d:%02d", dt->tm_hour, dt->tm_min,dt->tm_sec);
        drawTTitle(strdate);            
        setFont(u8g_font_9x15);  
        u8g2.drawStr((x/2)-(u8g2.getStrWidth(strtime)/2),yy/3,strtime); 
        // draw ip
        setFont(u8g_font_5x8);
        eepromReadStr(EEaddrIp, strtime);
        sprintf(strdate,"IP: %s",strtime);
        len = u8g2.getStrWidth(strdate);
        u8g2.drawStr(4,yy-u8g2.getFontLineSpacing(),strdate);
    } 
  }        
  mTscreen = 0;       
}


////////////////////
// Display a screen on the lcd
void drawScreen()
{
  switch (stateScreen)
  {
    case smain0:  // force the draw of the complete screen
//      u8g2.clearScreen();
      drawFrame();
      stateScreen = smain;
      break;
    case svolume:
      drawVolume();
      break;
    case sstation:
      drawStation(); 
      break; 
    case stime:
      drawTime(); 
//      drawSecond();
      break;     
    case snumber:
#ifdef IR    
      drawNumber();
#endif      
      break;
    default: 
      drawFrame();       
  }
}
*/

void lcd_init(uint8_t Type)
{
	lcd_type = Type;
	if (lcd_type & LCD_COLOR) // Color one
	{
		lcd_family = LCD_COLOR;
	} else //B/W lcd
	if (lcd_type & LCD_SPI) // BW SPI
	{
		lcd_family = LCD_SPI;
		u8g2_esp32_hal_t u8g2_esp32_hal = U8G2_ESP32_HAL_DEFAULT;
		u8g2_esp32_hal.clk   = PIN_NUM_CLK;
		u8g2_esp32_hal.mosi  = PIN_NUM_MOSI;
		u8g2_esp32_hal.cs    = PIN_LCD_CS;
		u8g2_esp32_hal.dc    = PIN_LCD_A0;
		u8g2_esp32_hal.reset = PIN_LCD_RST;
		u8g2_esp32_hal_init(u8g2_esp32_hal);		
	} else //BW I2C
	{
		lcd_family = LCD_I2C;
		u8g2_esp32_hal_t u8g2_esp32_hal = U8G2_ESP32_HAL_DEFAULT;
		u8g2_esp32_hal.sda  = PIN_I2C_SDA;
		u8g2_esp32_hal.scl  = PIN_I2C_SCL;
		u8g2_esp32_hal_init(u8g2_esp32_hal);
	}
	
	switch (lcd_type){
	case LCD_I2C_SH1106:
		u8g2_Setup_sh1106_128x64_noname_f(
			&u8g2,
			U8G2_R0,
			u8g2_esp32_msg_i2c_cb,
			u8g2_esp32_msg_i2c_and_delay_cb);  // init u8g2 structure
		break;
	case LCD_I2C_SH1306:
		u8g2_Setup_sh1106_128x64_noname_f(
			&u8g2,
			U8G2_R0,
			u8g2_esp32_msg_i2c_cb,
			u8g2_esp32_msg_i2c_and_delay_cb);  // init u8g2 structure	
		break;		
	case LCD_I2C_SSD1309:	
		u8g2_Setup_ssd1309_128x64_noname2_f(
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
		ESP_LOGE(TAG,"Unknown lcd lcd_type %d. Fall back to type 0",lcd_type);
		lcd_type = 0;
		lcd_family = LCD_I2C;
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

	if (lcd_family != LCD_COLOR)
	{
		if (lcd_family == LCD_I2C) u8x8_SetI2CAddress(&u8g2.u8x8,0x78);
		u8g2_InitDisplay(&u8g2); // send init sequence to the display, display is in sleep mode after this,
		u8g2_SetPowerSave(&u8g2, 0); // wake up display
		u8g2_ClearBuffer(&u8g2);
		u8g2_ClearDisplay(&u8g2);
		u8g2_SetFontPosTop(&u8g2);
		yy = u8g2.height;
		x  = u8g2.width;
		u8g2_DrawXBMP( &u8g2,x/2-logo_width/2, yy/2-logo_height/2, logo_width, logo_height, logo_bits);
		u8g2_SendBuffer(&u8g2);
		z = 0; 
	} else
	{
		ESP_LOGE(TAG,"Not yet lcd_type %d",lcd_type);
	}

}


void task_addon(void *pvParams)
{
	
// Encoder	init
  enum modeStateEncoder { encVolume, encStation } ;
  //static enum modeStateEncoder stateEncoder = encVolume;
  int16_t newValue = 0;
  Button newButton = Open;
  static int16_t oldValue = 0;
  ClickEncoderInit(PIN_ENC_A, PIN_ENC_B, PIN_ENC_BTN);
  serviceEncoder = &service;	; // connect the 1ms interruption
  serviceAddon = &ServiceAddon;	; // connect the 1ms interruption
  
  //------
  // Init lcd
  // in app_main
  //  lcd_init();
//----------
	

	while (1)
	{
// Encoder loop		
		newValue = - getValue();
		newButton = getButton();
		if (newValue != 0) 
		{
		//    Serial.print("Encoder: ");Serial.println(newValue);
			// reset our accelerator
			if ((newValue >0)&&(oldValue<0)) oldValue = 0;
			if ((newValue <0)&&(oldValue>0)) oldValue = 0;
		}
		else
		{
			// lower accelerator 
			if (oldValue <0) oldValue++;
			if (oldValue >0) oldValue--;
		}
    
		if (getPinState() == getpinsActive())
		{    
			if (newValue > 0) wsStationNext();
			else if (newValue < 0) wsStationPrev();

		} else

		if (/*(stateScreen  != sstation)&&*/(newValue != 0))
		{    
			ESP_LOGD(TAG,"Enc value: %d, oldValue: %d,  incr volume: %d",newValue, oldValue,newValue+(oldValue*3));
			setRelVolume(newValue+(oldValue*3));
		} 		
		oldValue += newValue;
// end Encoder loop

//lcd
		if (itAskTime) // time to ntp. Don't do that in interrupt.
		{
			if (ntp_get_time(&dt) )
			{	
				timestamp = mktime(dt); 
				itAskTime = false;
				
			} else vTaskDelay(1000);
		}
		if (itAskStime) // time start the time display. Don't do that in interrupt.
		{    
			//Screen(stime);
			itAskStime = false;
		}

		vTaskDelay(10);
	}
	
	
	vTaskDelete( NULL ); 
}
