/*
 * Copyright 2016 Piotr Sperka (http://www.piotrsperka.info)
*/
#ifndef __EXTRAM_H__
#define __EXTRAM_H__

#include "c_types.h"

void extramInit();
void initBuffer();
uint32_t extramRead(uint32_t size, uint32_t address, uint8_t *buffer);
uint32_t extramWrite(uint32_t size, uint32_t address, uint8_t *data);

#endif
