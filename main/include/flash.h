#pragma once

#include "esp_system.h"
#
#define INTERNAL_FLASH_START_ADDRESS    0x400D0000

uint32_t flashRead( void *to, uint32_t fromaddr, uint32_t size );
uint32_t flashWrite( void *data, uint32_t fromaddr, uint32_t size );
