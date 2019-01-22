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
#include "ClickButtons.h"
#include "ClickJoystick.h"
#include "app_main.h"
#include "gpio.h"
#include "webclient.h"
#include "webserver.h"
#include "interface.h"

#include "addon.h"
#include "custom.h"
#include "u8g2_esp32_hal.h"
#include "ucg_esp32_hal.h"
#include <time.h>
#include "ntp.h"

#include "eeprom.h"
#include "addonu8g2.h"
#include "addonucg.h"
#include "xpt2046.h"

#include "esp_adc_cal.h"

#define TAG  "addon"

static void evtClearScreen();
// second before time display in stop state
#define DTIDLE  60



#define isColor (lcd_type&LCD_COLOR)
const char *stopped = "STOPPED";	

char irStr[4];
xQueueHandle event_ir = NULL;
xQueueHandle event_lcd = NULL;
u8g2_t u8g2; // a structure which will contain all the data for one display
ucg_t  ucg;
static uint8_t lcd_type;
static xTaskHandle  pxTaskLcd;
// list of screen
typedef  enum typeScreen {smain,svolume,sstation,snumber,stime,snull} typeScreen ;
static typeScreen stateScreen = snull;
static typeScreen oldStateScreen = smain;
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
static uint8_t itLcdOut = 0;
//static bool itAskSsecond = false; // start the time display
static bool state = false; // start stop on Ok key

static int16_t currentValue = 0;
static bool dvolume = true; // display volume screen
 
// custom ir code init from hardware nvs
typedef enum {KEY_UP,KEY_LEFT,KEY_OK,KEY_RIGHT,KEY_DOWN,
		KEY_0,KEY_1,KEY_2,KEY_3,KEY_4,KEY_5,KEY_6,KEY_7,KEY_8,KEY_9,
		KEY_STAR,KEY_DIESE,KEY_INFO, KEY_MAX} customKey_t;
		
static uint32_t customKey[KEY_MAX][2]; 
static bool isCustomKey = false;

static bool isEncoder0 = true;
static bool isEncoder1 = true;
static bool isButton0 = true;
static bool isButton1 = true;
static bool isJoystick0 = true;
static bool isJoystick1 = true;
void Screen(typeScreen st); 
static void evtDrawScreen();
Encoder_t* encoder0 = NULL;
Encoder_t* encoder1 = NULL;
Button_t* button0 = NULL;
Button_t* button1 = NULL;
Joystick_t* joystick1 = NULL;
Joystick_t* joystick0 = NULL;

struct tm* getDt() { return dt;}

void* getEncoder(int num)
{
	if (num == 0) return (void*)encoder0;
	if (num == 1) return (void*)encoder1;
	return NULL;
}

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
uint16_t GetHeight()
{
  if (isColor)
	  return ucg_GetHeight(&ucg);

  return u8g2.height;
}

void wakeLcd()
{
	if (lcd_type == LCD_NONE) return;
	// add the gpio switch on here gpioLedBacklight can be directly a GPIO_NUM_xx or declared in gpio.h
	LedBacklightOn();	
	timerLcdOut = getLcdOut(); // rearm the tempo
	if(((isColor) && (itLcdOut))|| mTscreen== MTNEW) { evtDrawScreen(); }
	itLcdOut = 0;
	

}

void sleepLcd()
{
	itLcdOut = 2;
	// add the gpio switch off here
	LedBacklightOff();
	evtClearScreen();

}

void lcd_init(uint8_t Type)
{	
	lcd_type = Type;

	// init the gpio for backlight
	LedBacklightInit();
	if (lcd_type == LCD_NONE) return;
	
	if (lcd_type & LCD_COLOR) // Color one
	{
		lcd_initUcg(&lcd_type);
	} else //B/W lcd
	{
		lcd_initU8g2(&lcd_type);
	}
	vTaskDelay(1);
//	dt=localtime(&timestamp);
}

