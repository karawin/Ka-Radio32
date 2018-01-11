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
#include "ucg_esp32_hal.h"
#include <time.h>
#include "ntp.h"

#include "eeprom.h"
#include "addonu8g2.h"
#include "addonucg.h"


#define TAG  "addon"


// second before time display in stop state
#define DTIDLE  60



#define isColor (lcd_type&LCD_COLOR)

char irStr[4];
xQueueHandle event_ir;
xQueueHandle event_lcd;
u8g2_t u8g2; // a structure which will contain all the data for one display
ucg_t  ucg;
static uint8_t lcd_type;

// list of screen
typedef  enum typeScreen {smain,svolume,sstation,snumber,stime,snull} typeScreen ;
static typeScreen stateScreen = snull;
static typeScreen oldStateScreen = snull;
// state of the transient screen
static uint8_t mTscreen = MTNEW; // 0 dont display, 1 display full, 2 display variable part

static bool playable = true;
static uint16_t volume;
static int16_t futurNum = 0; // the number of the wanted station

static unsigned timerScreen = 0;
static unsigned timerScroll = 0;
static unsigned timerLcdOut = 0;
static unsigned timer1s = 0;

static unsigned timein = 0;
static struct tm *dt;
time_t timestamp = 0;
static bool syncTime = false;
static bool itAskTime = true; // update time with ntp if true
static bool itAskStime = false; // start the time display
static bool itLcdOut = false;
//static bool itAskSsecond = false; // start the time display
static bool state = false; // start stop on Ok key

static int16_t newValue = 0;
static int16_t currentValue = 0;
static bool dvolume = true; // display volume screen
 
void Screen(typeScreen st); 
 
 
// Compatibility B/W Color-------------------- 

static void ClearBuffer()
{
  if (isColor)
	ucg_ClearScreen(&ucg);
  else
	u8g2_ClearBuffer(&u8g2);
}

static int16_t DrawString(int16_t x, int16_t y,  const char *str)
{
  if (isColor)
	return ucg_DrawString(&ucg,x,y,0,str);
  else
	return u8g2_DrawUTF8(&u8g2,x,y,str);  
}

static void DrawColor(uint8_t color, uint8_t r, uint8_t g, uint8_t b)
{
  if (isColor)
	ucg_SetColor(&ucg, 0,r,g,b);
  else
	u8g2_SetDrawColor(&u8g2, color);
}

static void DrawBox(ucg_int_t x, ucg_int_t y, ucg_int_t w, ucg_int_t h)
{
  if (isColor)
	ucg_DrawBox(&ucg, x,y,w,h);
  else
	u8g2_DrawBox(&u8g2, x,y,w,h);
}

uint16_t GetWidth()
{
  if (isColor)
	  return ucg_GetWidth(&ucg);

  return u8g2.width;
}

void wakeLcd()
{
	if (lcd_type == LCD_NONE) return;
	timerLcdOut = getLcdOut();
	if((isColor) && (itLcdOut))  mTscreen = MTNEW;
	itLcdOut = false;
}

void lcd_init(uint8_t Type)
{	
	lcd_type = Type;
	if (lcd_type == LCD_NONE) return;
	if (lcd_type & LCD_COLOR) // Color one
	{
		lcd_initUcg(&lcd_type);
	} else //B/W lcd
	{
		lcd_initU8g2(&lcd_type);
	}
	vTaskDelay(2);
}


void lcd_state(char* State)
{
	if (lcd_type == LCD_NONE) return;
	DrawColor(0,0,0,0);
	DrawBox(2, 40, 128-30, 12);
	DrawColor(1,255,255,255);
	if (isColor) ucg_SetFont( &ucg,ucg_font_6x10_tf);
	else u8g2_SetFont( &u8g2,u8g2_font_6x10_tf);
	DrawString(2,40,State);
	if (!(isColor)) u8g2_SendBuffer(&u8g2);
}

void lcd_welcome(char* ip)
{
	if (lcd_type == LCD_NONE) return;
    char *url = "Stopped";// get_url(); // play_url();	
	if (strlen(ip)==0) ClearBuffer();
    if (isColor) 
		ucg_SetFont(&ucg,ucg_font_helvR14_tf );
	else  u8g2_SetFont(&u8g2,u8g2_font_helvR14_tf );
	if (GetWidth() <=64)
		DrawString(2,2,"KaRadio32");
    else DrawString(10,2,"KaRadio32");
	if (isColor) ucg_SetFont(&ucg,ucg_font_6x10_tf);
	else u8g2_SetFont(&u8g2,u8g2_font_6x10_tf);
	DrawString(2,24,"WiFi Webradio");
	DrawColor(0,0,0,0);
	DrawBox(2, 40, 128-30, 12);
	DrawColor(1,255,255,255);
	DrawString(2,40,url);
	DrawString( DrawString(2,53,"IP")+18,53,ip);
	if (!(isColor)) u8g2_SendBuffer(&u8g2);
}

 // ----------------------------------------------------------------------------
