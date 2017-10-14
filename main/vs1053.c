/**
  ***********************************************************************************************************************
  * @file    VS1053.c
  * @author  Piotr Sperka
  * @date    07.08.2015
  * @brief   This file provides VS1053 usage and control functions. Based on VS1003 library by Przemyslaw Stasiak.
  * Copyright 2017 karawin (http://www.karawin.fr) for KaRadio32
  * added control treble, bass and spacialisation
  ***********************************************************************************************************************
*/

/** @addtogroup VS1053
  * @{
  */
#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE

#include "vs1053.h"
#include "gpio.h"
#include "eeprom.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "driver/spi_master.h"
#include "soc/gpio_struct.h"
#include "driver/gpio.h"
#include <math.h>
#include "interface.h"
#include "app_main.h"
#include "audio_player.h"
#include "spiram_fifo.h"
#include "common_buffer.h"

extern void  LoadUserCodes(void);

#define TAG "vs1053"

int vsVersion ; // the version of the chip
//	SS_VER is 0 for VS1001, 1 for VS1011, 2 for VS1002, 3 for VS1003, 4 for VS1053 and VS8053, 5 for VS1033, 7 for VS1103, and 6 for VS1063.
//char strvMODE[] STORE_ATTR ICACHE_RODATA_ATTR = {"SCI_Mode (0x4800) = 0x%X\n"};

const char strvI2S[] = {"I2S Speed: %d\n"};

spi_device_handle_t vsspi;  // the device handle of the vs1053 spi
spi_device_handle_t hvsspi;  // the device handle of the vs1053 spi high speed

xSemaphoreHandle sSPI = NULL;

uint8_t spi_take_semaphore() {
	if(sSPI) if(xSemaphoreTake(sSPI, portMAX_DELAY)) return 1;
	return 0;
}

void spi_give_semaphore() {
	if(sSPI) xSemaphoreGive(sSPI);
}

void VS1053_spi_init(uint8_t spi_no){
	esp_err_t ret;
	
	if(!sSPI) vSemaphoreCreateBinary(sSPI);
	spi_give_semaphore();	

	if(spi_no > 1) return; //Only SPI and HSPI are valid spi modules. 
	
	spi_bus_config_t buscfg={
        .miso_io_num=PIN_NUM_MISO,
        .mosi_io_num=PIN_NUM_MOSI,
        .sclk_io_num=PIN_NUM_CLK,
        .quadwp_io_num=-1,
        .quadhd_io_num=-1,
		.max_transfer_sz = 64
		
	};		
	ret=spi_bus_initialize(HSPI_HOST, &buscfg, 0);	 // no dma	
	assert(ret==ESP_OK);	
}

int getVsVersion() { return vsVersion;}

void VS1053_HW_init(){
	spi_device_interface_config_t devcfg={
        .clock_speed_hz=2*1000*1000,               //Clock out at 2 MHz
		.command_bits = 8,
		.address_bits = 8,
		.dummy_bits = 0,
		.duty_cycle_pos = 0,
		.cs_ena_pretrans = 0,
		.cs_ena_posttrans = 0,
		//.flags = SPI_DEVICE_HALFDUPLEX,	
        .mode=0,                         //SPI mode 
        .spics_io_num= PIN_NUM_XCS,               //XCS pin
        .queue_size=4,                          //We want to be able to queue x transactions at a time
        //.pre_cb=lcd_spi_pre_transfer_callback,  //Specify pre-transfer callback to handle D/C line
        .pre_cb=NULL,  //Specify pre-transfer callback to handle D/C line
		.post_cb = NULL
	};	
	
 	VS1053_spi_init(HSPI_HOST);
	
	//slow speed
	ESP_ERROR_CHECK(spi_bus_add_device(HSPI_HOST, &devcfg, &vsspi));
	
	//high speed	
	devcfg.clock_speed_hz = 6000000;
	devcfg.spics_io_num= PIN_NUM_XDCS;               //XDCS pin
	devcfg.command_bits = 0;
	devcfg.address_bits = 0;
	ESP_ERROR_CHECK(spi_bus_add_device(HSPI_HOST, &devcfg, &hvsspi));
	
	//Initialize non-SPI GPIOs
    gpio_set_direction(PIN_NUM_RST, GPIO_MODE_OUTPUT);
	gpio_set_direction(PIN_NUM_DREQ, GPIO_MODE_INPUT);
	gpio_set_pull_mode(PIN_NUM_DREQ, GPIO_PULLUP_ENABLE); //usefull if no vs1053 test
	
}

