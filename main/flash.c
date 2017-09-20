#include "flash.h"
//#include "spi.h"
#include "esp_spi_flash.h"
#include "esp_partition.h"

uint32_t flashRead( void *to, uint32_t fromaddr, uint32_t size )
{
  fromaddr -= INTERNAL_FLASH_START_ADDRESS;

  return spi_flash_read(fromaddr, (uint32_t *)to, size);
}

uint32_t flashWrite( void *data, uint32_t fromaddr, uint32_t size )
{
  fromaddr -= INTERNAL_FLASH_START_ADDRESS;
//   printf("flasWrite from %x, size: %d  Data: %x\n",fromaddr,size,data);

  return spi_flash_write(fromaddr, (uint32_t *)data, size);
}