void lcd_welcome(const char* ip,const char*state)
{
char Version[20];
	if (lcd_type == LCD_NONE) return;
	if ((strlen(ip)==0)&&(strlen(state)==0)) ClearBuffer();
	if (isColor) 
	{
		ucg_SetFont(&ucg,ucg_font_helvR14_tf );
		if (GetWidth() <=64)
			DrawString(2,2,"KaRadio32");
		else DrawString(10,2,"KaRadio32");	
		ucg_SetFont(&ucg,ucg_font_6x10_tf);
		sprintf(Version,"Version %s R%s\n",RELEASE,REVISION);
		DrawString(2,24,Version);
		DrawColor(0,0,0,0);
		DrawBox(2, 40, 128-30, 12);
		DrawColor(1,255,255,255);
		DrawString(2,40,state);
		DrawString( DrawString(2,53,"IP")+18,53,ip);	
	} else
	{
		u8g2_FirstPage(&u8g2);
		do {	
			u8g2_SetFont(&u8g2,u8g2_font_helvR14_tf );
			if (GetWidth() <=64)
				DrawString(2,2,"KaRadio32");
			else DrawString(10,2,"KaRadio32");
			u8g2_SetFont(&u8g2,u8g2_font_6x10_tf);
			sprintf(Version,"Version %s R%s\n",RELEASE,REVISION);
			DrawString(2,24,Version);
			DrawColor(0,0,0,0);
			DrawBox(2, 40, 128-30, 12);
			DrawColor(1,255,255,255);
			DrawString(2,40,state);
			DrawString( DrawString(2,53,"IP")+18,53,ip);
		} while ( u8g2_NextPage(&u8g2) );	    	
	}
}

 // ----------------------------------------------------------------------------
// call this every 1 millisecond via timer ISR
//
void (*serviceAddon)() = NULL;
IRAM_ATTR  void ServiceAddon(void)
{
	timer1s++;
	timerScroll++;
	if (timer1s >=1000)
	{
		// Time compute
        timestamp++;  // time update  
		if (timerLcdOut >0) timerLcdOut--; // 
		timein++;
		if ((timestamp % (10*DTIDLE))==0){ itAskTime=true;} // synchronise with ntp every x*DTIDLE
		 
		if (((timein % DTIDLE)==0)&&(!state)  ) {           
			{itAskStime=true;timein = 0;} // start the time display
        } 
		if (timerLcdOut == 1) itLcdOut = 1;
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
	oldStateScreen = stateScreen;
	mTscreen = MTNEW;
  }
  else
    if (mTscreen == MTNODISPLAY) mTscreen = MTREFRESH;
  stateScreen = st;  
  timein = 0; 
//  printf("st: %d, mTscreen: %d, old: %d\n",st,mTscreen,oldStateScreen);
}


////////////////////////////////////////
// draw all lines
void drawFrame()
{	
	dt=localtime(&timestamp);
	isColor?drawFrameUcg(mTscreen):drawFrameU8g2(mTscreen);
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
//  printf("drawVolume. mTscreen: %d, Volume: %d\n",mTscreen,volume);
  isColor?drawVolumeUcg(mTscreen):drawVolumeU8g2(mTscreen);	
}

void drawTime()
{
	dt=localtime(&timestamp);
	isColor?drawTimeUcg(mTscreen,timein):drawTimeU8g2(mTscreen,timein);	
}