int VS1053_spi_write_char(spi_device_handle_t ivsspi, uint8_t *cbyte, uint16_t len)
{
	esp_err_t ret=0;
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));       //Zero out the transaction
	//t.flags |= SPI_TRANS_USE_RXDATA;
	t.tx_buffer = cbyte;	
    t.length= len*8;                     //Command is 4 bytes *8 =32 bits
    //t.rxlength=0;	
    ESP_ERROR_CHECK(ret=spi_device_transmit(ivsspi, &t));  //Transmit!
	//printf("VS1053_spi_write val: %x  rxlen: %x \n",*cbyte,t.rxlength);
    return ret;
}


void ControlReset(uint8_t State){
	gpio_set_level(PIN_NUM_RST, State);
}

uint8_t VS1053_checkDREQ() {
	return gpio_get_level(PIN_NUM_DREQ);
}


void VS1053_WriteRegister(uint8_t addressbyte, uint8_t highbyte, uint8_t lowbyte)
{
	spi_take_semaphore();
	while(VS1053_checkDREQ() == 0)taskYIELD ();

    spi_transaction_t t;
    memset(&t, 0, sizeof(t));       //Zero out the transaction
	t.flags |= SPI_TRANS_USE_TXDATA;
	t.cmd = VS_WRITE_COMMAND;
	t.addr = addressbyte;
	t.tx_data[0] = highbyte;
	t.tx_data[1] = lowbyte;		
    t.length= 16;
    ESP_ERROR_CHECK(spi_device_transmit(vsspi, &t));  //Transmit!	
	while(VS1053_checkDREQ() == 0);
	spi_give_semaphore();
}

void VS1053_WriteRegister16(uint8_t addressbyte, uint16_t value)
{
	spi_take_semaphore();
	while(VS1053_checkDREQ() == 0)taskYIELD ();

    spi_transaction_t t;
    memset(&t, 0, sizeof(t));       //Zero out the transaction
	t.flags |= SPI_TRANS_USE_TXDATA;
	t.cmd = VS_WRITE_COMMAND;
	t.addr = addressbyte;
	t.tx_data[0] = (value>>8)&0xff;	;
	t.tx_data[1] = value&0xff;		
    t.length= 16;
    ESP_ERROR_CHECK(spi_device_transmit(vsspi, &t));  //Transmit!	
	while(VS1053_checkDREQ() == 0);
	spi_give_semaphore();
}

uint16_t VS1053_ReadRegister(uint8_t addressbyte){
	spi_take_semaphore();
	uint16_t result;
	while(VS1053_checkDREQ() == 0)taskYIELD ();

    spi_transaction_t t;
    uint16_t data;
    memset(&t, 0, sizeof(t));       //Zero out the transaction
	t.length=16;   
	t.cmd = VS_READ_COMMAND;
	t.addr = addressbyte;
    t.rx_buffer=&data;
    ESP_ERROR_CHECK(spi_device_transmit(vsspi, &t));  //Transmit!
	result =  (((data&0xFF)<<8) | ((data>>8)&0xFF)) ;  	
	while(VS1053_checkDREQ() == 0);
	spi_give_semaphore();
	return result;
}


void WriteVS10xxRegister(unsigned short addr,unsigned short val)
{
	VS1053_WriteRegister((uint8_t)addr&0xff, (uint8_t)((val&0xFF00)>>8), (uint8_t)(val&0xFF));
}


void VS1053_ResetChip(){
	uint8_t ff;
	ControlReset(SET);
	VS1053_spi_write_char(vsspi,&ff,1);
	vTaskDelay(200);
	ControlReset(RESET);
	vTaskDelay(10);
	if (VS1053_checkDREQ() == 1) return;
	vTaskDelay(100);
//	while(VS1053_checkDREQ() == 0)taskYIELD ();
//	vTaskDelay(100);
}

uint16_t MaskAndShiftRight(uint16_t Source, uint16_t Mask, uint16_t Shift){
	return ( (Source & Mask) >> Shift );
}