// call this every 1 millisecond via timer ISR
//
void (*serviceAddon)() = NULL;
IRAM_ATTR void ServiceAddon(void)
{
	timer1s++;
	timerScroll++;
	if (timer1s >=1000)
	{
		// Time compute
        timestamp++;  // time update  
		if (timerLcdOut >0) timerLcdOut--; // 
/*		if (state) timein = 0; // only on stop state
         else */
		timein++;
		if ((timestamp % (10*DTIDLE))==0){ itAskTime=true;} // synchronise with ntp every x*DTIDLE
		 
		if (((timein % DTIDLE)==0)&&(!state)  ) {           
			{itAskStime=true;timein = 0;} // start the time display
        } 
		if (timerLcdOut == 1) itLcdOut = true;
		//if (stateScreen == stime) {itAskSsecond=true;} // start the time display
		if ((stateScreen == stime)||(stateScreen == smain)) { mTscreen = MTREFRESH; } // display time
		if (!syncTime) itAskTime=true; // first synchro if not done
		
		timer1s = 0;
		// Other slow timers        
         timerScreen++;
         
	}
}

////////////////////////////////////////
// futurNum
void setFuturNum(int16_t new)
{
	futurNum = new;
}
int16_t getFuturNum()
{
	return futurNum;
}

////////////////////////////////////////
// scroll each line
void scroll()
{	
	isColor?scrollUcg():scrollU8g2();
}


////////////////////////////
// Change the current screen
////////////////////////////
void Screen(typeScreen st){
  if (stateScreen != st)
  {
//	stateScreen = (stateScreen == smain)?smain0:stateScreen;  
	oldStateScreen = stateScreen;
	mTscreen = MTNEW;
  }
  else
    if (mTscreen == MTNODISPLAY) mTscreen = MTREFRESH;
  stateScreen = st;  
  timein = 0; 
//  printf("Screen %d  mTscreen:%d\n",st,mTscreen);
}


////////////////////////////////////////
// draw all lines
void drawFrame()
{	
	dt=localtime(&timestamp);
	isColor?drawFrameUcg(mTscreen,dt):drawFrameU8g2(mTscreen,dt);
}


//////////////////////////
void drawTTitle(char* ttitle)
{ 
	isColor?drawTTitleUcg(ttitle):drawTTitleU8g2(ttitle);
}

////////////////////
// draw the number entered from IR
void drawNumber()
{
	isColor?drawNumberUcg(mTscreen,irStr):drawNumberU8g2(mTscreen,irStr);  
}