////////////////////
// Display a screen on the lcd
void drawScreen()
{
  if (lcd_type == LCD_NONE) return;
//  ESP_LOGW(TAG,"stateScreen: %d, mTscreen: %d",stateScreen,mTscreen);
  if ((mTscreen != MTNODISPLAY)&&(!itLcdOut))
  {
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
	ESP_LOGD(TAG,"START/STOP State: %d",state);
    state?stopStation():startStation();
}  
void stationOk()
{
	ESP_LOGD(TAG,"STATION OK");
       if (strlen(irStr) >0)
	   {	   
		  futurNum = atoi(irStr);
          playStationInt(futurNum);
	   }  
        else
        {
            startStop();
        }  
        irStr[0] = 0;  
}
void changeStation(int16_t value)
{
//	Screen(sstation);
//	wakeLcd();
	timerScreen = 0;  
	currentValue = value;
	if (value > 0) futurNum++;
	if (futurNum > 254) futurNum = 0;
	else if (value < 0) futurNum--;
	if (futurNum <0) futurNum = 254;
	//else if (value != 0) mTscreen = MTREFRESH;
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
 
// 

static void evtDrawScreen()
{
	event_lcd_t evt;
	evt.lcmd = edraw;	
	evt.lline = NULL;
//	xQueueSendToFront(event_lcd,&evt, 0);	
	xQueueSend(event_lcd,&evt, 0);	
}

static void evtClearScreen()
{
//	isColor?ucg_ClearScreen(&ucg):u8g2_ClearDisplay(&u8g2);
	event_lcd_t evt;
	evt.lcmd = eclrs;	
	evt.lline = NULL;
//	xQueueSendToFront(event_lcd,&evt, 0);	
	xQueueSend(event_lcd,&evt, 0);	
}


static void evtStation(int16_t value)
{
	event_lcd_t evt;
//	wakeLcd();
//	if (stateScreen != sstation) evtClearScreen();
	timerScreen = 0;  
	evt.lcmd = estation;
	evt.lline = (char*)((uint32_t)value);
	xQueueSend(event_lcd,&evt, 0);			
}

// toggle main / time
static void toggletime()
{
	event_lcd_t evt;
	evt.lcmd = etoggle;	
	evt.lline = NULL;
	xQueueSend(event_lcd,&evt, 0);	
}

//----------------------------
// Adc read: keyboard buttons
//----------------------------

static adc1_channel_t  channel = GPIO_NONE;
static bool inside = false;

void adcInit()
{
	gpio_get_adc(&channel);	
	ESP_LOGD(TAG,"ADC Channel: %i",channel);
	if (channel != GPIO_NONE)
	{
		adc1_config_width(ADC_WIDTH_BIT_12);
		adc1_config_channel_atten(channel, ADC_ATTEN_DB_0);
	}
}

void adcLoop() {
	uint32_t voltage,voltage0,voltage1;
	bool wasVol = false;
	if (channel == GPIO_NONE) return;  // no gpio specified
	
	voltage0 = (adc1_get_raw(channel)+adc1_get_raw(channel)+adc1_get_raw(channel)+adc1_get_raw(channel))/4;
	vTaskDelay(1);
	voltage1 = (adc1_get_raw(channel)+adc1_get_raw(channel)+adc1_get_raw(channel)+adc1_get_raw(channel))/4;
//	printf ("Volt0: %d, Volt1: %d\n",voltage0,voltage1);
	voltage = (voltage0+voltage1)*105/(819);
	if (voltage <  40) return; // no panel
//	printf("Voltage: %d\n",voltage);

	if (inside&&(voltage0 > 3700)) 
	{
		inside = false;
		wasVol = false;
		return;
	}
	if (voltage0 > 3700) 
	{
		wasVol = false;
	}
	if ((voltage0 >3700) || (voltage1 >3700)) return; // must be two valid voltage	
	
	if (voltage < 985) ESP_LOGD(TAG,"Voltage: %i",voltage);	
//		printf("VOLTAGE: %d\n",voltage);
	if ((voltage >400) && (voltage < 590)) // volume +
	{
		setRelVolume(+5);
		wasVol = true;
		ESP_LOGD(TAG,"Volume+ : %i",voltage);
	}
	else if ((voltage >730) && (voltage < 830)) // volume -
	{
		setRelVolume(-5);
		wasVol = true;
		ESP_LOGD(TAG,"Volume- : %i",voltage);
	}	
		else if ((voltage >900) && (voltage < 985)) // station+
		{
			if (!wasVol)
			{
				evtStation(1);
				ESP_LOGD(TAG,"station+: %i",voltage);
			}
		}	
		else if ((voltage >620) && (voltage < 710)) // station-
		{
			if (!wasVol)
			{
				evtStation(-1);
				ESP_LOGD(TAG,"station-: %i",voltage);
			}
		}	
	if (!inside)
	{	
		if  ((voltage >100) && (voltage < 220)) // toggle time/info  old stop
		{
			inside = true;
			toggletime();
			ESP_LOGD(TAG,"toggle time: %i",voltage);	
		}
		else if ((voltage >278) && (voltage < 380)) //start stop toggle   old start
		{
			inside = true;
			startStop();
			ESP_LOGD(TAG,"start stop: %i",voltage);
		}

	}
}

//-----------------------
 // Compute the Buttons
 //----------------------
 void joystickCompute(Joystick_t *enc,bool role)
 {
	int16_t newValue = 0;
	{
		Button state1 = getJoystick(enc,0);
		Button state2 = getJoystick(enc,1);
//		ESP_LOGD(TAG,"Button1: %i, Button2: %i",state1,state2);	
		newValue=((state1!=Open)?5:0)+((state2!=Open)?-5:0); // sstation take + or - in any value
		typeScreen estate;
		if (role) estate = sstation; else estate = svolume;
		if ((stateScreen  != estate)&&(newValue != 0))
		{    
			if(role) setRelVolume(newValue);else evtStation(-newValue);
			ESP_LOGD(TAG,"Button1: %i, Button2: %i, value: %i",state1,state2,newValue);	
		} 
		if ((stateScreen  == estate)&&(newValue != 0))
		{    
			if(role) evtStation(-newValue); else setRelVolume(newValue);
			ESP_LOGD(TAG,"Button1: %i, Button2: %i, value: %i",state1,state2,newValue);		
		} 			
	}	 
 }

//-----------------------
 // Compute the Buttons
 //----------------------
 void buttonCompute(Button_t *enc,bool role)
{	
	int16_t newValue = 0;
	Button state0 = getButtons(enc,0);	
	if (state0 != Open)
	{
		ESP_LOGD(TAG,"Button0: %i",state0);	
		if (state0 == Clicked) startStop();
		// double click = toggle time
		if (state0 == DoubleClicked) toggletime();	
		if (state0 == Held)
		{  
			timerScreen = 0; 
			if (stateScreen!= (role?sstation:svolume))
			{	
				role?evtStation(newValue):setRelVolume(newValue);
			}
		} 			
	} else
	{
		Button state1 = getButtons(enc,1);
		Button state2 = getButtons(enc,2);
//		ESP_LOGD(TAG,"Button1: %i, Button2: %i",state1,state2);	
		newValue=((state1!=Open)?5:0)+((state2!=Open)?-5:0); // sstation take + or - in any value
		typeScreen estate;
		if (role) estate = sstation; else estate = svolume;
		if ((stateScreen  != estate)&&(newValue != 0))
		{    
			if(role) setRelVolume(newValue);else evtStation(newValue);
		} 
		if ((stateScreen  == estate)&&(newValue != 0))
		{    
			if(role) evtStation(newValue); else setRelVolume(newValue);		
		} 			
	}
}
 
void buttonsLoop()
{	
// button0 = volume control or station when pushed
// button1 = station control or volume when pushed
	if (isButton0) buttonCompute(button0,VCTRL);
	if (isButton1) buttonCompute(button1,SCTRL);
	if (isJoystick0) joystickCompute(joystick0,VCTRL);
	if (isJoystick1) joystickCompute(joystick1,SCTRL);
}

//-----------------------
 // Compute the encoder
 //----------------------

void encoderCompute(Encoder_t *enc,bool role)
{	
	int16_t newValue = - getValue(enc);
	Button newButton = getButton(enc);
	typeScreen estate;
	if (role) estate = sstation; else estate = svolume;
   	// if an event on encoder switch	
	if (newButton != Open)
	{ 
//		wakeLcd();
		// clicked = startstop
		if (newButton == Clicked) {startStop();}
		// double click = toggle time
		if (newButton == DoubleClicked) { toggletime();}
		// switch held and rotated then change station
		if ((newButton == Held)&&(getPinState(enc) == getpinsActive(enc)))
		{   
			timerScreen = 0; 
			if (stateScreen!= (role?sstation:svolume))
				role?evtStation(newValue):setRelVolume(newValue);
		} 			
	}	//else
		// no event on button switch
	{
		if ((stateScreen  != estate)&&(newValue != 0))
		{    
			if(role) setRelVolume(newValue);else evtStation(newValue);
		} 
		if ((stateScreen  == estate)&&(newValue != 0))
		{    
			if(role) evtStation(newValue); else setRelVolume(newValue);			
		} 	
	}		
}

void encoderLoop()
{
// encoder0 = volume control or station when pushed
// encoder1 = station control or volume when pushed
	if (isEncoder0) encoderCompute(encoder0,VCTRL);
	if (isEncoder1) encoderCompute(encoder1,SCTRL);
}



// compute custom IR
bool irCustom(uint32_t evtir, bool repeat)
{
	int i;
	for (i=KEY_UP;i < KEY_MAX;i++)
	{
		if ((evtir == customKey[i][0])||(evtir == customKey[i][1])) break;
	}
	if (i<KEY_MAX)
	{
		switch (i)
		{
			case KEY_UP: evtStation(+1);  break;
			case KEY_LEFT: setRelVolume(-5);  break;
			case KEY_OK: if (!repeat ) stationOk();   break;
			case KEY_RIGHT: setRelVolume(+5);   break;
			case KEY_DOWN: evtStation(-1);  break;
			case KEY_0: if (!repeat ) nbStation('0');   break;  
			case KEY_1: if (!repeat ) nbStation('1');  break;   
			case KEY_2: if (!repeat ) nbStation('2');  break;   
			case KEY_3: if (!repeat ) nbStation('3');  break;   
			case KEY_4: if (!repeat ) nbStation('4');  break;   
			case KEY_5: if (!repeat ) nbStation('5');  break;   
			case KEY_6: if (!repeat ) nbStation('6');  break;   
			case KEY_7: if (!repeat ) nbStation('7');  break;   
			case KEY_8: if (!repeat ) nbStation('8');  break;   
			case KEY_9: if (!repeat ) nbStation('9');  break;
			case KEY_STAR: if (!repeat ) playStationInt(futurNum);  break;
			case KEY_DIESE: if (!repeat )  stopStation();  break;
			case KEY_INFO: if (!repeat ) toggletime();  break;
			default: ;			
		}
		ESP_LOGV(TAG,"irCustom success, evtir %x, i: %d",evtir,i);
		return true;
	}
	return false;
}

 //-----------------------
 // Compute the ir code
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
		
		if (isCustomKey){
			if (irCustom(evtir,evt.repeat_flag)) break;
		}
		else{ // no predefined keys
		switch(evtir)
		{
		case 0xDF2047:
		case 0xDF2002:
		case 0xFF0046: 
		case 0xF70812:  /*(" UP");*/  evtStation(+1);  
		break;
		case 0xDF2049:
		case 0xDF2041:
		case 0xFF0044:
		case 0xF70842:
		case 0xF70815: /*(" LEFT");*/  setRelVolume(-5);  
		break;
		case 0xDF204A:
		case 0xFF0040:
		case 0xF7081E: /*(" OK");*/ if (!evt.repeat_flag ) stationOk();     
		break;
		case 0xDF204B:
		case 0xDF2003:
		case 0xFF0043:
		case 0xF70841:
		case 0xF70814: /*(" RIGHT");*/ setRelVolume(+5);     
		break; 
		case 0xDF204D:
		case 0xDF2009:
		case 0xFF0015:
		case 0xF70813: /*(" DOWN");*/ evtStation(-1);
		break;
		case 0xDF2000:
		case 0xFF0016:
		case 0xF70801: /*(" 1");*/ if (!evt.repeat_flag ) nbStation('1');   
		break;
		case 0xDF2010:
		case 0xFF0019:
		case 0xF70802: /*(" 2");*/ if (!evt.repeat_flag ) nbStation('2');   
		break;
		case 0xDF2011:
		case 0xFF000D:
		case 0xF70803: /*(" 3");*/ if (!evt.repeat_flag ) nbStation('3');   
		break;
		case 0xDF2013:
		case 0xFF000C:
		case 0xF70804: /*(" 4");*/ if (!evt.repeat_flag ) nbStation('4');   
		break;
		case 0xDF2014:
		case 0xFF0018:
		case 0xF70805: /*(" 5");*/ if (!evt.repeat_flag ) nbStation('5');   
		break;
		case 0xDF2015:
		case 0xFF005E:
		case 0xF70806: /*(" 6");*/ if (!evt.repeat_flag ) nbStation('6');   
		break;
		case 0xDF2017:
		case 0xFF0008:
		case 0xF70807: /*(" 7");*/ if (!evt.repeat_flag ) nbStation('7');   
		break;
		case 0xDF2018:
		case 0xFF001C:
		case 0xF70808: /*(" 8");*/ if (!evt.repeat_flag ) nbStation('8');   
		break;
		case 0xDF2019:
		case 0xFF005A:
		case 0xF70809: /*(" 9");*/ if (!evt.repeat_flag ) nbStation('9');   
		break;
		case 0xDF2045:
		case 0xFF0042:
		case 0xF70817: /*(" *");*/   if (!evt.repeat_flag ) playStationInt(futurNum);   
		break;
		case 0xDF201B:
		case 0xFF0052:
		case 0xF70800: /*(" 0");*/ if (!evt.repeat_flag ) nbStation('0');   
		break;
		case 0xDF205B:
		case 0xFF004A:
		case 0xF7081D: /*(" #");*/ if (!evt.repeat_flag )  stopStation();    
		break;
		case 0xDF2007: /*(" Info")*/ if (!evt.repeat_flag ) toggletime();	
		break;
		default:;
		/*SERIALX.println(F(" other button   "));*/
		}// End Case
		}		
	}
}
 