void VS1053_regtest()
{
	int MP3Status = VS1053_ReadRegister(SPI_STATUS);
	int MP3Mode = VS1053_ReadRegister(SPI_MODE);
	int MP3Clock = VS1053_ReadRegister(SPI_CLOCKF);
	printf(PSTR("SCI_Status  = 0x%X\n"),MP3Status);
	printf(PSTR("SCI_Mode (0x4800) = 0x%X\n"),MP3Mode);
	printf("SCI_ClockF = 0x%X\n",MP3Clock);
//	vsVersion = (MP3Status >> 4) & 0x000F; //Mask out only the four version bits
	printf("VS Version (VS1053 is 4) = %d\n",vsVersion);
	//The 1053B should respond with 4. VS1001 = 0, VS1011 = 1, VS1002 = 2, VS1003 = 3, VS1054 = 4
}

void VS1053_I2SRate(uint8_t speed){ // 0 = 48kHz, 1 = 96kHz, 2 = 128kHz
    if (speed > 2) speed = 0;
	if (vsVersion != 4) return;
	VS1053_WriteRegister16(SPI_WRAMADDR, 0xc040); //address of GPIO_ODATA is 0xC017	
	VS1053_WriteRegister16(SPI_WRAM, 0x0008|speed); //
	VS1053_WriteRegister16(SPI_WRAMADDR, 0xc040); //address of GPIO_ODATA is 0xC017	
	VS1053_WriteRegister16(SPI_WRAM, 0x000C|speed); //
	printf(strvI2S,speed);
}

void VS1053_DisableAnalog(){
	// disable analog output
	VS1053_WriteRegister16(SPI_VOL,0xFFFF);
}

// reduce the chip consumption
void VS1053_LowPower(){
	VS1053_WriteRegister16(SPI_CLOCKF,0x0000); // 
}

// normal chip consumption
void VS1053_HighPower(){
   if (vsVersion == 4) // only 1053  	
		VS1053_WriteRegister16(SPI_CLOCKF,0xB800); // SC_MULT = x1, SC_ADD= x1
	else	
		VS1053_WriteRegister16(SPI_CLOCKF,0xb000);	
}


void VS1053_Start(){
	struct device_settings *device;
	int i = 0;
	
	VS1053_ResetChip();
	while(VS1053_checkDREQ() == 0) 
	{
		if (i++ >= 20) {vsVersion = 0; ESP_LOGE(TAG,"NO VS1053 detected");return;}
		vTaskDelay(1);
	}	
// these 4 lines makes board to run on mp3 mode, no soldering required anymore
	VS1053_WriteRegister16(SPI_WRAMADDR, 0xc017); //address of GPIO_DDR is 0xC017
	VS1053_WriteRegister16(SPI_WRAM, 0x0003); //GPIO_DDR=3
	VS1053_WriteRegister16(SPI_WRAMADDR, 0xc019); //address of GPIO_ODATA is 0xC019
	VS1053_WriteRegister16(SPI_WRAM, 0x0000); //GPIO_ODATA=0
	vTaskDelay(100);
	
	int MP3Status = VS1053_ReadRegister(SPI_STATUS);
	vsVersion = (MP3Status >> 4) & 0x000F; //Mask out only the four version bits
//0 for VS1001, 1 for VS1011, 2 for VS1002, 3 for VS1003, 4 for VS1053 and VS8053,
//5 for VS1033, 7 for VS1103, and 6 for VS1063	
   if (vsVersion == 4) // only 1053b  	
//		VS1053_WriteRegister(SPI_CLOCKF,0x78,0x00); // SC_MULT = x3, SC_ADD= x2
		VS1053_WriteRegister16(SPI_CLOCKF,0xB800); // SC_MULT = x1, SC_ADD= x1
//		VS1053_WriteRegister(SPI_CLOCKF,0x90,0x00); // SC_MULT = x3.5, SC_ADD= x1.5
	else	
		VS1053_WriteRegister16(SPI_CLOCKF,0xB000);
	
	VS1053_SoftwareReset();
	printf("mode: %x\n", (SM_SDINEW|SM_LINE1)| SM_LAYER12);
	while(VS1053_checkDREQ() == 0)taskYIELD ();
	
	VS1053_regtest();
	
	device = getDeviceSettings();
	printf("device: %x\n",(int)device);
	if (device != NULL)
	{	
	// enable I2C dac output
		if (vsVersion == 4) // only 1053
		{
			VS1053_WriteRegister16(SPI_WRAMADDR, 0xc017); //
			VS1053_WriteRegister16(SPI_WRAM, 0x00F0); //
			VS1053_I2SRate(device->i2sspeed);	

	// plugin patch
			if  ((device->options&T_PATCH)==0) 
			{	
				LoadUserCodes() ;	// vs1053b patch and admix
				VS1053_SetVolumeLine(-31);
				VS1053_Admix(false);
			}
		}
		vTaskDelay(10);
		printf(PSTR("volume: %d\n"),device->vol);
		setIvol( device->vol);
		VS1053_SetVolume( device->vol);	
		VS1053_SetTreble(device->treble);
		VS1053_SetBass(device->bass);
		VS1053_SetTrebleFreq(device->freqtreble);
		VS1053_SetBassFreq(device->freqbass);
		VS1053_SetSpatial(device->spacial);
		free(device);
	}
}

