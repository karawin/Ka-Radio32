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

#include "addon.h"
#include "u8g2_esp32_hal.h"
#include <time.h>
#include "ntp.h"
#include "logo.h"
#include "eeprom.h"


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

char irStr[4];
xQueueHandle event_ir;
u8g2_t u8g2; // a structure which will contain all the data for one display
static uint8_t lcd_type;
static uint8_t lcd_family;
static uint16_t y ;		//Height of a line
static uint16_t yy;		//Height of screen
static uint16_t x ;		//Width
static uint16_t z ;		// an internal offset for y

// list of screen
typedef  enum typeScreen {smain,svolume,sstation,snumber,stime} typeScreen ;
//typeScreen stateScreen = smain0;
static typeScreen stateScreen = smain;
// state of the transient screen
static uint8_t mTscreen = 0; // 0 dont display, 1 display full, 2 display variable part

//static uint8_t highlight=0;// index in sline of the highlighted station

static char sline[BUFLEN] ; // station 
static char station[BUFLEN]; //received station
static char title[BUFLEN];	// received title
static char nameset[BUFLEN/2]; // the local name of the station
static bool playable = true;
static uint16_t volume;
static char* lline[LINES] ; // array of ptr of n lines 
static uint8_t  iline[LINES] ; //array of index for scrolling
static uint8_t  tline[LINES] ;

static char nameNum[5] ; // the number of the current station
static int16_t futurNum = 0; // the number of the wanted station
static char genre[BUFLEN/2]; // the local name of the station

static unsigned timerScreen = 0;
static unsigned timerScroll = 0;
static unsigned timer1s = 0;

static unsigned timein = 0;
static struct tm *dt;
time_t timestamp = 0;
static bool syncTime = false;
static bool itAskTime = true; // update time with ntp if true
static bool itAskStime = false; // start the time display
//static bool itAskSsecond = false; // start the time display
static bool state = false; // start stop on Ok key

// svolume: display the volume
static char aVolume[4] = {"0"}; 
// time string
static char strsec[30]; 

static int16_t newValue = 0;
static int16_t currentValue = 0;
  


 // ----------------------------------------------------------------------------
// call this every 1 millisecond via timer ISR
//
void (*serviceAddon)() = NULL;
void ServiceAddon(void)
{
	timer1s++;
	timerScroll++;
	if (timer1s >=1000)
	{
		// Time compute
        timestamp++;  // time update  
		if (state) timein = 0; // only on stop state
         else timein++;
		 
		if (((timein % DTIDLE)==0)&&(!state)  ) {
            if ((timein % (30*DTIDLE))==0){ itAskTime=true;timein = 0;} // synchronise with ntp every x*DTIDLE
            if (stateScreen != stime) {itAskStime=true;} // start the time display
        } 
		//if (stateScreen == stime) {itAskSsecond=true;} // start the time display
		if ((stateScreen == stime)||(stateScreen == smain)) { mTscreen = 1; } // display time
		if (!syncTime) itAskTime=true; // first synchro if not done
		
		timer1s = 0;
		// Other slow timers        
         timerScreen++;
         
	}
}

////////////////////////////////////////
// Clear all buffers and indexes
void clearAll()
{
      title[0] = 0;
      station[0]=0;
    for (int i=1;i<LINES;i++) {lline[i] = NULL;iline[i] = 0;tline[i] = 0;}
}
////////////////////////////////////////
void cleartitle()
{
     title[0] = 0;
     for (int i = 3;i<LINES;i++)  // clear lines
     {
       lline[i] = NULL;
     iline[i] = 0;
     tline[i] = 0; 
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
		   if ((lline[i] != NULL))
		   {
				len = u8g2_GetUTF8Width(&u8g2,lline[i]+iline[i]);
				if (i == 0)	 len += u8g2_GetUTF8Width(&u8g2,nameNum) ;
				if (len >= x-20) 
					iline[i]++;
				else 
					tline[i] = 6;
		   }
	   }
	}
	mTscreen = 1;	
}


////////////////////////////
// Change the current screen
////////////////////////////
void Screen(typeScreen st){
  if (stateScreen != st)
  {
// if a number is entered, play it.
    if (strlen(irStr) >0)
       playStationInt(atoi(irStr));
// clear the number       
    irStr[0] = 0;
  }
//  else
//    if (mTscreen == 0) mTscreen = 2;
  stateScreen = st;  
  timein = 0;
  mTscreen = 1;
  
}


