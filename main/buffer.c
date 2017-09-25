/*
 * Copyright 2016 Piotr Sperka (http://www.piotrsperka.info)
*/

//#include "buffer.h"
#include "esp_system.h"

/*
#ifndef USE_EXTERNAL_SRAM
	uint8_t buffer[BUFFER_SIZE];
#endif
*/
uint32_t BUFFER_SIZE;
uint8_t *buffer;
uint32_t wptr = 0;
uint32_t rptr = 0;
uint8_t bempty = 1;

void initBuffer()
{
//		 BUFFER_SIZE = 12960;
//		 BUFFER_SIZE = 14080;
		 BUFFER_SIZE = 1;
		 buffer = malloc(BUFFER_SIZE);	 	 
}
uint32_t getBufferFree() {
	if(wptr > rptr ) return BUFFER_SIZE - wptr + rptr;
	else if(wptr < rptr) return rptr - wptr;
	else if(bempty) return BUFFER_SIZE; else return 0;
}
bool getBufferEmpty() {
	return bempty;
}

uint32_t getBufferFilled() {
	return BUFFER_SIZE - getBufferFree();
}

uint32_t bufferWrite(uint8_t *data, uint32_t size) {
uint32_t i;
	for(i=0; i<size; i++) {
		if(getBufferFree() == 0) { return i;}
		buffer[wptr++] = data[i];
		if(bempty) bempty = 0;
		if(wptr == BUFFER_SIZE) wptr = 0;
	}
	return size;
}

uint32_t bufferRead(uint8_t *data, uint32_t size) {
	uint32_t i = 0;
	uint32_t bf = getBufferFilled();
	if(size > bf) size = bf;
	for (i = 0; i < size; i++) {
		if(bf == 0) { return i;}
		data[i] = buffer[rptr++];
		if(rptr == BUFFER_SIZE) rptr = 0;
		if(rptr == wptr) bempty = 1;
	}
	return size;
}

void bufferReset() {
	wptr = 0;
	rptr = 0;
	bempty = 1;
}