int VS1053_SendMusicBytes(uint8_t* music, uint16_t quantity){
	if(quantity ==0) return 0;
	int oo = 0;
	spi_take_semaphore();
	while(VS1053_checkDREQ() == 0) taskYIELD ();
	while(quantity)
	{
		if(VS1053_checkDREQ()) 
		{
			int t = quantity;
			if(t > 32) t = 32;	
			VS1053_spi_write_char(hvsspi, &music[oo], t);
			oo += t;
			quantity -= t;
		} 
	}
	spi_give_semaphore();
	return oo;
}

void VS1053_SoftwareReset(){
	VS1053_WriteRegister(SPI_MODE, (SM_SDINEW|SM_LINE1)>>8,SM_RESET);
	VS1053_WriteRegister(SPI_MODE, (SM_SDINEW|SM_LINE1)>>8, SM_LAYER12); //mode 
}

// activate or stop admix plugin (true = activate)
void VS1053_Admix(bool val) {
	uint16_t Mode = VS1053_ReadRegister(SPI_MODE);
	VS1053_WriteRegister(SPI_MODE, MaskAndShiftRight(Mode|SM_LINE1,0xFF00,8), (Mode & 0x00FF));
	if (val) 
		VS1053_WriteRegister16(SPI_AIADDR,0x0F00);
	else
		VS1053_WriteRegister16(SPI_AIADDR,0x0F01);
}

// Set the volume of the line1 (for admix plugin) // -31 to -3
void VS1053_SetVolumeLine(int16_t vol){
	if (vol > -3) vol = -3;
	if (vol < -31) vol = -31;
	VS1053_WriteRegister(SPI_AICTRL0,(vol&0xFF00)>>8,vol&0xFF);
}

// Get volume and convert it in log one
uint8_t VS1053_GetVolume(){
uint8_t i,j;
uint8_t value =  VS1053_ReadRegister(SPI_VOL) & 0x00FF;
	for (i = 0;i< 255; i++)
	{
		j = (log10(255/((float)i+1)) * 105.54571334); // magic no?
//		printf("i=%d  j=%d value=%d\n",i,j,value);
		if (value == j )
		  return i;
	}	
	return 127;
}

// rough volume
uint8_t VS1053_GetVolumeLinear(){
	return VS1053_ReadRegister(SPI_VOL) & 0x00FF;
}

/**
 * Function sets the same volume level to both channels.
 * @param xMinusHalfdB describes damping level as a multiple
 * 		of 0.5dB. Maximum volume is 0 and silence is 0xFEFE.
 * convert the log one to rough one and set it invs1053
 */
void VS1053_SetVolume(uint8_t xMinusHalfdB){
uint8_t value = (log10(255/((float)xMinusHalfdB+1)) * 105.54571334);	
//printf("setvol: %d\n",value);
	if (value == 255) value = 254;
//printf("xMinusHalfdB=%d  value=%d\n",xMinusHalfdB,value);
	VS1053_WriteRegister(SPI_VOL,value,value);
}

/**
 * Functions returns level of treble enhancement.
 * @return Returned value describes enhancement in multiplies
 * 		of 1.5dB. 0 value means no enhancement, 8 max (12dB).
 */
int8_t	VS1053_GetTreble(){
	int8_t  treble = (VS1053_ReadRegister(SPI_BASS) & 0xF000) >> 12;
	if ( (treble&0x08)) treble |= 0xF0; // negative value
	return ( treble);
}