////////////////////
// draw the station screen
void drawStation()
{
  char sNum[4] ; 
  char* ddot;
  char* ptl ;
  struct shoutcast_info* si;

 //ClearBuffer();
	
  do {
	si = getStation(futurNum);
	sprintf(sNum,"%d",futurNum);
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
	
  //drawTTitle(ststr);   

  isColor?drawStationUcg(mTscreen,sNum,ddot):drawStationU8g2(mTscreen,sNum,ddot);
   
  free (si);
}

////////////////////
// draw the volume screen
void drawVolume()
{
  char aVolume[4] ; 
  sprintf(aVolume,"%d",volume);
//  printf("drawVolume. mTscreen: %d, aVolume: %d\n",mTscreen,atoi(aVolume));
  isColor?drawVolumeUcg(mTscreen,aVolume):drawVolumeU8g2(mTscreen,aVolume);	
}

void drawTime()
{
	dt=localtime(&timestamp);
//	printf("drawTime. mTscreen: %d, timein: %d \n",mTscreen,timein);
	isColor?drawTimeUcg(mTscreen,dt,timein):drawTimeU8g2(mTscreen,dt,timein);	
}


////////////////////
// Display a screen on the lcd
void drawScreen()
{
  if (lcd_type == LCD_NONE) return;
  //ESP_LOGV(TAG,"stateScreen: %d",stateScreen);
  if ((mTscreen != MTNODISPLAY)&&(!itLcdOut))
  {
//	  printf("drawScreenenter mTscreen:%d\n",mTscreen);
//printf("drawScreen %d, mTscreen: %d\n",stateScreen,mTscreen);	
  switch (stateScreen)
  {
    case smain:  // 
      drawFrame();
      break;
    case svolume:
      drawVolume();
      break;
    case sstation:
      drawStation(); 
      break; 
    case stime:
      drawTime(); 
      break;     
    case snumber:   
      drawNumber();     
      break;
    default: 
	  Screen(smain); 
	  drawFrame();	  
  }
  if (!(isColor)) u8g2_SendBuffer(&u8g2); 
  mTscreen = MTNODISPLAY;
  }   
}


void stopStation()
{
//    irStr[0] = 0;
	clientDisconnect("addon stop");
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
	timerScreen = 0;  
	currentValue = value;
	if (value > 0) futurNum++;
	if (futurNum > 254) futurNum = 0;
	else if (value < 0) futurNum--;
	if (futurNum <0) futurNum = 254;
	if (stateScreen != sstation) Screen(sstation);
	else if (value != 0) mTscreen = MTREFRESH;
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
 
//-----------------------
 // Compute the encoder
 //----------------------
void encoderLoop()
{
	Button newButton ;
	static int16_t oldValue = 0;
	event_lcd_t evt;

// Encoder loop		
		newValue = - getValue();
		newButton = getButton();
		if (newValue != 0) 
		{
		//    Serial.print("Encoder: ");Serial.println(newValue);
			// reset our accelerator
			if ((newValue >0)&&(oldValue<0)) oldValue = 0;
			if ((newValue <0)&&(oldValue>0)) oldValue = 0;
			wakeLcd();
		}
		else
		{
			// lower accelerator 
			if (oldValue <0) oldValue++;
			if (oldValue >0) oldValue--;
		}
    		
		if (newButton != Open)
		{ 
			wakeLcd();
			ESP_LOGD(TAG,"Button: %d",newButton);
			if (newButton == Clicked) {startStop();}
			if (newButton == DoubleClicked) {
				(stateScreen==smain)?Screen(stime):Screen(smain);
				drawScreen(); 
			}
//			if (getPinState() == getpinsActive())
			if ((newButton == Held)&&(getPinState() == getpinsActive()))
			{   
				currentValue = newValue;
				changeStation(newValue);
			} 
			
		}	else
		{
			if ((stateScreen  != sstation)&&(newValue != 0))
			{    
				ESP_LOGD(TAG,"Enc value: %d, oldValue: %d,  incr volume: %d",newValue, oldValue,newValue+(oldValue*3));
				evt.lcmd = evol;
				evt.lline = (char*)((uint32_t)newValue+(oldValue*3));
				xQueueSend(event_lcd,&evt, 0);
			} 
			if ((stateScreen  == sstation)&&(newValue != 0))
			{    
				currentValue += newValue;
				evt.lcmd = estation;
				evt.lline = (char*)((uint32_t)newValue);
				xQueueSend(event_lcd,&evt, 0);				
			} 	
		}		
		oldValue += newValue;
// end Encoder loop

}

 //-----------------------
 // Compute the encoder
 //----------------------
 void irLoop()
 {
// IR
event_ir_t evt;
	while (xQueueReceive(event_ir, &evt, 0))
	{
		wakeLcd();
		uint32_t evtir = ((evt.addr)<<8)|(evt.cmd&0xFF);
		ESP_LOGI(TAG,"IR event: Channel: %x, ADDR: %x, CMD: %x = %X, REPEAT: %d",evt.channel,evt.addr,evt.cmd, evtir,evt.repeat_flag );
		if (!evt.repeat_flag ) // avoid repetition
		switch(evtir)
		{
		case 0xFF0046: 
		case 0xFF18E7:
		case 0xF70812:  /*(" FORWARD");*/  changeStation(+1);  break;
		case 0xFF0044:
		case 0XFF10EF:
		case 0xF70842:
		case 0xF70815: /*(" LEFT");*/  setRelVolume(-5);  break;
		case 0xFF0040:
		case 0XFF38C7:
		case 0xF7081E: /*(" -OK-");*/ stationOk();     break;
		case 0xFF0043:
		case 0XFF5AA5:
		case 0xF70841:
		case 0xF70814: /*(" RIGHT");*/ setRelVolume(+5);     break; // volume +
		case 0xFF0015:
		case 0XFF4AB5:
		case 0xF70813: /*(" REVERSE");*/ changeStation(-1); break;
		case 0xFF0016:
		case 0XFFA25D:
		case 0xF70801: /*(" 1");*/ nbStation('1');   break;
		case 0xFF0019:
		case 0XFF629D:
		case 0xF70802: /*(" 2");*/ nbStation('2');   break;
		case 0xFF000D:
		case 0XFFE21D:
		case 0xF70803: /*(" 3");*/ nbStation('3');   break;
		case 0xFF000C:
		case 0XFF22DD:
		case 0xF70804: /*(" 4");*/ nbStation('4');   break;
		case 0xFF0018:
		case 0XFF02FD:
		case 0xF70805: /*(" 5");*/ nbStation('5');   break;
		case 0xFF005E:
		case 0XFFC23D:
		case 0xF70806: /*(" 6");*/ nbStation('6');   break;
		case 0xFF0008:
		case 0XFFE01F:
		case 0xF70807: /*(" 7");*/ nbStation('7');   break;
		case 0xFF001C:
		case 0XFFA857:
		case 0xF70808: /*(" 8");*/ nbStation('8');   break;
		case 0xFF005A:
		case 0XFF906F:
		case 0xF70809: /*(" 9");*/ nbStation('9');   break;
		case 0xFF0042:
		case 0XFF6897:
		case 0xF70817: /*(" *");*/   playStationInt(futurNum);   break;
		case 0xFF0052:
		case 0XFF9867:
		case 0xF70800: /*(" 0");*/ nbStation('0');   break;
		case 0xFF004A:
		case 0XFFB04F:
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
}
 
 // IO task
 void task_addonio(void *pvParams)
 {
	 while (1)
	 {
		encoderLoop(); // compute the encoder		
		irLoop();
		vTaskDelay(20);
	}
	vTaskDelete( NULL ); 
 }
//------------------- 
// Main task of addon
//------------------- 
extern void rmt_nec_rx_task();
void task_addon(void *pvParams)
{
	event_lcd_t evt; // lcd event

	// Encoder	init
	//enum modeStateEncoder { encVolume, encStation } ;
	//static enum modeStateEncoder stateEncoder = encVolume;
	ClickEncoderInit(PIN_ENC_A, PIN_ENC_B, PIN_ENC_BTN);
	serviceEncoder = &service;	; // connect the 1ms interruption
	serviceAddon = &ServiceAddon;	; // connect the 1ms interruption
	futurNum = getCurrentStation();
	//ir
	// queue for events of the IR nec rx
	event_ir = xQueueCreate(10, sizeof(event_ir_t));
	ESP_LOGI(TAG,"event_ir: %x",(int)event_ir);
	// queue for events of the lcd
	event_lcd = xQueueCreate(40, sizeof(event_lcd_t));
	ESP_LOGI(TAG,"event_lcd: %x",(int)event_lcd);
	
	xTaskCreate(rmt_nec_rx_task, "rmt_nec_rx_task", 2148, NULL, 10, NULL);
//	xTaskCreate(task_addonio, "task_addonio", 2350, NULL, 4, NULL);
	vTaskDelay(1);
	wakeLcd();

	while (1)
	{

		encoderLoop(); // compute the encoder
		
		irLoop();

		while (xQueueReceive(event_lcd, &evt, 0))
		{ 
			wakeLcd();
			switch(evt.lcmd)
			{
				case lmeta:
					isColor?metaUcg(evt.lline):metaU8g2(evt.lline);
					break;
				case licy4:
					isColor?icy4Ucg(evt.lline):icy4U8g2(evt.lline);
					break;
				case licy0:
					isColor?icy0Ucg(evt.lline):icy0U8g2(evt.lline);
					break;
				case lstop:
					isColor?statusUcg("STOPPED"):statusU8g2("STOPPED");
					if (stateScreen != smain)
					{
						mTscreen= MTNEW;
						stateScreen =  smain; 
						drawScreen();
					}
					break;
				case lnameset:
					isColor?namesetUcg(evt.lline):namesetU8g2(evt.lline);
					Screen(smain);
					mTscreen= MTNEW;
					stateScreen =  smain; 
					drawScreen();
					break;
				case lplay:
					isColor?playingUcg():playingU8g2();						  
					break;
				case lvol:
					isColor?setVolumeUcg(volume):setVolumeU8g2(volume);
					if (dvolume)
						Screen(svolume); 
					else 
						dvolume = true;
					timerScreen = 0;
					break;
				case lovol:
					dvolume = false; // don't show volume on start station
					break;
				case evol:
					setRelVolume((uint32_t)evt.lline);
					evt.lline = NULL;
					break;
				case estation:
					changeStation((uint32_t)evt.lline);				
					evt.lline = NULL;
					break;
				default:;
			}
			if (evt.lline != NULL) free(evt.lline);

		}
		
//		vTaskDelay(1);		

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
			//drawScreen();
			itAskStime = false;
		}

		if (itLcdOut) // switch off the lcd
		{
			isColor?ucg_ClearScreen(&ucg):u8g2_ClearDisplay(&u8g2);
		}
		
		if (timerScreen >= 2) // 2 sec timeout 
		{
			timerScreen = 0;
			if ((stateScreen != smain)&&(stateScreen != stime)&&(stateScreen != snull))
			{
				Screen(oldStateScreen);  //Back the the old screen
				// Play the changed station on return to main screen
				// if a number is entered, play it.
				if (strlen(irStr) >0){
					futurNum = atoi (irStr);
					if (futurNum>254) futurNum = 0;
					playable = true;
					// clear the number       
					irStr[0] = 0;
				}
				if ((strlen(isColor?getNameNumUcg():getNameNumU8g2()) != 0 )
					&& playable 
					&& ( futurNum!= atoi(  isColor?getNameNumUcg():getNameNumU8g2()  ))) 
				{
					isColor?statusUcg("STARTING"):statusU8g2("STARTING");
					if (lcd_type != LCD_NONE) drawScreen(); 
					playStationInt(futurNum);
				}				
			}
		}
//		vTaskDelay(1);
		if ( timerScroll >= 300) //
		{
			if (lcd_type != LCD_NONE) 
			{
				if (stateScreen == smain) scroll(); 
				drawScreen(); 
			}
			timerScroll = 0;
		}  
	
		vTaskDelay(30);
	}
	
	vTaskDelete( NULL ); 
}

// force a new dt fetch
void addonDt() { itAskTime = true; }


////////////////////////////////////////
// parse the karadio received line and do the job
void addonParse(const char *fmt, ...)
{
	event_lcd_t evt;
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
	
  char* ici;
 
 ////// Meta title  ##CLI.META#: 
   if ((ici=strstr(line,"META#: ")) != NULL)
   {     
		evt.lcmd = lmeta;
		evt.lline = malloc(strlen(ici)+1);
		//evt.lline = NULL;
		strcpy(evt.lline,ici);
		xQueueSend(event_lcd,&evt, 0);
   } else 
 ////// ICY4 Description  ##CLI.ICY4#:
    if ((ici=strstr(line,"ICY4#: ")) != NULL)
    {
		evt.lcmd = licy4;
		evt.lline = malloc(strlen(ici)+1);
		//evt.lline = NULL;
		strcpy(evt.lline,ici);
		xQueueSend(event_lcd,&evt, 0);
    } else 
 ////// ICY0 station name   ##CLI.ICY0#:
   if ((ici=strstr(line,"ICY0#: ")) != NULL)
   {
		evt.lcmd = licy0;
		evt.lline = malloc(strlen(ici)+1);
		//evt.lline = NULL;
		strcpy(evt.lline,ici);
		xQueueSend(event_lcd,&evt, 0);
   } else
 ////// STOPPED  ##CLI.STOPPED#  
   if ((ici=strstr(line,"STOPPED")) != NULL)
   {
		state = false;	  
 		evt.lcmd = lstop;
		evt.lline = NULL;
		xQueueSend(event_lcd,&evt, 0);
   }    
   else  
 //////Nameset    ##CLI.NAMESET#:
   if ((ici=strstr(line,"MESET#: ")) != NULL)  
   {   
	  	evt.lcmd = lnameset;
		evt.lline = malloc(strlen(ici)+1);
		//evt.lline = NULL;
		strcpy(evt.lline,ici);
		xQueueSend(event_lcd,&evt, 0);
   } else
 //////Playing    ##CLI.PLAYING#
   if ((ici=strstr(line,"YING#")) != NULL)  
   {
		state = true;
 		evt.lcmd = lplay;
		evt.lline = NULL;
		xQueueSend(event_lcd,&evt, 0);
   } else
   //////Volume   ##CLI.VOL#:
   if ((ici=strstr(line,"VOL#:")) != NULL)  
   {
		volume = atoi(ici+6);
 		evt.lcmd = lvol;
		evt.lline = NULL;
		xQueueSend(event_lcd,&evt, 0);
   } else
  //////Volume offset    ##CLI.OVOLSET#:
   if ((ici=strstr(line,"OVOLSET#:")) != NULL)  
   {
	    evt.lcmd = lovol;
		evt.lline = NULL;
		xQueueSend(event_lcd,&evt, 0);
   }
   free (line);
}

