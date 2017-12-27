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

#include "common.h"
#include "rda5807m.h"

void RDA5807M_dump(void) {
	unsigned short reg=0;
	int i=0;
	
	for(i=0;i<16;i++) {
		readReg(RDA5807M_REG_ADDR_00+i, &reg);
		DBG("%02X: %04X\n", i, reg);
	}
}

bool RDA5807M_detection()
{
	RDA5807M_REG_00 r00;
	if(readReg(RDA5807M_REG_ADDR_00, &r00.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		return false;
	}	
	if (r00.f.CHIPID == 0x58) return true;
	return false;	
}


int RDA5807M_init(const RDA5807M_SETTING *pSetting) {
//	RDA5807M_REG_00 r00;
	RDA5807M_REG_02 r02;
	RDA5807M_REG_03 r03;
	RDA5807M_REG_04 r04;
	RDA5807M_REG_07 r07;
	
	if(!pSetting)
		goto failed;

	r02.f.SOFT_RESET=1;
	r02.f.ENABLE=1;
	if(writeReg(RDA5807M_REG_ADDR_02, r02.b)<0) {
		DBG("[%d] Failed to invoke writeReg().\n", __LINE__);
		goto failed;
	}

	if(readReg(RDA5807M_REG_ADDR_02, &r02.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}
	
	r02.f.RCLK_NON_CAL=pSetting->clkSetting.isClkNoCalb?1:0;
	r02.f.RCLK_DIR_INP=pSetting->clkSetting.isClkDirInp?1:0;
	r02.f.CLK_MODE=pSetting->clkSetting.freq;
	r02.f.RDS_EN=pSetting->useRDS?1:0;
	r02.f.NEW_METHOD=pSetting->useNewDMMethod?1:0;
	r02.f.SOFT_RESET=0;
	r02.f.ENABLE=1;
	r04.f.DE=pSetting->isDECNST50us?1:0;
	r03.f.BAND=pSetting->system.band;
	r03.f.SPACE=pSetting->system.space;
	r07.f.BAND_OPT=pSetting->system.is6576Sys?1:0;

	if(writeReg(RDA5807M_REG_ADDR_02, r02.b)<0) {
		DBG("[%d] Failed to invoke writeReg().\n", __LINE__);
		goto failed;
	}

	if(writeReg(RDA5807M_REG_ADDR_03, r03.b)<0) {
		DBG("[%d] Failed to invoke writeReg().\n", __LINE__);
		goto failed;
	}

	if(writeReg(RDA5807M_REG_ADDR_04, r04.b)<0) {
		DBG("[%d] Failed to invoke writeReg().\n", __LINE__);
		goto failed;
	}

	if(writeReg(RDA5807M_REG_ADDR_07, r07.b)<0) {
		DBG("[%d] Failed to invoke writeReg().\n", __LINE__);
		goto failed;
	}
	
	return RDA5807M_OK;

failed:
	return RDA5807M_ERR_FAILED;
}

int RDA5807M_enableOutput(RDA5807M_BOOL flag) {
	RDA5807M_REG_02 r02;
		
	if(readReg(RDA5807M_REG_ADDR_02, &r02.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}

	r02.f.DHIZ=flag?1:0;

	if(writeReg(RDA5807M_REG_ADDR_02, r02.b)<0) {
		DBG("[%d] Failed to invoke writeReg().\n", __LINE__);
		goto failed;
	}
	
	return RDA5807M_OK;
	
failed:
	return RDA5807M_ERR_FAILED;
}

int RDA5807M_isOutputEnable(RDA5807M_BOOL *pFlag) {
	RDA5807M_REG_02 r02;
		
	if(readReg(RDA5807M_REG_ADDR_02, &r02.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}

	*pFlag=r02.f.DHIZ?RDA5807M_TRUE:RDA5807M_FALSE;
	
	return RDA5807M_OK;
	
failed:
	return RDA5807M_ERR_FAILED;
}

int RDA5807M_unmute(RDA5807M_BOOL flag) {
	RDA5807M_REG_02 r02;
		
	if(readReg(RDA5807M_REG_ADDR_02, &r02.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}

	r02.f.DMUTE=flag?1:0;

	if(writeReg(RDA5807M_REG_ADDR_02, r02.b)<0) {
		DBG("[%d] Failed to invoke writeReg().\n", __LINE__);
		goto failed;
	}
	
	return RDA5807M_OK;
	
failed:
	return RDA5807M_ERR_FAILED;
}

int RDA5807M_isUnmute(RDA5807M_BOOL *pFlag) {
	RDA5807M_REG_02 r02;
		
	if(readReg(RDA5807M_REG_ADDR_02, &r02.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}

	*pFlag=r02.f.DMUTE?RDA5807M_TRUE:RDA5807M_FALSE;
	
	return RDA5807M_OK;
	
failed:
	return RDA5807M_ERR_FAILED;
}

int RDA5807M_setBB(RDA5807M_BOOL flag) {
	RDA5807M_REG_02 r02;
		
	if(readReg(RDA5807M_REG_ADDR_02, &r02.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}

	r02.f.BASS=flag?1:0;

	if(writeReg(RDA5807M_REG_ADDR_02, r02.b)<0) {
		DBG("[%d] Failed to invoke writeReg().\n", __LINE__);
		goto failed;
	}
	
	return RDA5807M_OK;
	
failed:
	return RDA5807M_ERR_FAILED;
}

int RDA5807M_isBB(RDA5807M_BOOL *pFlag) {
	RDA5807M_REG_02 r02;
		
	if(readReg(RDA5807M_REG_ADDR_02, &r02.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}

	*pFlag=r02.f.BASS?RDA5807M_TRUE:RDA5807M_FALSE;
	
	return RDA5807M_OK;
	
failed:
	return RDA5807M_ERR_FAILED;
}

int RDA5807M_setFreq(unsigned long freq) {
	RDA5807M_REG_03 r03;
	RDA5807M_REG_07 r07;
	RDA5807M_REG_0A r0A;
	
	unsigned long base[4]={87000, 76000, 76000, 65000},
				space[4]={100, 200, 50, 25},
				channel=0;
				
	unsigned int now=0, prev=0;
				
	if(readReg(RDA5807M_REG_ADDR_03, &r03.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}

	if(readReg(RDA5807M_REG_ADDR_07, &r07.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}
	
	if(r07.f.BAND_OPT)
		base[3]=50000;
	
	channel=(freq-base[r03.f.BAND])/space[r03.f.SPACE];
	r03.f.CHAN=(unsigned short)channel;
	r03.f.TUNE=1;
	
	if(writeReg(RDA5807M_REG_ADDR_03, r03.b)<0) {
		DBG("[%d] Failed to invoke writeReg().\n", __LINE__);
		goto failed;
	}
	
	now=prev=xTaskGetTickCount();
	while(1) {
		vTaskDelay(MSEC2TICKS(20));
		
		if(readReg(RDA5807M_REG_ADDR_0A, &r0A.b)<0) {
			DBG("[%d] Failed to invoke readReg().\n", __LINE__);
			goto failed;
		}
		
		if(r0A.f.STC)
			break;
		
		now=xTaskGetTickCount();
		if(now-prev>=MSEC2TICKS(3000)) {
			DBG("[%d] Failed to set frequency.\n", __LINE__);
			goto failed;
		}
	}

	return RDA5807M_OK;
	
failed:
	return RDA5807M_ERR_FAILED;
}

int RDA5807M_getFreq(unsigned long *pFreq) {
	RDA5807M_REG_03 r03;
	RDA5807M_REG_07 r07;
	RDA5807M_REG_0A r0A;
	
	unsigned long base[4]={87000, 76000, 76000, 65000},
				space[4]={100, 200, 50, 25};
				
	if(readReg(RDA5807M_REG_ADDR_03, &r03.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}

	if(readReg(RDA5807M_REG_ADDR_07, &r07.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}
	
	if(readReg(RDA5807M_REG_ADDR_0A, &r0A.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}
	
	if(r07.f.BAND_OPT)
		base[3]=50000;
	
	*pFreq=r0A.f.READCHAN;
	*pFreq=*pFreq*space[r03.f.SPACE]+base[r03.f.BAND];

	return RDA5807M_OK;

failed:
	return RDA5807M_ERR_FAILED;
}

int RDA5807M_seek(RDA5807M_BOOL isUp, RDA5807M_BOOL dontWrap) {
	RDA5807M_REG_02 r02;
	
	if(readReg(RDA5807M_REG_ADDR_02, &r02.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}
	
	r02.f.SEEKUP=isUp?1:0;
	r02.f.SKMODE=dontWrap?1:0;
	r02.f.SEEK=1;
	
	if(writeReg(RDA5807M_REG_ADDR_02, r02.b)<0) {
		DBG("[%d] Failed to invoke writeReg().\n", __LINE__);
		goto failed;
	}
	
	return RDA5807M_OK;

failed:
	return RDA5807M_ERR_FAILED;
}

int RDA5807M_isSeekingComplete(RDA5807M_BOOL *pFlag) {
	RDA5807M_REG_0A r0A;
	
	if(readReg(RDA5807M_REG_ADDR_0A, &r0A.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}
	
	*pFlag=r0A.f.STC?RDA5807M_TRUE:RDA5807M_FALSE;

	return RDA5807M_OK;

failed:
	return RDA5807M_ERR_FAILED;
}

int RDA5807M_isSeekingFailed(RDA5807M_BOOL *pFlag) {
	RDA5807M_REG_0A r0A;
	
	if(readReg(RDA5807M_REG_ADDR_0A, &r0A.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}
	
	*pFlag=r0A.f.SF?RDA5807M_TRUE:RDA5807M_FALSE;

	return RDA5807M_OK;

failed:
	return RDA5807M_ERR_FAILED;
}

int RDA5807M_stopSeeking(void) {
	RDA5807M_REG_02 r02;
	
	if(readReg(RDA5807M_REG_ADDR_02, &r02.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}
	
	r02.f.SEEK=0;

	if(writeReg(RDA5807M_REG_ADDR_02, r02.b)<0) {
		DBG("[%d] Failed to invoke writeReg().\n", __LINE__);
		goto failed;
	}
	
	return RDA5807M_OK;

failed:
	return RDA5807M_ERR_FAILED;
}

int RDA5807M_setAFCDisable(RDA5807M_BOOL flag) {
	RDA5807M_REG_04 r04;
	
	if(readReg(RDA5807M_REG_ADDR_04, &r04.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}
	
	r04.f.AFCD=flag?1:0;
	
	if(writeReg(RDA5807M_REG_ADDR_04, r04.b)<0) {
		DBG("[%d] Failed to invoke writeReg().\n", __LINE__);
		goto failed;
	}
	
	return RDA5807M_OK;

failed:
	return RDA5807M_ERR_FAILED;
}

int RDA5807M_getAFCDisable(RDA5807M_BOOL *pFlag) {
	RDA5807M_REG_04 r04;
	
	if(readReg(RDA5807M_REG_ADDR_04, &r04.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}
	
	*pFlag=r04.f.AFCD?RDA5807M_TRUE:RDA5807M_FALSE;
	
	return RDA5807M_OK;

failed:
	return RDA5807M_ERR_FAILED;
}

int RDA5807M_setSeekSNRThrshold(unsigned char threshold) {
	RDA5807M_REG_05 r05;
	
	if(readReg(RDA5807M_REG_ADDR_05, &r05.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}
	
	r05.f.SEEKTH=threshold;
	
	if(writeReg(RDA5807M_REG_ADDR_05, r05.b)<0) {
		DBG("[%d] Failed to invoke writeReg().\n", __LINE__);
		goto failed;
	}
	
	return RDA5807M_OK;

failed:
	return RDA5807M_ERR_FAILED;
}

int RDA5807M_getSeekSNRThrshold(unsigned char *pThreshold) {
	RDA5807M_REG_05 r05;
	
	if(readReg(RDA5807M_REG_ADDR_05, &r05.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}
	
	*pThreshold=r05.f.SEEKTH;
	
	return RDA5807M_OK;

failed:
	return RDA5807M_ERR_FAILED;
}

int RDA5807M_setVolume(unsigned char volume) {
	RDA5807M_REG_05 r05;
	
	if(readReg(RDA5807M_REG_ADDR_05, &r05.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}
	
	r05.f.VOLUME=volume;
	
	if(writeReg(RDA5807M_REG_ADDR_05, r05.b)<0) {
		DBG("[%d] Failed to invoke writeReg().\n", __LINE__);
		goto failed;
	}
	
	return RDA5807M_OK;

failed:
	return RDA5807M_ERR_FAILED;
}

int RDA5807M_getVolume(unsigned char *pVolume) {
	RDA5807M_REG_05 r05;
	
	if(readReg(RDA5807M_REG_ADDR_05, &r05.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}
	
	*pVolume=r05.f.VOLUME;
	
	return RDA5807M_OK;

failed:
	return RDA5807M_ERR_FAILED;
}

int RDA5807M_setSoftBlendThreshold(unsigned char threshold) {
	RDA5807M_REG_07 r07;
	
	if(readReg(RDA5807M_REG_ADDR_07, &r07.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}
	
	r07.f.TH_SOFRBLEND=threshold;
	
	if(writeReg(RDA5807M_REG_ADDR_07, r07.b)<0) {
		DBG("[%d] Failed to invoke writeReg().\n", __LINE__);
		goto failed;
	}
	
	return RDA5807M_OK;

failed:
	return RDA5807M_ERR_FAILED;
}

int RDA5807M_getSoftBlendThreshold(unsigned char *pThreshold) {
	RDA5807M_REG_07 r07;
	
	if(readReg(RDA5807M_REG_ADDR_07, &r07.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}
	
	*pThreshold=r07.f.TH_SOFRBLEND;
	
	return RDA5807M_OK;

failed:
	return RDA5807M_ERR_FAILED;
}

int RDA5807M_setSoftBlendEnable(RDA5807M_BOOL flag) {
	RDA5807M_REG_07 r07;
	
	if(readReg(RDA5807M_REG_ADDR_07, &r07.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}
	
	r07.f.SOFTBLEND_EN=flag?1:0;
	
	if(writeReg(RDA5807M_REG_ADDR_07, r07.b)<0) {
		DBG("[%d] Failed to invoke writeReg().\n", __LINE__);
		goto failed;
	}
	
	return RDA5807M_OK;

failed:
	return RDA5807M_ERR_FAILED;
}

int RDA5807M_isSoftBlendEnable(RDA5807M_BOOL *pFlag) {
	RDA5807M_REG_07 r07;
	
	if(readReg(RDA5807M_REG_ADDR_07, &r07.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}
	
	*pFlag=r07.f.SOFTBLEND_EN?RDA5807M_TRUE:RDA5807M_FALSE;
	
	return RDA5807M_OK;

failed:
	return RDA5807M_ERR_FAILED;
}

int RDA5807M_isRDSReady(RDA5807M_BOOL *pFlag) {
	RDA5807M_REG_0A r0A;
	
	if(readReg(RDA5807M_REG_ADDR_0A, &r0A.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}
	
	*pFlag=r0A.f.RDSR?RDA5807M_TRUE:RDA5807M_FALSE;
	
	return RDA5807M_OK;

failed:
	return RDA5807M_ERR_FAILED;
}

int RDA5807M_isRDSSynced(RDA5807M_BOOL *pFlag) {
	RDA5807M_REG_0A r0A;
	
	if(readReg(RDA5807M_REG_ADDR_0A, &r0A.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}
	
	*pFlag=r0A.f.RDSS?RDA5807M_TRUE:RDA5807M_FALSE;
	
	return RDA5807M_OK;

failed:
	return RDA5807M_ERR_FAILED;
}

int RDA5807M_isBlockEFound(RDA5807M_BOOL *pFlag) {
	RDA5807M_REG_0A r0A;
	
	if(readReg(RDA5807M_REG_ADDR_0A, &r0A.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}
	
	*pFlag=r0A.f.BLK_E?RDA5807M_TRUE:RDA5807M_FALSE;
	
	return RDA5807M_OK;

failed:
	return RDA5807M_ERR_FAILED;
}

int RDA5807M_isStereo(RDA5807M_BOOL *pFlag) {
	RDA5807M_REG_0A r0A;
	
	if(readReg(RDA5807M_REG_ADDR_0A, &r0A.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}
	
	*pFlag=r0A.f.ST?RDA5807M_TRUE:RDA5807M_FALSE;
	
	return RDA5807M_OK;

failed:
	return RDA5807M_ERR_FAILED;
}

int RDA5807M_getRSSI(unsigned char *pRSSI) {
	RDA5807M_REG_0B r0B;
	
	if(readReg(RDA5807M_REG_ADDR_0B, &r0B.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}
	
	*pRSSI=r0B.f.RSSI;
	
	return RDA5807M_OK;

failed:
	return RDA5807M_ERR_FAILED;
}

int RDA5807M_getBLERA(unsigned char *pBLERA){
	RDA5807M_REG_0B r0B;
	
	if(readReg(RDA5807M_REG_ADDR_0B, &r0B.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}
	
	*pBLERA=r0B.f.BLERA;
	
	return RDA5807M_OK;

failed:
	return RDA5807M_ERR_FAILED;
}

int RDA5807M_getBLERB(unsigned char *pBLERB){
	RDA5807M_REG_0B r0B;
	
	if(readReg(RDA5807M_REG_ADDR_0B, &r0B.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}
	
	*pBLERB=r0B.f.BLERB;
	
	return RDA5807M_OK;

failed:
	return RDA5807M_ERR_FAILED;
}

int RDA5807M_isStation(RDA5807M_BOOL *pFlag) {
	RDA5807M_REG_0B r0B;
	
	if(readReg(RDA5807M_REG_ADDR_0B, &r0B.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}
	
	*pFlag=r0B.f.FM_TRUE?RDA5807M_TRUE:RDA5807M_FALSE;
	
	return RDA5807M_OK;

failed:
	return RDA5807M_ERR_FAILED;
}

int RDA5807M_isFMReady(RDA5807M_BOOL *pFlag) {
	RDA5807M_REG_0B r0B;

	if(readReg(RDA5807M_REG_ADDR_0B, &r0B.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}
	
	*pFlag=r0B.f.FM_READY?RDA5807M_TRUE:RDA5807M_FALSE;
	
	return RDA5807M_OK;

failed:
	return RDA5807M_ERR_FAILED;
}

int RDA5807M_getRDSA(unsigned short *pRDSA)
{
	RDA5807M_REG_0C r0;	
	if(readReg(RDA5807M_REG_ADDR_0C, &r0.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}	
	*pRDSA=r0.b;	
	return RDA5807M_OK;
failed:
	return RDA5807M_ERR_FAILED;	
}

int RDA5807M_getRDSB(unsigned short *pRDSB)
{
	RDA5807M_REG_0D r0;	
	if(readReg(RDA5807M_REG_ADDR_0D, &r0.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}	
	*pRDSB=r0.b;	
	return RDA5807M_OK;
failed:
	return RDA5807M_ERR_FAILED;	
}
int RDA5807M_getRDSC(unsigned short *pRDSC)
{
	RDA5807M_REG_0E r0;	
	if(readReg(RDA5807M_REG_ADDR_0E, &r0.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}	
	*pRDSC=r0.b;	
	return RDA5807M_OK;
failed:
	return RDA5807M_ERR_FAILED;	
}

int RDA5807M_getRDSD(unsigned short *pRDSD)
{
	RDA5807M_REG_0F r0;	
	if(readReg(RDA5807M_REG_ADDR_0F, &r0.b)<0) {
		DBG("[%d] Failed to invoke readReg().\n", __LINE__);
		goto failed;
	}	
	*pRDSD=r0.b;	
	return RDA5807M_OK;
failed:
	return RDA5807M_ERR_FAILED;	
}