/**
 * Sets treble level.
 * @note If xOneAndHalfdB is greater than max value, sets treble
 * 		to maximum.
 * @param xOneAndHalfdB describes level of enhancement. It is a multiplier
 * 		of 1.5dB. 0 - no enhancement, -8 minimum -12dB , 7 - maximum, 10.5dB.
 * @return void
 */
void VS1053_SetTreble(int8_t xOneAndHalfdB){
	uint16_t bassReg = VS1053_ReadRegister(SPI_BASS);
	
	if (( xOneAndHalfdB <= 7) && ( xOneAndHalfdB >=-8))
		VS1053_WriteRegister( SPI_BASS, MaskAndShiftRight(bassReg,0x0F00,8) | (xOneAndHalfdB << 4), bassReg & 0x00FF );
}

/**
 * Sets low limit frequency of treble enhancer.
 * @note new frequency is set only if argument is valid.
 * @param xkHz The lowest frequency enhanced by treble enhancer.
 * 		Values from 0 to 15 (in kHz)
 * @return void
 */
void VS1053_SetTrebleFreq(uint8_t xkHz){
	uint16_t bassReg = VS1053_ReadRegister(SPI_BASS);
	if ( xkHz <= 15 )
		VS1053_WriteRegister( SPI_BASS, MaskAndShiftRight(bassReg,0xF000,8) | xkHz, bassReg & 0x00FF );
}
int8_t	VS1053_GetTrebleFreq(){
	return ( (VS1053_ReadRegister(SPI_BASS) & 0x0F00) >> 8);
}

/**
 * Returns level of bass boost in dB.
 * @return Value of bass enhancement from 0 (off) to 15(dB).
 */
uint8_t	VS1053_GetBass(){
	return ( (VS1053_ReadRegister(SPI_BASS) & 0x00F0) >> 4);
}

/**
 * Sets bass enhancement level (in dB).
 * @note If xdB is greater than max value, bass enhancement is set to its max (15dB).
 * @param xdB Value of bass enhancement from 0 (off) to 15(dB).
 * @return void
 */
void VS1053_SetBass(uint8_t xdB){
	uint16_t bassReg = VS1053_ReadRegister(SPI_BASS);
	if (xdB <= 15)
		VS1053_WriteRegister(SPI_BASS, (bassReg & 0xFF00) >> 8, (bassReg & 0x000F) | (xdB << 4) );
	else
		VS1053_WriteRegister(SPI_BASS, (bassReg & 0xFF00) >> 8, (bassReg & 0x000F) | 0xF0 );
}

/**
 * Sets low limit frequency of bass enhancer.
 * @note new frequency is set only if argument is valid.
 * @param xTenHz The lowest frequency enhanced by bass enhancer.
 * 		Values from 2 to 15 ( equal to 20 - 150 Hz).
 * @return void
 */
void VS1053_SetBassFreq(uint8_t xTenHz){
	uint16_t bassReg = VS1053_ReadRegister(SPI_BASS);
	if (xTenHz >=2 && xTenHz <= 15)
		VS1053_WriteRegister(SPI_BASS, MaskAndShiftRight(bassReg,0xFF00,8), (bassReg & 0x00F0) | xTenHz );
}

uint8_t	VS1053_GetBassFreq(){
	return ( (VS1053_ReadRegister(SPI_BASS) & 0x000F) );
}

uint8_t	VS1053_GetSpatial(){
	if (vsVersion != 4) return 0;
	uint16_t spatial = (VS1053_ReadRegister(SPI_MODE) & 0x0090) >>4;
	return ((spatial&1) | ((spatial>>2) & 2));
}

void VS1053_SetSpatial(uint8_t num){
	if (vsVersion != 4) return ;
	uint16_t spatial = VS1053_ReadRegister(SPI_MODE);
	if (num <= 3)
	{	
		num = (((num <<2)&8) | (num&1))<<4;
		VS1053_WriteRegister(SPI_MODE, MaskAndShiftRight(spatial,0xFF00,8), (spatial & 0x006F) | num );
	}	
}

uint16_t VS1053_GetDecodeTime(){
	return VS1053_ReadRegister(SPI_DECODE_TIME);
}