void initButtonDevices()
{
	struct device_settings *device;
	gpio_num_t enca0;
	gpio_num_t encb0;
	gpio_num_t encbtn0;
	gpio_num_t enca1;
	gpio_num_t encb1;
	gpio_num_t encbtn1;	
	gpio_get_encoders(&enca0, &encb0, &encbtn0,&enca1, &encb1, &encbtn1);
	if (enca1 == GPIO_NONE) isEncoder1 = false; //no encoder
	if (enca0 == GPIO_NONE) isEncoder0 = false; //no encoder
	device = getDeviceSettings();
	if (isEncoder0)	encoder0 = ClickEncoderInit(enca0, encb0, encbtn0,((device->options32&T_ENC0)==0)?false:true );	
	if (isEncoder1)	encoder1 = ClickEncoderInit(enca1, encb1, encbtn1,((device->options32&T_ENC1)==0)?false:true );	
	free (device);
	
	gpio_get_buttons(&enca0, &encb0, &encbtn0,&enca1, &encb1, &encbtn1);
	if (enca1 == GPIO_NONE) isButton1 = false; //no encoder
	if (enca0 == GPIO_NONE) isButton0 = false; //no encoder	
	if (isButton0)	button0 = ClickButtonsInit(enca0, encb0, encbtn0);	
	if (isButton1)	button1 = ClickButtonsInit(enca1, encb1, encbtn1 );	
	
	gpio_get_joysticks(&enca0,&enca1);
	if (enca0 == GPIO_NONE) isJoystick0 = false; //no encoder
	if (enca1 == GPIO_NONE) isJoystick1 = false; //no encoder
	if (isJoystick0)	joystick0 = ClickJoystickInit(enca0 );	
	if (isJoystick1)	joystick1 = ClickJoystickInit(enca1);	
	
}


