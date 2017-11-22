
//#include <SPI.h>
#include "ucg.h"

ucg_t ucg;

uint8_t ucg_cs_pin = 10;	/* more flexible: Ucglib uses independet chip select */
uint8_t ucg_cd_pin = 9;	/* command / data line */
uint8_t ucg_reset_pin = 8;


void u8g_arduino_sw_spi_shift_out(uint8_t val)
{
  uint8_t dataPin  = 11;
  uint8_t clockPin = 13;
  uint8_t i = 8;
  do
  {
    if ( val & 128 )
      digitalWrite(dataPin, HIGH);
    else
      digitalWrite(dataPin, LOW);
    val <<= 1;
    delayMicroseconds(1);		/* 23 Sep 2012 */
    //delay(1);
    digitalWrite(clockPin, HIGH);
    delayMicroseconds(1);		/* 23 Sep 2012 */
    //delay(1);
    digitalWrite(clockPin, LOW);		
    delayMicroseconds(1);		/* 23 Sep 2012 */
    //delay(1);
    i--;
  } while( i != 0 );
}

int16_t ucg_com_arduino_spi(ucg_t *ucg, int16_t msg, uint32_t arg, uint8_t *data)
{
  switch(msg)
  {
    case UCG_COM_MSG_POWER_UP:
      /* "data" is a pointer to ucg_com_info_t structure with the following information: */
      /*	((ucg_com_info_t *)data)->serial_clk_speed value in nanoseconds */
      /*	((ucg_com_info_t *)data)->parallel_clk_speed value in nanoseconds */
      
      /* setup pins */
      pinMode(13, OUTPUT);
      pinMode(11, OUTPUT);
      pinMode(ucg_reset_pin, OUTPUT);
      pinMode(ucg_cd_pin, OUTPUT);
      pinMode(ucg_cs_pin, OUTPUT);
      
      /* setup Arduino SPI */
      //SPI.begin();
      //SPI.setClockDivider( SPI_CLOCK_DIV128 );
      //SPI.setDataMode( SPI_MODE0 );
      //SPI.setBitOrder(MSBFIRST);
      break;
    case UCG_COM_MSG_POWER_DOWN:
      //SPI.end(); 
      break;
    case UCG_COM_MSG_DELAY:
      delayMicroseconds(arg);
      break;
    case UCG_COM_MSG_CHANGE_RESET_LINE:
      digitalWrite(ucg_reset_pin, arg);
      break;
    case UCG_COM_MSG_CHANGE_CS_LINE:
      digitalWrite(ucg_cs_pin, arg);
      break;
    case UCG_COM_MSG_CHANGE_CD_LINE:
      digitalWrite(ucg_cd_pin, arg);
      break;
    case UCG_COM_MSG_SEND_BYTE:
      //SPI.transfer(arg); 
      u8g_arduino_sw_spi_shift_out(arg);
      break;
    case UCG_COM_MSG_REPEAT_1_BYTE:
      while( arg > 0 ) {
	u8g_arduino_sw_spi_shift_out(data[0]);
	arg--;
      }
      break;
    case UCG_COM_MSG_REPEAT_2_BYTES:
      while( arg > 0 ) {
	u8g_arduino_sw_spi_shift_out(data[0]);
	u8g_arduino_sw_spi_shift_out(data[1]);
	arg--;
      }
      break;
    case UCG_COM_MSG_REPEAT_3_BYTES:
      while( arg > 0 ) {
	u8g_arduino_sw_spi_shift_out(data[0]);
	u8g_arduino_sw_spi_shift_out(data[1]);
	u8g_arduino_sw_spi_shift_out(data[2]);
	arg--;
      }
      break;
    case UCG_COM_MSG_SEND_STR:
      while( arg > 0 ) {
	u8g_arduino_sw_spi_shift_out(*data++);
	arg--;
      }
      break;
  }
  return 1;
}


void setup(void)
{
  ucg_Init(&ucg, u8g_dev_ssd1351_128x128_oled_ilsoft, ucg_com_arduino_spi);
}

void loop(void)
{
  ucg_SetColor(&ucg, 0, 255, 0, 0);
  ucg_DrawHLine(&ucg, 0, 0, 20);
  ucg_DrawHLine(&ucg, 0, 1, 20);
  ucg_DrawHLine(&ucg, 0, 2, 20);
  ucg_DrawHLine(&ucg, 0, 3, 20);
  ucg_SetColor(&ucg, 0, 0, 255, 0);
  ucg_DrawHLine(&ucg, 0, 4, 20);
  ucg_DrawHLine(&ucg, 0, 5, 20);
  ucg_DrawHLine(&ucg, 0, 6, 20);
  ucg_DrawHLine(&ucg, 0, 7, 20);
  
  ucg_SetColor(&ucg, 0, 255, 0, 0);
  ucg_SetColor(&ucg, 1, 0, 255, 0);
  ucg_SetColor(&ucg, 2, 255, 0, 255);
  ucg_SetColor(&ucg, 3, 0, 255, 255);

  ucg_DrawGradientBox(&ucg, 10, 43, 100, 20);
}