uint16_t VS1053_GetBitrate(){
	uint16_t bitrate = (VS1053_ReadRegister(SPI_HDAT0) & 0xf000) >> 12;
	uint8_t ID = (VS1053_ReadRegister(SPI_HDAT1) & 0x18) >> 3;
	uint16_t res;
	if (ID == 3)
	{	res = 32;
		while(bitrate>13)
		{
			res+=64;
			bitrate--;
		}
		while (bitrate>9)
		{
			res+=32;
			bitrate--;
		}
		while (bitrate>5)
		{
			res+=16;
			bitrate--;
		}
		while (bitrate>1)
		{
			res+=8;
			bitrate--;
		}
	}
	else
	{	res = 8;

		while (bitrate>8)
		{
			res+=16;
			bitrate--;
		}
		while (bitrate>1)
		{
			res+=8;
			bitrate--;
		}
	}
	return res;
}

uint16_t VS1053_GetSampleRate(){
	return (VS1053_ReadRegister(SPI_AUDATA) & 0xFFFE);
}

/* to start and stop a new stream */
void VS1053_flush_cancel(uint8_t mode) {  // 0 only fillbyte  1 before play    2 cancel play
//  int8_t endFillByte = (int8_t) (Mp3ReadWRAM(para_endFillByte) & 0xFF);
	int8_t endFillByte ;
	int16_t y;
	uint8_t buf[513];	
	if (mode != 2)
	{
		VS1053_WriteRegister(SPI_WRAMADDR,MaskAndShiftRight(para_endFillByte,0xFF00,8), (para_endFillByte & 0x00FF) );		
		endFillByte = (int8_t) VS1053_ReadRegister(SPI_WRAM) & 0xFF;
		for (y = 0; y < 513; y++) buf[y] = endFillByte;
	}

  if (mode != 0) //set CANCEL
  {
	uint16_t spimode = VS1053_ReadRegister(SPI_MODE)| SM_CANCEL;
  // set CANCEL
	VS1053_WriteRegister(SPI_MODE,MaskAndShiftRight(spimode,0xFF00,8), (spimode & 0x00FF) );
	// wait CANCEL
	y = 0;
	while (VS1053_ReadRegister(SPI_MODE)& SM_CANCEL)
	{	  
		if (mode == 1) VS1053_SendMusicBytes( buf, 32); //1
		else vTaskDelay(1); //2  
//		printf ("Wait CANCEL clear\n");
		if (y++ > 200) 
		{
			if (mode == 1) VS1053_Start();
			break;
		}		
	}	
	VS1053_WriteRegister(SPI_WRAMADDR,MaskAndShiftRight(para_endFillByte,0xFF00,8), (para_endFillByte & 0x00FF) );
	endFillByte = (int8_t) VS1053_ReadRegister(SPI_WRAM) & 0xFF;
	for (y = 0; y < 513; y++) buf[y] = endFillByte;	
	for ( y = 0; y < 4; y++)	VS1053_SendMusicBytes( buf, 513); // 4*513 = 2052
  } else
  {
	for ( y = 0; y < 4; y++)	VS1053_SendMusicBytes( buf, 513); // 4*513 = 2052
  }	  
}


IRAM_ATTR void vsTask(void *pvParams) { 
#define VSTASKBUF	1024
	portBASE_TYPE uxHighWaterMark;
	uint8_t b[VSTASKBUF];
//	struct device_settings *device;
	uint16_t size ,s;

	player_t *player = pvParams;
	
	while(1) {
		// stop requested, terminate immediately
        if(player->decoder_command == CMD_STOP) {
            break;
        }		
//		if(playing)
		{			
			//size = bufferRead(b, VSTASKBUF);
			size = min(VSTASKBUF, spiRamFifoFill());
			spiRamFifoRead((char*)b, size);
			s = 0; 			
			while(s < size) 
			{
				s += VS1053_SendMusicBytes(b+s, size-s);	
			}
			vTaskDelay(2);	
		} 
/*		else 
		{
			vTaskDelay(40);				
//			uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
//			printf("watermark vstask: %x  %d\n",uxHighWaterMark,uxHighWaterMark);			
		}	
*/
	}
	uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
	ESP_LOGI(TAG,"watermark: %x  %d",uxHighWaterMark,uxHighWaterMark);	
	
	spiRamFifoReset();
    player->decoder_status = STOPPED;
    player->decoder_command = CMD_NONE;
    ESP_LOGD(TAG, "Decoder vs1053 stopped.\n");
	vTaskDelete(NULL);
	
}