// custom ir code init from hardware nvs partition
#define hardware "hardware"
void customKeyInit()
{
	customKey_t index;
	nvs_handle handle;
	const char *klab[] = {"K_UP","K_LEFT","K_OK","K_RIGHT","K_DOWN","K_0","K_1","K_2","K_3","K_4","K_5","K_6","K_7","K_8","K_9","K_STAR","K_DIESE","K_INFO"};
	
	memset(&customKey,0,sizeof(uint32_t)*2*KEY_MAX); // clear custom
	if (open_partition(hardware, "custom_ir_space",NVS_READONLY,&handle)!= ESP_OK) return;
		
	for (index = KEY_UP; index < KEY_MAX;index++)
	{
		// get the key in the nvs
		isCustomKey |= gpio_get_ir_key(handle,klab[index],(uint32_t*)&(customKey[index][0]),(uint32_t*)&(customKey[index][1]));
		ESP_LOGV(TAG," isCustomKey is %d for %d",isCustomKey,index);
		taskYIELD();
	}
	close_partition(handle,hardware);	
}

// touch loop

void touchLoop()
{
int tx,ty;
	if (haveTouch())
	{
		if ( xpt_read_touch(&tx, &ty, 0)) {
			ESP_LOGD(TAG,"tx: %d, ty: %d",tx,ty);
			uint16_t width = GetWidth();
			uint16_t height = GetHeight();
			uint16_t xdiv2 = width/2;
			uint16_t xdiv6 = width/6;
			uint16_t ydiv2 = height/2;
			uint16_t ydiv6 = height/6;
			uint16_t xl = xdiv2-xdiv6;
			uint16_t xh = xdiv2+xdiv6;
			uint16_t yl = ydiv2-ydiv6;
			uint16_t yh = ydiv2+ydiv6;
			if ((ty > yl) && (ty < yh))
			{
				if ((tx > xl) && (tx < xh)) startStop(); // center
				else {
					if (tx < xl) evtStation(-1); // 
					else evtStation(+1);// evtStation(1);
				}
			} else 
				if (ty < yl) setRelVolume(+5); 
			else setRelVolume(-5); 
			
		}
	}
}


