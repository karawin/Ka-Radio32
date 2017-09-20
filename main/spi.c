/*
* The MIT License (MIT)
* 
* Copyright (c) 2015 David Ogilvy (MetalPhreak)
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esp_system.h"
#include "driver/spi_master.h"
#include "soc/gpio_struct.h"
#include "driver/gpio.h"


#include "spi.h"

xSemaphoreHandle sSPI = NULL;

uint8_t spi_take_semaphore() {
	if(sSPI) if(xSemaphoreTake(sSPI, portMAX_DELAY)) return 1;
	return 0;
}

void spi_give_semaphore() {
	if(sSPI) xSemaphoreGive(sSPI);
}

////////////////////////////////////////////////////////////////////////////////
//
// Function Name: spi_init
//   Description: Wrapper to setup HSPI/SPI GPIO pins and default SPI clock
//    Parameters: spi_no - SPI (0) or HSPI (1)
//				 
////////////////////////////////////////////////////////////////////////////////

void spi_init(uint8_t spi_no){
	esp_err_t ret;
	
	if(!sSPI) vSemaphoreCreateBinary(sSPI);
	spi_give_semaphore();
	

	if(spi_no > 1) return; //Only SPI and HSPI are valid spi modules. 
	
	spi_bus_config_t buscfg={
        .miso_io_num=PIN_NUM_MISO,
        .mosi_io_num=PIN_NUM_MOSI,
        .sclk_io_num=PIN_NUM_CLK,
        .quadwp_io_num=-1,
        .quadhd_io_num=-1
	};		
	ret=spi_bus_initialize(HSPI_HOST, &buscfg, 0);	 // no dma	
	assert(ret==ESP_OK);	
}

////////////////////////////////////////////////////////////////////////////////


uint32_t spi_transaction(spi_device_handle_t spi_no, uint8_t cmd_bits, uint16_t cmd_data, uint32_t addr_bits, uint32_t addr_data, uint32_t dout_bits, uint32_t dout_data,
				uint32_t din_bits, uint32_t dummy_bits){
    esp_err_t ret;
    spi_transaction_t t;
	uint32_t rxdata;
    memset(&t, 0, sizeof(t));       //Zero out the transaction
    t.user=(void*)0;                //D/C needs to be set to 0
	
	if (dout_bits !=0) {//tx data
		t.length=dout_bits;             // in bits
		t.tx_buffer=&dout_data;          //The data 
		ret=spi_device_transmit(spi_no, &t);  //Transmit!
		assert(ret==ESP_OK); //Should have had no issues.
		return 1; //success
	} else  //rx data
	{
		t.length=din_bits;             // in bits
		t.rx_buffer=&rxdata;          //The data 
		ret=spi_device_transmit(spi_no, &t);  //receive
		assert(ret==ESP_OK); //Should have had no issues.
		return rxdata;
	}		

	//Transaction completed
	return 1; //success
}

////////////////////////////////////////////////////////////////////////////////

/*///////////////////////////////////////////////////////////////////////////////
//
// Function Name: func
//   Description: 
//    Parameters: 
//				 
////////////////////////////////////////////////////////////////////////////////

void func(params){

}

///////////////////////////////////////////////////////////////////////////////*/


