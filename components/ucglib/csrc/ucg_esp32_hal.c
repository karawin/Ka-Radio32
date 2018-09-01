#include <stdio.h>
#include <string.h>
#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include "sdkconfig.h"
#include "esp_log.h"
#include "rom/ets_sys.h"
#include "esp_heap_caps.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "ucg.h"

#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "driver/i2c.h"
#include "ucg_esp32_hal.h"

#ifdef KaRadio32
#include "gpio.h"
#include "vs1053.h"
#endif

#define TAG  "ucg_hal"

static spi_device_handle_t handle; // SPI handle.
DRAM_ATTR static ucg_esp32_hal_t ucg_esp32_hal; // HAL state data.
static ucg_esp32_oneByte oneByte;

/* to init call
//init hal
ucg_esp32_hal_t ucg_esp32_hal = UCG_ESP32_HAL_DEFAULT;
			ucg_esp32_hal.clk   = PIN_NUM_CLK;
			ucg_esp32_hal.mosi  = PIN_NUM_MOSI;
			ucg_esp32_hal.cs    = PIN_LCD_CS;
			ucg_esp32_hal.dc    = PIN_LCD_A0;
			ucg_esp32_hal.reset = PIN_LCD_RST;	
ucg_esp32_hal_init(ucg_esp32_hal);	
		
//init the lcd
ucg_int_t ucg_Init(ucg_t *ucg, ucg_dev_fnptr device_cb, ucg_dev_fnptr ext_cb, ucg_com_fnptr com_cb);
example
//setup ucglib, see ucg.h for a list of ucg_dev and ucg_ext objects 
ucg_Init(&ucg, ucg_dev_ssd1351_18x128x128_ilsoft, ucg_ext_ssd1351_18, ucg_com_hal);

//define prefered font rendering method (no text will be visibile, if this is missing 
ucg_SetFontMode(&ucg, UCG_FONT_MODE_TRANSPARENT); 

*/

/*
 * Initialze the ESP32 HAL.
 */
void ucg_esp32_hal_init(ucg_esp32_hal_t ucg_esp32_hal_param) {
	ucg_esp32_hal = ucg_esp32_hal_param;
	oneByte.nb = 0;
	
} // ucg_esp32_hal_init

void sendOneByte()
{
	int nb = oneByte.nb;
	oneByte.nb = 0;	
	
	
	if (nb != 0)
	{
		spi_transaction_t trans_desc;
		trans_desc.addr      = 0;
		trans_desc.cmd   = 0;
		trans_desc.rx_buffer = NULL;
		trans_desc.rxlength  = 0;
		trans_desc.flags     =  SPI_TRANS_USE_TXDATA;
		trans_desc.length    = 8*nb;  // Number of bits NOT number of bytes.
		trans_desc.tx_data[0] = oneByte.data[0];// data;
		trans_desc.tx_data[1] = oneByte.data[1];// data;
		trans_desc.tx_data[2] = oneByte.data[2];// data;
		trans_desc.tx_data[3] = oneByte.data[3];//			
		ESP_ERROR_CHECK(spi_device_transmit(handle, &trans_desc));	
//		printf("O");
	}
}

//IRAM_ATTR 
void addOneByte(uint8_t bt)
{
	oneByte.data[oneByte.nb++] = bt;
	if (oneByte.nb >3) sendOneByte(); //security, but ucglib send a max of 4 bytes alone.
}


