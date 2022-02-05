/******************************************************************************
 * Copyright 2013-2015 Espressif Systems
 *
 * FileName: user_main.c
 *
 * Description: Routines to use a SPI RAM chip as a big FIFO buffer. Multi-
 * thread-aware: the reading and writing can happen in different threads and
 * will block if the fifo is empty and full, respectively.
 *
 * Modification history:
 *     2015/06/02, v1.0 File created.
*******************************************************************************/
#include "esp_system.h"
#include "string.h"
#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

#include "spiram_fifo.h"
//#include "spiram.h"
//#include "esp_heap_trace.h"
#include "esp_heap_caps.h"
//#include "playerconfig.h"
#define FAKE_SPI_BUFF

//#define SPIREADSIZE 1024
#define SPIREADSIZE 1024

static unsigned fifoRpos;
static unsigned fifoWpos;
static unsigned fifoFill;
//static xSemaphoreHandle semCanRead;
//static xSemaphoreHandle semCanWrite;
static xSemaphoreHandle mux = NULL;
static long fifoOvfCnt, fifoUdrCnt;

//Low watermark where we restart the reader thread.
//#define FIFO_LOWMARK (16*1024)
#define FIFO_LOWMARK (512)

#ifdef FAKE_SPI_BUFF
//Re-define a bunch of things so we use the internal buffer
#undef SPIRAMSIZE
//static  char fakespiram[SPIRAMSIZE];
static  char *fakespiram;

#define spiRamWrite(pos, buf, n) memcpy(&fakespiram[pos], buf, n)
#define spiRamRead(pos, buf, n) memcpy(buf, &fakespiram[pos], n)
#endif

static unsigned SPIRAMSIZE = (30*1024);

void setSPIRAMSIZE(unsigned size)
{
	SPIRAMSIZE = size;
}
unsigned getSPIRAMSIZE()
{
	return SPIRAMSIZE ;
}

//Initialize the FIFO
void* spiRamFifoInit() {
	fakespiram = malloc(SPIRAMSIZE);
	fifoRpos=0;
	fifoWpos=0;
	fifoFill=0;
	fifoOvfCnt=0;
	fifoUdrCnt=0;
//	vSemaphoreCreateBinary(semCanRead);
//	vSemaphoreCreateBinary(semCanWrite);
if (mux == NULL)
		mux=xSemaphoreCreateMutex();
//	spiRamInit();
	return ( fakespiram);
}

void spiRamFifoReset() {
	xSemaphoreTake(mux, portMAX_DELAY);
	fifoRpos=0;
	fifoWpos=0;
	fifoFill=0;
	fifoOvfCnt=0;
	fifoUdrCnt=0;
	memset( fakespiram, 0, SPIRAMSIZE );
//	xSemaphoreGive(semCanWrite);
//	xSemaphoreTake(semCanRead, portMAX_DELAY);
	xSemaphoreGive(mux);
}

//Read bytes from the FIFO
void spiRamFifoRead(char *buff, unsigned len) {
//	unsigned n;
	while (len > 0) {
//		heap_caps_check_integrity_all(true) ;
		unsigned n = len;
//		unsigned fifomFill;
		//printf("i%d\n",n);
		if (xSemaphoreTake(mux, portMAX_DELAY))
		{
		if (n>SPIREADSIZE) n=SPIREADSIZE;			//don't read more than SPIREADSIZE
		if (n>(SPIRAMSIZE-fifoRpos)) n = SPIRAMSIZE - fifoRpos; //don't read past end of buffer
		if (fifoFill < n) {
			//printf("FIFO empty.\n");
			//Drat, not enough data in FIFO. Wait till there's some written and try again.
			fifoUdrCnt++;
			xSemaphoreGive(mux);
//			if (fifomFill < FIFO_LOWMARK) xSemaphoreTake(semCanRead, portMAX_DELAY);
			vTaskDelay(10);
		} else {
			//Read the data.
			spiRamRead(fifoRpos, buff, n);
			buff += n;
			len -= n;
			fifoFill -= n;
			fifoRpos += n;
			if (fifoRpos>=SPIRAMSIZE) fifoRpos=0;
			//printf("r%d\n",n);
			xSemaphoreGive(mux);
//			xSemaphoreGive(semCanWrite); //Indicate writer thread there's some free room in the fifo
		}
		} else {printf("spiRamFifoRead MUX take failed\n"); }
	}
}

//Write bytes to the FIFO
void spiRamFifoWrite(const char *buff, unsigned buffLen) {
//	unsigned n;
	while (buffLen > 0) {
		unsigned n = buffLen;
		if (xSemaphoreTake(mux, portMAX_DELAY))
		{
		// don't read more than SPIREADSIZE
		if (n > SPIREADSIZE) n = SPIREADSIZE;

		// don't read past end of buffer
		if (n > (SPIRAMSIZE - fifoWpos)) {
			n = SPIRAMSIZE - fifoWpos;
		}

		if ((SPIRAMSIZE - fifoFill) < n) {
            //printf("FIFO full.\n");
			// Drat, not enough free room in FIFO. Wait till there's some read and try again.
			fifoOvfCnt++;
			xSemaphoreGive(mux);
//			printf("FIFO full.\n");
//			xSemaphoreTake(semCanWrite, portMAX_DELAY);
			vTaskDelay(10);
		} else {
			// Write the data.
			spiRamWrite(fifoWpos, buff, n);
			buff += n;
			buffLen -= n;
			fifoFill += n;
			fifoWpos += n;
			if (fifoWpos >= SPIRAMSIZE) fifoWpos = 0;
			//printf("w%d\n",n);
			xSemaphoreGive(mux);
//			xSemaphoreGive(semCanRead); // Tell reader thread there's some data in the fifo.
		}
		} else {printf(" spiRamFifoWrite MUX take failed\n"); }
	}
}

//Get amount of bytes in use
unsigned spiRamFifoFill() {
//	unsigned ret;
	xSemaphoreTake(mux, portMAX_DELAY);
	unsigned ret=fifoFill;
	xSemaphoreGive(mux);
	return ret;

}

unsigned spiRamFifoFree() {
	return (SPIRAMSIZE-spiRamFifoFill());
}

void spiRamFifoDestroy() {
	
	if (fakespiram) free (fakespiram);
}
unsigned spiRamFifoLen() {
	return SPIRAMSIZE;
}

long spiRamGetOverrunCt() {
//	long ret;
	xSemaphoreTake(mux, portMAX_DELAY);
	 long ret=fifoOvfCnt;
	xSemaphoreGive(mux);
	return ret;
}

long spiRamGetUnderrunCt() {
//	long ret;
	xSemaphoreTake(mux, portMAX_DELAY);
	long ret=fifoUdrCnt;
	xSemaphoreGive(mux);
	return ret;
}