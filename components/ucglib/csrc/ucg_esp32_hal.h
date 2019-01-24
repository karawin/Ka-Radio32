/*
 * ucg_esp32_hal.h
 *
 *  Created on: Nov 12, 2017
 *      Author: karawin
 */

#ifndef UCG_ESP32_HAL_H_
#define UCG_ESP32_HAL_H_

//my adaptation. Comment for a generic product
#define KaRadio32 

#define UCG_ESP32_HAL_UNDEFINED (-1)
#define ONEBYTEMAX 4
#define ONEBYTEMAXM1 3
typedef struct {
#ifdef KaRadio32	
	uint8_t spi_no;
#endif	
	gpio_num_t clk;
	gpio_num_t mosi;
	gpio_num_t sda; // data for I²C
	gpio_num_t scl; // clock for I²C
	gpio_num_t cs;
	gpio_num_t reset;
	gpio_num_t dc;
//	gpio_num_t t_cs;  // touch cs
//	gpio_num_t t_irq; //touch irq
} ucg_esp32_hal_t ;

//cumul one byte entries
typedef struct {
	uint16_t nb;
	uint8_t data[ONEBYTEMAX];
} ucg_esp32_oneByte;


#ifdef KaRadio32	
#define UCG_ESP32_HAL_DEFAULT {UCG_ESP32_HAL_UNDEFINED,UCG_ESP32_HAL_UNDEFINED, UCG_ESP32_HAL_UNDEFINED, UCG_ESP32_HAL_UNDEFINED, UCG_ESP32_HAL_UNDEFINED, UCG_ESP32_HAL_UNDEFINED, UCG_ESP32_HAL_UNDEFINED, UCG_ESP32_HAL_UNDEFINED }
#else
#define UCG_ESP32_HAL_DEFAULT {UCG_ESP32_HAL_UNDEFINED, UCG_ESP32_HAL_UNDEFINED, UCG_ESP32_HAL_UNDEFINED, UCG_ESP32_HAL_UNDEFINED, UCG_ESP32_HAL_UNDEFINED, UCG_ESP32_HAL_UNDEFINED, UCG_ESP32_HAL_UNDEFINED }
#endif	



void ucg_esp32_hal_init(ucg_esp32_hal_t ucg_esp32_hal_param);

int16_t ucg_com_hal(ucg_t *ucg, int16_t msg, uint16_t arg, uint8_t *data);

#endif /* UG_ESP32_HAL_H_ */