// indirect call to service
IRAM_ATTR void multiService()
{
	if (isEncoder0) service(encoder0);
	if (isEncoder1) service(encoder1);
	if (isButton0) serviceBtn(button0);
	if (isButton1) serviceBtn(button1);
	if (isJoystick0) serviceJoystick(joystick0);
	if (isJoystick1) serviceJoystick(joystick1);
	ServiceAddon();
}
//--------------------
// LCD display task
//--------------------

void task_lcd(void *pvParams)
{
	event_lcd_t evt ; // lcd event	
	event_lcd_t evt1 ; // lcd event	
	ESP_LOGD(TAG, "task_lcd Started, LCD Type %d",lcd_type);
	while (1)
	{	
		if (itLcdOut==1) // switch off the lcd
		{
			sleepLcd();
		}
		if (itAskStime) // time start the time display. Don't do that in interrupt.
		{    
			Screen(stime);
			itAskStime = false;
		}
		if (timerScroll >= 500) //
		{
			if (lcd_type != LCD_NONE) 
			{
				if (stateScreen == smain)
				{
					scroll(); 
				}
				drawScreen();
			}
			timerScroll = 0;
		}  		
		if (event_lcd != NULL)
		while (xQueueReceive(event_lcd, &evt, 0))
		{ 
			if (evt.lcmd != lmeta)
				ESP_LOGV(TAG,"event_lcd: %x",(int)evt.lcmd);
			else
				ESP_LOGV(TAG,"event_lcd: %x  %s",(int)evt.lcmd,evt.lline);
			switch(evt.lcmd)
			{
				case lmeta:
					Screen(smain);
					isColor?metaUcg(evt.lline):metaU8g2(evt.lline);
//					mTscreen= MTREFRESH;
					wakeLcd();	
					break;
				case licy4:
					isColor?icy4Ucg(evt.lline):icy4U8g2(evt.lline);
					break;
				case licy0:
//					wakeLcd(); 					
					isColor?icy0Ucg(evt.lline):icy0U8g2(evt.lline);
					break;
				case lstop:
					Screen(smain);
					isColor?statusUcg(stopped):statusU8g2(stopped);
//					mTscreen= MTNEW;
					wakeLcd();
					break;
				case lnameset:
					Screen(smain);
					isColor?namesetUcg(evt.lline):namesetU8g2(evt.lline);
					isColor?statusUcg("STARTING"):statusU8g2("STARTING");
					mTscreen= MTNEW;
					wakeLcd();
					break;
				case lplay:
					isColor?playingUcg():playingU8g2();						  
					break;
				case lvol:
					// ignore it if the next is a lvol
					if(xQueuePeek(event_lcd, &evt1, 0))
						if (evt1.lcmd == lvol) break;
					isColor?setVolumeUcg(volume):setVolumeU8g2(volume);
					if (dvolume)
					{	Screen(svolume); 
						wakeLcd();
					}
					dvolume = true;									
					timerScreen = 0;					
					break;
				case lovol:
//					wakeLcd();
					dvolume = false; // don't show volume on start station
					break;
				case estation:
					wakeLcd();
					if(xQueuePeek(event_lcd, &evt1, 0))
						if (evt1.lcmd == estation) {evt.lline = NULL;break;}
					Screen(sstation);
					changeStation((uint32_t)evt.lline);	
					evt.lline = NULL;	// just a number			
					break;
				case eclrs:
					isColor?ucg_ClearScreen(&ucg):u8g2_ClearDisplay(&u8g2);
					break;
				case etoggle:
//					wakeLcd();
//					isColor?ucg_ClearScreen(&ucg):u8g2_ClearDisplay(&u8g2);
					(stateScreen==smain)?Screen(stime):Screen(smain);
					mTscreen= MTNEW;
					wakeLcd();
//					drawScreen(); 
					break;
				case edraw:	// force redraw
					itLcdOut = 0;
					mTscreen = MTNEW;
					drawScreen(); 
					break;
				default:;
			}
			if (evt.lline != NULL) free(evt.lline);
			vTaskDelay(1);	
		}
		vTaskDelay(5);	
	}
	vTaskDelete( NULL ); 	
}