int16_t ucg_com_hal(ucg_t *ucg, int16_t msg, uint16_t arg, uint8_t *data)
{
//  taskYIELD();

  switch(msg)
  {
    case UCG_COM_MSG_POWER_UP: {
      /* "data" is a pointer to ucg_com_info_t structure with the following information: */
      /*	((ucg_com_info_t *)data)->serial_clk_speed value in nanoseconds */
      /*	((ucg_com_info_t *)data)->parallel_clk_speed value in nanoseconds */
      /* "arg" is not used */

      /* This message is sent once at the uC startup and for power up. */
      /* setup i/o or do any other setup */
	  ESP_LOGI(TAG, "UCG_COM_MSG_POWER_UP: %d ns so in Hz: %d", ((ucg_com_info_t *)data)->serial_clk_speed,1000000000/((ucg_com_info_t *)data)->serial_clk_speed);
	  	if (ucg_esp32_hal.clk == UCG_ESP32_HAL_UNDEFINED ||
				ucg_esp32_hal.mosi == UCG_ESP32_HAL_UNDEFINED ||
				ucg_esp32_hal.cs == UCG_ESP32_HAL_UNDEFINED) {
			break;
		}
		uint64_t bitmask = 0;
		if (ucg_esp32_hal.dc != UCG_ESP32_HAL_UNDEFINED) {
			bitmask = bitmask | (1<<ucg_esp32_hal.dc);
		}
		if (ucg_esp32_hal.reset != UCG_ESP32_HAL_UNDEFINED) {
			bitmask = bitmask | (1<<ucg_esp32_hal.reset);
		}

#ifndef KaRadio32
// init the spi master if not done elsewhere
 		  spi_bus_config_t bus_config;
		  bus_config.sclk_io_num   = ucg_esp32_hal.clk; // CLK
		  bus_config.mosi_io_num   = ucg_esp32_hal.mosi; // MOSI
		  bus_config.miso_io_num   = -1; // MISO
		  bus_config.quadwp_io_num = -1; // Not used
		  bus_config.quadhd_io_num = -1; // Not used
//done for vs1053
		  ESP_ERROR_CHECK(spi_bus_initialize(KSPI, &bus_config, 1));
#endif		
		
		gpio_config_t gpioConfig;
		gpioConfig.pin_bit_mask = bitmask;
		gpioConfig.mode         = GPIO_MODE_OUTPUT;
		gpioConfig.pull_up_en   = GPIO_PULLUP_DISABLE;
		gpioConfig.pull_down_en = GPIO_PULLDOWN_DISABLE;
		gpioConfig.intr_type    = GPIO_INTR_DISABLE;
		ESP_ERROR_CHECK(gpio_config(&gpioConfig));
		
		gpio_set_level(ucg_esp32_hal.reset, 0);
		gpio_set_level(ucg_esp32_hal.cs, 0);		
		gpio_set_level(ucg_esp32_hal.dc, 0);		
		
		spi_device_interface_config_t dev_config;
		dev_config.address_bits     = 0;
		dev_config.command_bits     = 0;
		dev_config.dummy_bits       = 0;
		dev_config.mode             = 0;
		dev_config.duty_cycle_pos   = 0;
		dev_config.cs_ena_posttrans = 1;
		dev_config.cs_ena_pretrans  = 0;
//		dev_config.clock_speed_hz   = (1000000000/((ucg_com_info_t *)data)->serial_clk_speed) ;
		dev_config.clock_speed_hz   = (2000000000/((ucg_com_info_t *)data)->serial_clk_speed) ; // test at double speed
		dev_config.spics_io_num     = ucg_esp32_hal.cs;
		dev_config.flags            = SPI_DEVICE_NO_DUMMY;
		dev_config.queue_size       = 1;
		dev_config.pre_cb           = NULL;
		dev_config.post_cb          = NULL;
		ESP_LOGI(TAG, "... Adding device bus  Speed= %d.",dev_config.clock_speed_hz);
		ESP_ERROR_CHECK(spi_bus_add_device(KSPI, &dev_config, &handle)); 
	}
		break;

    case UCG_COM_MSG_POWER_DOWN:
      /* "data" and "arg" are not used*/
      /* This message is sent for a power down request */

      break;
    case UCG_COM_MSG_DELAY:
      /* "data" is not used */
      /* "arg" contains the number of microseconds for the delay */
      /* By receiving this message, the following code should delay by */
      /* "arg" microseconds. One microsecond is 0.000001 second */
		ets_delay_us (arg);
      break;
    case UCG_COM_MSG_CHANGE_RESET_LINE:
		//ESP_LOGD(TAG,"ucg_com_hal  msg: %d, arg: %x, data: %x",msg,arg,(data!=NULL)?*data:0);
      /* "data" is not used */
      /* "arg" = 1: set the reset output line to 1 */
      /* "arg" = 0: set the reset output line to 0 */
		gpio_set_level(ucg_esp32_hal.reset, arg);
      break;
    case UCG_COM_MSG_CHANGE_CD_LINE:
//	printf("C");
	sendOneByte();
//		ESP_LOGD(TAG,"ucg_com_hal  msg: %d, arg: %x, data: %x",msg,arg,(data!=NULL)?*data:0);
      /* "ucg->com_status"  bit 0 contains the old level for the CD line */
      /* "data" is not used */
      /* "arg" = 1: set the command/data (a0) output line to 1 */
      /* "arg" = 0: set the command/data (a0) output line to 0 */
		gpio_set_level(ucg_esp32_hal.dc, arg);
      break;
    case UCG_COM_MSG_CHANGE_CS_LINE:
		//ESP_LOGD(TAG,"ucg_com_hal  msg: %d, arg: %x, data: %x",msg,arg,(data!=NULL)?*data:0);
      /* "ucg->com_status"  bit 1 contains the old level for the CS line */
      /* "data" is not used */
      /* "arg" = 1: set the chipselect output line to 1 */
      /* "arg" = 0: set the chipselect output line to 0 */
		//gpio_set_level(ucg_esp32_hal.cs, arg); //done by the spi driver
      break;
    case UCG_COM_MSG_SEND_BYTE: {
//		printf("B");
		addOneByte(arg);
      /* "data" is not used */
      /* "arg" contains one byte, which should be sent to the display */
      /* The current status of the CD line is available */
      /* in bit 0 of u8g->com_status */
/*			spi_transaction_t trans_desc;
			trans_desc.addr      = 0;
			trans_desc.cmd   = 0;
			trans_desc.flags     = SPI_TRANS_USE_TXDATA;
			trans_desc.length    = 8 ; // Number of bits NOT number of bytes.
			trans_desc.rxlength  = 0;
			trans_desc.tx_data[0] = (char) arg;
			trans_desc.rx_buffer = NULL;
			 
			ESP_ERROR_CHECK(spi_device_transmit(handle, &trans_desc));
//			ESP_ERROR_CHECK(spi_device_queue_trans(handle, &trans_desc,portMAX_DELAY));
*/			 
	  }
      break;
    case UCG_COM_MSG_REPEAT_1_BYTE: 
	if (arg ==0) break;
	else
	{
//		printf("1");
		sendOneByte();
      /* "data[0]" contains one byte */
      /* repeat sending the byte in data[0] "arg" times */
      /* The current status of the CD line is available */
      /* in bit 0 of u8g->com_status */
		uint16_t i = arg;	  
		spi_transaction_t trans_desc;
		trans_desc.addr      = 0;
		trans_desc.cmd   = 0;
		trans_desc.rx_buffer = NULL;
		trans_desc.rxlength  = 0;
	  
	  if (arg >4)
	  {
		uint8_t* txbf;
		uint8_t* txb = heap_caps_malloc(arg*2, MALLOC_CAP_DMA);
		txbf = txb;
		while (i--) { *txbf++ = (char) data[0];} 
		trans_desc.flags     = 0;
		trans_desc.length    = 8*arg ; // Number of bits NOT number of bytes.
		trans_desc.tx_buffer = txb;
		ESP_ERROR_CHECK(spi_device_transmit(handle, &trans_desc));				
		heap_caps_free(txb);	
	  } else
	  {	
		trans_desc.flags     =  SPI_TRANS_USE_TXDATA;
		trans_desc.length    = 8*arg;  // Number of bits NOT number of bytes.
		trans_desc.tx_data[0] = data[0];// data;
		trans_desc.tx_data[1] = data[0];// data;
		trans_desc.tx_data[2] = data[0];// data;
		trans_desc.tx_data[3] = data[0];// data;			
		ESP_ERROR_CHECK(spi_device_transmit(handle, &trans_desc));
	  } 
	}
      break;
    case UCG_COM_MSG_REPEAT_2_BYTES: 
	if (arg ==0) break;
	else
	{
//		printf("2");
		sendOneByte();
      /* "data[0]" contains first byte */
      /* "data[1]" contains second byte */
      /* repeat sending the two bytes "arg" times */
      /* The current status of the CD line is available */
      /* in bit 0 of u8g->com_status */
	  uint16_t i = arg;
	  
	  spi_transaction_t trans_desc;
		trans_desc.addr      = 0;
		trans_desc.cmd   = 0;
		trans_desc.rx_buffer = NULL;
		trans_desc.rxlength  = 0;
	  
	  if (arg >2)
	  {
		uint8_t* txbf;
		uint8_t* txb = heap_caps_malloc(arg*2, MALLOC_CAP_DMA);
		txbf = txb;
		while (i--) { *txbf++ = (char) data[0]; *txbf++ = (char) data[1]; } 
		trans_desc.flags     = 0;
		trans_desc.length    = 16*arg ; // Number of bits NOT number of bytes.
		trans_desc.tx_buffer = txb;
		ESP_ERROR_CHECK(spi_device_transmit(handle, &trans_desc));				
		heap_caps_free(txb);	
	  } else
	  {	
		trans_desc.flags     =  SPI_TRANS_USE_TXDATA;
		trans_desc.length    = 16*arg;  // Number of bits NOT number of bytes.
		trans_desc.tx_data[0] = data[0];// data;
		trans_desc.tx_data[1] = data[1];// data;
		trans_desc.tx_data[2] = data[0];// data;
		trans_desc.tx_data[3] = data[1];// data;			
		ESP_ERROR_CHECK(spi_device_transmit(handle, &trans_desc));
	  } 
	}
    break;
    case UCG_COM_MSG_REPEAT_3_BYTES: 
	if (arg ==0) break;
	else
	{
//		printf("3");
		sendOneByte();
      /* "data[0]" contains first byte */
      /* "data[1]" contains second byte */
      /* "data[2]" contains third byte */
      /* repeat sending the three bytes "arg" times */
      /* The current status of the CD line is available */
      /* in bit 0 of u8g->com_status */
	  uint16_t i = arg;	  
	  spi_transaction_t trans_desc;
		trans_desc.addr      = 0;
		trans_desc.cmd   = 0;
		trans_desc.rxlength  = 0;
		trans_desc.rx_buffer = NULL;
		
	  if (arg >1)
	  {
		uint8_t* txbf;
		uint8_t* txb = heap_caps_malloc(arg*4, MALLOC_CAP_DMA);
		txbf = txb;
		while (i--) { *txbf++ = (char) data[0]; *txbf++ = (char) data[1]; *txbf++ = (char) data[2];} 
		*txbf = 0;
		trans_desc.flags     = 0;
		trans_desc.length    = 24*arg ; // Number of bits NOT number of bytes.
		trans_desc.tx_buffer = txb;
		ESP_ERROR_CHECK(spi_device_transmit(handle, &trans_desc));				
		heap_caps_free(txb);	
	  } else
	  {	
		trans_desc.flags     =  SPI_TRANS_USE_TXDATA;
		trans_desc.length    = 24;  // Number of bits NOT number of bytes.
		trans_desc.tx_data[0] = data[0];// data;
		trans_desc.tx_data[1] = data[1];// data;
		trans_desc.tx_data[2] = data[2];// data;
		trans_desc.tx_data[3] = 0;//			
		ESP_ERROR_CHECK(spi_device_transmit(handle, &trans_desc));
	  } 
	}
    break;
    case UCG_COM_MSG_SEND_STR: {
//		printf("S");
		sendOneByte();
      /* "data" is an array with "arg" bytes */
      /* send "arg" bytes to the display */
	  uint8_t* txb = heap_caps_malloc(arg, MALLOC_CAP_DMA);
	  memcpy(txb,data,arg);
	  spi_transaction_t trans_desc;
		trans_desc.addr      = 0;
		trans_desc.cmd   = 0;
		trans_desc.flags     = 0;
		trans_desc.length    = 8*arg ; // Number of bits NOT number of bytes.
		trans_desc.rxlength  = 0;
		trans_desc.tx_buffer = txb;
		trans_desc.rx_buffer = NULL;
		ESP_ERROR_CHECK(spi_device_transmit(handle, &trans_desc));
		heap_caps_free(txb);	 
	}
    break;
    case UCG_COM_MSG_SEND_CD_DATA_SEQUENCE:
      /* "data" is a pointer to two bytes, which contain the cd line */
      /* status and display data */
      /* "arg" contains the number of these two byte tuples which need to */
      /* be analysed and sent. Bellow is a example sequence */
      /* The content of bit 0 in u8g->com_status is undefined for this message */
//	  printf("D");
	  sendOneByte();
      while(arg > 0)
      {
		if ( *data != 0 )
		{
			if ( *data == 1 )
			{// set CD (=D/C=A0) line to low 			
				gpio_set_level(ucg_esp32_hal.dc, 0);}
			else
			{// set CD (=D/C=A0) line to high 
				gpio_set_level(ucg_esp32_hal.dc, 1);
			}
		}
		data++;
        /* send *data to the display */
		spi_transaction_t trans_desc;
		trans_desc.addr      = 0;
		trans_desc.cmd   = 0;
		trans_desc.flags     = SPI_TRANS_USE_TXDATA;
		trans_desc.length    = 8 ; // Number of bits NOT number of bytes.
		trans_desc.rxlength  = 0;
		trans_desc.tx_buffer = NULL;
		trans_desc.tx_data[0] = (char)*data;// data;
		trans_desc.rx_buffer = NULL;		 
		ESP_ERROR_CHECK(spi_device_transmit(handle, &trans_desc));
		data++;
		arg--;
      }
      break;
	default:
	printf("ucg_esp default to %d\n",msg);
  }
  return 1;
}