// Bottom of screens
void screenBottom()
{
//VOLUME
    u8g2_DrawFrame(&u8g2,0,yy-3,x-1,3);
    u8g2_DrawHLine(&u8g2,0,yy-2,((uint16_t)(x*volume)/255));                         
//TIME
//  if ((lline[4] == NULL)||(x==84))
    u8g2_SetFont(&u8g2, u8g2_font_5x8_tf);
    u8g2_DrawUTF8(&u8g2,x/2-(u8g2_GetUTF8Width(&u8g2,strsec)/2),yy-y-4,strsec);  
	
}

uint8_t getFontLineSpacing()
{
	return (u8g2_GetAscent(&u8g2) - u8g2_GetDescent(&u8g2));
}

////////////////////////////////////////
// draw all lines
void drawFrame()
{
if(mTscreen)
{
  u8g2_ClearBuffer(&u8g2);
  dt=gmtime(&timestamp);
  if (x==84)
  sprintf(strsec,"%02d-%02d  %02d:%02d:%02d",dt->tm_mon,dt->tm_mday, dt->tm_hour, dt->tm_min,dt->tm_sec);
  else
  sprintf(strsec,"%02d-%02d-%04d  %02d:%02d:%02d",dt->tm_mon,dt->tm_mday,dt->tm_year+1900, dt->tm_hour, dt->tm_min,dt->tm_sec);
  if (u8g2.width == 84)
    u8g2_SetFont(&u8g2, u8g2_font_5x8_tf);
  else 
    u8g2_SetFont(&u8g2, u8g2_font_6x10_tf);
  u8g2_SetDrawColor(&u8g2, 1);

    y = getFontLineSpacing();
    u8g2_SetFontRefHeightText(&u8g2); 
  
//  do {
    u8g2_DrawHLine(&u8g2,0,(4*y) - (y/2)-1,x);
    u8g2_DrawBox(&u8g2,0,0,x-1,y);
    for (int i = 0;i < LINES;i++)
    {
      if (i == 0)u8g2_SetDrawColor(&u8g2, 0);
      else u8g2_SetDrawColor(&u8g2, 1);
      if (i >=3) z = y/2+2 ; else z = 1;
      if ((lline[i] != NULL))
      {
//Serial.print("Liney: ");Serial.println(y);  
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
    screenBottom();    
 // } while( u8g2_NextPage(&u8g2); );
   u8g2_SendBuffer(&u8g2);
   mTscreen = 0;
}   
}


//////////////////////////
void drawTTitle(char* ttitle)
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

////////////////////
// draw the number entered from IR
void drawNumber()
{
  char ststr[] = {"Number"};
  if(mTscreen)
  {
       u8g2_ClearBuffer(&u8g2);
		drawTTitle(ststr);   
        uint16_t xxx = (x/2)-(u8g2_GetUTF8Width(&u8g2,irStr)/2); 
        u8g2_DrawUTF8(&u8g2,xxx,yy/3, irStr);        
        screenBottom(); 
		u8g2_SendBuffer(&u8g2);  		
		mTscreen = 0;    
  }   

}


////////////////////
// draw the station screen
void drawStation()
{
  char ststr[] = {"Station"};
  char* ddot;
  int16_t len;
  char* ptl ;
  struct shoutcast_info* si;
  if (mTscreen)
  { 
	u8g2_ClearBuffer(&u8g2);
	
	do {
		si = getStation(futurNum);
		sprintf(sline,"%d",futurNum);
		ddot = si->name;    
		ptl = ddot;
		while ( *ptl == 0x20){ddot++;ptl++;}
		if (strlen(ddot)==0) // don't start an undefined station
		{
			playable = false; 
			free(si);
			if (currentValue < 0) {
				futurNum--; 
				if (futurNum <0) futurNum = 254;
			}
			else {
				futurNum++;
				if (futurNum > 254) futurNum = 0;
			}
		}	
		else 
			playable = true;                      
    } while (playable == false); 
	
    drawTTitle(ststr);        
    if (ddot != NULL)
    {
        u8g2_DrawUTF8(&u8g2,(x/2)-(u8g2_GetUTF8Width(&u8g2,sline)/2),yy/3-2, sline);
        len = (x/2)-(u8g2_GetUTF8Width(&u8g2,ddot)/2);
        if (len <0) len = 0;
        u8g2_DrawUTF8(&u8g2,len,yy/3+4+y, ddot);
    }
    screenBottom();  
	free (si);
	u8g2_SendBuffer(&u8g2);  	
	mTscreen = 0;    
  }  
}

////////////////////
// draw the volume screen
void drawVolume()
{
  char vlstr[] = {"Volume"}; 
   if (mTscreen){
        u8g2_ClearBuffer(&u8g2);
        drawTTitle(vlstr) ;  
		sprintf(aVolume,"%d",volume);
        uint16_t xxx = (x/2)-(u8g2_GetUTF8Width(&u8g2,aVolume)/2);     
        u8g2_DrawUTF8(&u8g2,xxx,yy/3,aVolume);
        screenBottom(); 
		u8g2_SendBuffer(&u8g2);  		   
		mTscreen = 0; 
    }  
}

void drawTime()
{
  char strdate[23];
  char strtime[20];
//  char strsec[3]; 
//  unsigned len;
  if (mTscreen)
  {  
		u8g2_ClearBuffer(&u8g2);
        dt=gmtime(&timestamp);
        sprintf(strdate,"%02d-%02d-%04d", dt->tm_mon, dt->tm_mday, dt->tm_year+1900);
        sprintf(strtime,"%02d:%02d:%02d", dt->tm_hour, dt->tm_min,dt->tm_sec);
        drawTTitle(strdate); 
		u8g2_SetFont(&u8g2, u8g2_font_9x15_tf);		
        u8g2_DrawUTF8(&u8g2,(x/2)-(u8g2_GetUTF8Width(&u8g2,strtime)/2),yy/3,strtime); 
        // draw ip
		u8g2_SetFont(&u8g2, u8g2_font_5x8_tf);
        u8g2_DrawUTF8(&u8g2,4,yy-getFontLineSpacing(),getIp());
		u8g2_SendBuffer(&u8g2);  
		mTscreen = 0;       
  }     
}


////////////////////
// Display a screen on the lcd
void drawScreen()
{
  if (mTscreen == 0) return;
  ESP_LOGV(TAG,"stateScreen: %d",stateScreen);
  switch (stateScreen)
  {
    case smain:  // force the draw of the complete screen
//      u8g2.clearScreen();
      drawFrame();
//      stateScreen = smain;
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
      drawNumber();     
      break;
    default: 
		drawFrame();       
  }
}


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


void stopStation()
{
//    irStr[0] = 0;
	clientDisconnect("cli stop");
}
void startStation()
{
 //   irStr[0] = 0;
    playStationInt(futurNum); ; 
}
void startStop()
{   
    state?stopStation():startStation();
}  
void stationOk()
{
       if (strlen(irStr) >0)
	   {	   
		  futurNum = atoi(irStr);
          playStationInt(futurNum);
	   }  
        else
        {
 //         if (stateScreen == sstation) 
            startStop();
        }  
        irStr[0] = 0;  
}
void changeStation(int16_t value)
{
	Screen(sstation);
	timerScreen = 0;  
	currentValue = value;
	if (value > 0) futurNum++;
	if (futurNum > 254) futurNum = 0;
	else if (value < 0) futurNum--;
	if (futurNum <0) futurNum = 254;
}				
// IR 
// a number of station in progress...
void nbStation(char nb)
{
  Screen(snumber);
  timerScreen = 0;
  if (strlen(irStr)>=3) irStr[0] = 0;
  uint8_t id = strlen(irStr);
  irStr[id] = nb;
  irStr[id+1] = 0;
}
 

extern void rmt_nec_rx_task();
void task_addon(void *pvParams)
{
	
// Encoder	init
  enum modeStateEncoder { encVolume, encStation } ;
  //static enum modeStateEncoder stateEncoder = encVolume;
  Button newButton ;
  static int16_t oldValue = 0;
  ClickEncoderInit(PIN_ENC_A, PIN_ENC_B, PIN_ENC_BTN);
  serviceEncoder = &service;	; // connect the 1ms interruption
  serviceAddon = &ServiceAddon;	; // connect the 1ms interruption
  futurNum = getCurrentStation();
  //ir
  // queue for events of the IR nec rx
  event_ir = xQueueCreate(10, sizeof(event_ir_t));
  event_ir_t evt;
  xTaskCreate(rmt_nec_rx_task, "rmt_nec_rx_task", 2048, NULL, 10, NULL);
	
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
    		
		if (newButton != Open)
		{    
			ESP_LOGD(TAG,"Button: %d",newButton);
			if (newButton == DoubleClicked) {startStop();}
//			if (getPinState() == getpinsActive())
			if ((newButton == Held)&&(getPinState() == getpinsActive()))
			{   
				currentValue = newValue;
				changeStation(newValue);
			} 
		}	else
		if (/*(stateScreen  != sstation)&&*/(newValue != 0))
		{    
			ESP_LOGD(TAG,"Enc value: %d, oldValue: %d,  incr volume: %d",newValue, oldValue,newValue+(oldValue*3));
			setRelVolume(newValue+(oldValue*3));
		} 
		
		oldValue += newValue;
// end Encoder loop

// IR
		while (xQueueReceive(event_ir, &evt, 0))
		{
			uint32_t evtir = ((evt.addr)<<8)|(evt.cmd&0xFF);
			ESP_LOGD(TAG,"IR event: Channel: %x, ADDR: %x, CMD: %x = %X, REPEAT: %d",evt.channel,evt.addr,evt.cmd, evtir,evt.repeat_flag );
	if (!evt.repeat_flag ) // avoid repetition
    switch(evtir)
    {
      case 0xFF0046: 
      case 0xF70812:  /*(" FORWARD");*/  changeStation(+1);  break;
      case 0xFF0044:
      case 0xF70842:
      case 0xF70815: /*(" LEFT");*/  setRelVolume(-5);  break;
      case 0xFF0040:
      case 0xF7081E: /*(" -OK-");*/ stationOk();     break;
      case 0xFF0043:
      case 0xF70841:
      case 0xF70814: /*(" RIGHT");*/ setRelVolume(+5);     break; // volume +
      case 0xFF0015:
      case 0xF70813: /*(" REVERSE");*/ changeStation(-1); break;
      case 0xFF0016:
      case 0xF70801: /*(" 1");*/ nbStation('1');   break;
      case 0xFF0019:
      case 0xF70802: /*(" 2");*/ nbStation('2');   break;
      case 0xFF000D:
      case 0xF70803: /*(" 3");*/ nbStation('3');   break;
      case 0xFF000C:
      case 0xF70804: /*(" 4");*/ nbStation('4');   break;
      case 0xFF0018:
      case 0xF70805: /*(" 5");*/ nbStation('5');   break;
      case 0xFF005E:
      case 0xF70806: /*(" 6");*/ nbStation('6');   break;
      case 0xFF0008:
      case 0xF70807: /*(" 7");*/ nbStation('7');   break;
      case 0xFF001C:
      case 0xF70808: /*(" 8");*/ nbStation('8');   break;
      case 0xFF005A:
      case 0xF70809: /*(" 9");*/ nbStation('9');   break;
      case 0xFF0042:
      case 0xF70817: /*(" *");*/   playStationInt(futurNum);   break;
      case 0xFF0052:
      case 0xF70800: /*(" 0");*/ nbStation('0');   break;
      case 0xFF004A:
      case 0xF7081D: /*(" #");*/  stopStation();    break;
      default:;
      /*SERIALX.println(F(" other button   "));*/
    }// End Case

    if (evt.repeat_flag ) // repetition
    switch(evtir)
    {
      case 0xFF0046: 
      case 0xF70812:  /*(" FORWARD");*/  changeStation(+1); break;
      case 0xFF0015:
      case 0xF70813:  /*(" REVERSE");*/ changeStation(-1); break;
      case 0xFF0044:
      case 0xF70842:
      case 0xF70815: /*(" LEFT");*/  setRelVolume(-5);  break;
      case 0xFF0043:
      case 0xF70841:
      case 0xF70814: /*(" RIGHT");*/ setRelVolume(+5);  break; // volume +
      default:;
    } 
			
			
			
		}

//lcd
		drawScreen(); 
		vTaskDelay(1);		
		if (itAskTime) // time to ntp. Don't do that in interrupt.
		{
			if (ntp_get_time(&dt) )
			{	
				applyTZ(dt);
				timestamp = mktime(dt); 
				syncTime = true;				
			} 
			itAskTime = false;
		}
		if (itAskStime) // time start the time display. Don't do that in interrupt.
		{    
			Screen(stime);
			drawScreen();
			itAskStime = false;
		}

		if (timerScreen >= 3) // 3 sec timeout 
		{
			timerScreen = 0;
			if ((stateScreen != smain)&&(stateScreen != stime))
			{
			Screen(smain);  //Back the the main screen
			// Play the changed station on return to main screen
			if (playable && ( futurNum!= atoi(nameNum))) playStationInt(futurNum);
			}
		}
		vTaskDelay(1);
		if ( timerScroll >= 500) //
		{
			if (stateScreen == smain) scroll();  
			timerScroll = 0;
		}    	
		vTaskDelay(5);
	}
	
	vTaskDelete( NULL ); 
}

// interace funcion for the KaRadio32 events
void dVolume(uint16_t vol)
{ return;
volume = vol; Screen(svolume); drawScreen(); timerScreen = 0;}


////////////////////////////////////////
void separator(char* from)
{
//    byte len;
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

////////////////////////////////////////
// parse the karadio received line and do the job
void addonParse(const char *fmt, ...)
{
	char *line = NULL;
//	char* lfmt;
	int rlen;
	line = (char *)malloc(1024);
	if (line == NULL) return;
	line[0] = 0;
	strcpy(line,"ok\n");
	
	va_list ap;
	va_start(ap, fmt);	
	rlen = vsprintf(line,fmt, ap);		
	va_end(ap);
	line = realloc(line,rlen+1);
	if (line == NULL) return;	
	ESP_LOGV(TAG,"LINE: %s",line);
	
  static bool dvolume = true; // display volume screen
  char* ici;
 //  removeUtf8((byte*)line);
 
 ////// Meta title  ##CLI.META#: 
   if ((ici=strstr(line,"META#: ")) != NULL)
   {     
      cleartitle(); 
      strcpy(title,ici+7);    
      separator(title); 
   } else 
    ////// ICY4 Description  ##CLI.ICY4#:
    if ((ici=strstr(line,"ICY4#: ")) != NULL)
    {
//      cleartitle();
      strcpy(genre,ici+7);
      lline[2] = genre;
    } else 
 ////// ICY0 station name   ##CLI.ICY0#:
   if ((ici=strstr(line,"ICY0#: ")) != NULL)
   {
      clearAll();
      if (strlen(ici+7) == 0) strcpy (station,nameset);
      else strcpy(station,ici+7);
      separator(station);
   } else
 ////// STOPPED  ##CLI.STOPPED#  
   if ((ici=strstr(line,"STOPPED")) != NULL)
   {
      state = false;
      cleartitle();
      strcpy(title,"STOPPED");
      lline[TITLE1] = title;
	  mTscreen = 1;
   }    
   else  
 //////Namesett    ##CLI.NAMESET#:
   if ((ici=strstr(line,"MESET#: ")) != NULL)  
   {
      strcpy(nameset,ici+8);
      ici = strstr(nameset," ");
     if (ici != NULL)
     {
       clearAll();
       strncpy(nameNum,nameset,ici-nameset+1);
       nameNum[ici - nameset+1] = 0; 
       futurNum = atoi(nameNum);     
     }
     strcpy(nameset,nameset+strlen(nameNum));
     lline[STATIONNAME] = nameset;
//     separator(nameset);            
   } else
 //////Playing    ##CLI.PLAYING#
   if ((ici=strstr(line,"YING#")) != NULL)  
   {
      state = true;
      if (stateScreen == stime) Screen(smain);      
      if (strcmp(title,"STOPPED") == 0)
      {
        title[0] = 0;
        separator(title);
      }
	  mTscreen = 1;
   } else
   //////Volume   ##CLI.VOL#:
   if ((ici=strstr(line,"VOL#:")) != NULL)  
   {
      volume = atoi(ici+6);
      strcpy(aVolume,ici+6); 
      if (dvolume)
         Screen(svolume); 
      else 
         dvolume = true;
      timerScreen = 0;
   } else
  //////Volume offset    ##CLI.OVOLSET#:
   if ((ici=strstr(line,"OVOLSET#:")) != NULL)  
   {
      dvolume = false; // don't show volume on start station
   }
   free (line);
}