//------------------- 
// Main task of addon
//------------------- 
extern void rmt_nec_rx_task();

void task_addon(void *pvParams)
{
	xTaskHandle pxCreatedTask;
	customKeyInit();
	initButtonDevices();
	adcInit();
	
	serviceAddon = &multiService;		; // connect the 1ms interruption
	futurNum = getCurrentStation();
	
	//ir
	// queue for events of the IR nec rx
	event_ir = xQueueCreate(5, sizeof(event_ir_t));
	ESP_LOGD(TAG,"event_ir: %x",(int)event_ir);
	// queue for events of the lcd
	event_lcd = xQueueCreate(20, sizeof(event_lcd_t));
	ESP_LOGD(TAG,"event_lcd: %x",(int)event_lcd);	
	
	xTaskCreatePinnedToCore(rmt_nec_rx_task, "rmt_nec_rx_task", 2148, NULL, PRIO_RMT, &pxCreatedTask,CPU_RMT);
	ESP_LOGI(TAG, "%s task: %x","rmt_nec_rx_task",(unsigned int)pxCreatedTask);		;
	xTaskCreatePinnedToCore (task_lcd, "task_lcd", 2200, NULL, PRIO_LCD, &pxTaskLcd,CPU_LCD); 
	ESP_LOGI(TAG, "%s task: %x","task_lcd",(unsigned int)pxTaskLcd);
	getTaskLcd(&pxTaskLcd); // give the handle to xpt
	vTaskDelay(1);	
	wakeLcd();
	
	while (1)
	{
		adcLoop();  // compute the adc keyboard
		encoderLoop(); // compute the encoder
		buttonsLoop(); // compute the buttons and joysticks
		irLoop();  // compute the ir		
		touchLoop();
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
		
		if (timerScreen >= 3) //  sec timeout transient screen
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
					playStationInt(futurNum);
				}				
			}
		}

		vTaskDelay(10);
	}	
	vTaskDelete( NULL ); 
}

