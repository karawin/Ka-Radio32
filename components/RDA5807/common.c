/* BSD 3-Clause License
 * 
 * RDA5807M driver for ESP8266
 * Copyright (c) 2017, ccbruce0812 (ccbruce@gmail.com)
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * 
 * * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

//#include "common.h"
#include "rda5807m.h"

#if defined(__xtensa__)
#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#include "esp_log.h"
#include "freertos/semphr.h"
#define TAG "RDA5807"
xSemaphoreHandle semI2C = NULL;

bool i2c_init(int scl, int sda)
{
		    i2c_config_t conf;
		    conf.mode = I2C_MODE_MASTER;
		    conf.sda_io_num = sda;
		    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
		    conf.scl_io_num = scl;
		    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
		    conf.master.clk_speed = I2C_MASTER_RFREQ_HZ;
		    //ESP_ERROR_CHECK
			(i2c_param_config(I2C_MASTER_NUM, &conf));
			ESP_LOGD(TAG, "i2c_driver_install %d", I2C_MASTER_NUM);
		    //ESP_ERROR_CHECK
			(i2c_driver_install(I2C_MASTER_NUM, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0));					
	return true;
}

bool i2c_slave_read_only(uint8_t slave_addr,  uint8_t *buf, uint32_t len)
{
	if (semI2C == NULL) vSemaphoreCreateBinary(semI2C);
//	xSemaphoreTake(semI2C, portMAX_DELAY);
			i2c_cmd_handle_t cmd = i2c_cmd_link_create();
			ESP_ERROR_CHECK(i2c_master_start(cmd));
			ESP_ERROR_CHECK(i2c_master_write_byte(cmd, (slave_addr<<1) | I2C_MASTER_READ, ACK_CHECK_EN));
			ESP_ERROR_CHECK(i2c_master_read(cmd, buf,len-1, ACK_VAL));
			ESP_ERROR_CHECK(i2c_master_read_byte(cmd, buf+len-1, NACK_VAL));
			ESP_ERROR_CHECK(i2c_master_stop(cmd));
			i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS);
			i2c_cmd_link_delete(cmd);	
//	xSemaphoreGive(semI2C);		
	return true;			
}

bool i2c_slave_read(uint8_t slave_addr, uint8_t data, uint8_t *buf, uint32_t len)
{
	if (semI2C == NULL) vSemaphoreCreateBinary(semI2C);
	xSemaphoreTake(semI2C, portMAX_DELAY);
//			i2c_init(GPIO_NUM_14, GPIO_NUM_13);

			i2c_cmd_handle_t cmd = i2c_cmd_link_create();
			ESP_ERROR_CHECK(i2c_master_start(cmd));
			ESP_ERROR_CHECK(i2c_master_write_byte(cmd, (slave_addr<<1) | I2C_MASTER_WRITE, ACK_CHECK_EN));
			ESP_ERROR_CHECK(i2c_master_write_byte(cmd, data, ACK_CHECK_EN)); // reg addr
			ESP_ERROR_CHECK(i2c_master_stop(cmd));
			i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS);
			i2c_cmd_link_delete(cmd);	
			
			i2c_slave_read_only(slave_addr,  buf, len);	
	xSemaphoreGive(semI2C);		
	return true;
}

bool i2c_slave_write(uint8_t slave_addr, uint8_t *buf, uint8_t len)
{
	if (semI2C == NULL) vSemaphoreCreateBinary(semI2C);
	xSemaphoreTake(semI2C, portMAX_DELAY);
			i2c_cmd_handle_t cmd = i2c_cmd_link_create();
			ESP_ERROR_CHECK(i2c_master_start(cmd));	
			ESP_ERROR_CHECK(i2c_master_write_byte(cmd, (slave_addr<<1) | I2C_MASTER_WRITE, ACK_CHECK_EN));
			ESP_ERROR_CHECK(i2c_master_write(cmd, buf, len, ACK_CHECK_EN));
			ESP_ERROR_CHECK(i2c_master_stop(cmd));
			i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, 1000 / portTICK_RATE_MS);
			i2c_cmd_link_delete(cmd);			
	xSemaphoreGive(semI2C);		
	return true;
}

#endif

int RDA5807M_readReg(unsigned char regAddr, unsigned short *pData) {
	if(!pData) {
		DBG("Bad argument. Check your code.\n");
		assert(false);
	}
	
	if(!i2c_slave_read(RDA5807M_ADDR, regAddr, (unsigned char *)pData, sizeof(unsigned short)))
		goto failed;

	unsigned char *pArr=(unsigned char *)pData;
	
	SWAP(pArr[0], pArr[1]);
	
	return 0;

failed:
	return -1;
}
int RDA5807M_readRegOnly( unsigned short *pData,int len) {
	int i;
	if(!pData) {
		DBG("Bad argument. Check your code.\n");
		assert(false);
	}
	
	if(!i2c_slave_read_only(RDA5807M_ADDR, (unsigned char *)pData, len*sizeof(unsigned short)))
		goto failed;

	unsigned char *pArr=(unsigned char *)pData;
//	printf ("beforeswap: %x\n",*pData);
	for ( i = 0; i < len; i++)
	{	
		char a,b;
		a = pArr[i*2]; b= pArr[(i*2)+1];
		pArr[i*2] = b ; pArr[(i*2)+1] = a;		
	}
	//SWAP(pArr[0], pArr[1]);
//	printf ("after swap: %x\n",*pData);
	return 0;

failed:
	return -1;
}

int RDA5807M_writeReg(unsigned char regAddr, unsigned short data) {
	unsigned char buf[3]={regAddr, (unsigned char)(data>>8), (unsigned char)data};

	if(!i2c_slave_write(RDA5807M_ADDR, buf, sizeof(buf)))
		goto failed;

	return 0;

failed:
	return -1;
}

/*
int readRegs(unsigned short *pData, unsigned int count) {
	int i;
	
	if(count<1)
		goto failed;
	
	count=Wire.requestFrom((int)RDA5807M_SEQADDR, count*2);
	for(i=0;i<count/2;i++) {
		pData[i]=Wire.read();
		pData[i]<<=8;
		pData[i]|=Wire.read();
	}
	
	return 0;

failed:
	DBG("Failed.\n");
	return -1;
}

int writeRegs(unsigned short *pData, unsigned int count) {
	int i;
	
	if(count<1)
		goto failed;
	
	Wire.beginTransmission(RDA5807M_SEQADDR);
	for(i=0;i<count;i++) {
		Wire.write(pData[i]>>8);
		Wire.write(pData[i]&0xff);
	}
	Wire.endTransmission();
	
	return 0;
	
failed:
	return -1;
}
*/