// force a new dt ntp fetch
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
	evt.lcmd = -1;
  char* ici;
 
 ////// Meta title  ##CLI.META#: 
   if ((ici=strstr(line,"META#: ")) != NULL)
   {     
		evt.lcmd = lmeta;
		evt.lline = malloc(strlen(ici)+1);
		//evt.lline = NULL;
		strcpy(evt.lline,ici);
//		xQueueSend(event_lcd,&evt, 0);
   } else 
 ////// ICY4 Description  ##CLI.ICY4#:
    if ((ici=strstr(line,"ICY4#: ")) != NULL)
    {
		evt.lcmd = licy4;
		evt.lline = malloc(strlen(ici)+1);
		//evt.lline = NULL;
		strcpy(evt.lline,ici);
//		xQueueSend(event_lcd,&evt, 0);
    } else 
 ////// ICY0 station name   ##CLI.ICY0#:
   if ((ici=strstr(line,"ICY0#: ")) != NULL)
   {
		evt.lcmd = licy0;
		evt.lline = malloc(strlen(ici)+1);
		//evt.lline = NULL;
		strcpy(evt.lline,ici);
//		xQueueSend(event_lcd,&evt, 0);
   } else
 ////// STOPPED  ##CLI.STOPPED#  
   if ((ici=strstr(line,"STOPPED")) != NULL)
   {
		state = false;	  
 		evt.lcmd = lstop;
		evt.lline = NULL;
//		xQueueSend(event_lcd,&evt, 0);
   }    
   else  
 //////Nameset    ##CLI.NAMESET#:
   if ((ici=strstr(line,"MESET#: ")) != NULL)  
   {   
	  	evt.lcmd = lnameset;
		evt.lline = malloc(strlen(ici)+1);
		//evt.lline = NULL;
		strcpy(evt.lline,ici);
//		xQueueSend(event_lcd,&evt, 0);
   } else
 //////Playing    ##CLI.PLAYING#
   if ((ici=strstr(line,"YING#")) != NULL)  
   {
		state = true;
 		evt.lcmd = lplay;
		evt.lline = NULL;
//		xQueueSend(event_lcd,&evt, 0);
   } else
   //////Volume   ##CLI.VOL#:
   if ((ici=strstr(line,"VOL#:")) != NULL)  
   {
	   if (*(ici+6) != 'x') // ignore help display.
	   {
		volume = atoi(ici+6);
 		evt.lcmd = lvol;
		evt.lline = NULL;//atoi(ici+6);
//		xQueueSend(event_lcd,&evt, 0);
	   }
   } else
  //////Volume offset    ##CLI.OVOLSET#:
   if ((ici=strstr(line,"OVOLSET#:")) != NULL)  
   {
	    evt.lcmd = lovol;
		evt.lline = NULL;
//		xQueueSend(event_lcd,&evt, 0);
   }
   if (evt.lcmd != -1) xQueueSend(event_lcd,&evt, 0);
   free (line);
}

