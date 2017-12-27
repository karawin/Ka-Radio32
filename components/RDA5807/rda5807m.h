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

#ifndef RDA5807M_H
#define RDA5807M_H

#include "common.h"
#include "rda5807m_reg.h"
#include "rda5807m_data.h"

//RDA5807M's I2C addresses
#define RDA5807M_ADDR				(0x11)
#define RDA5807M_SEQADDR			(0x10)

void RDA5807M_dump(void);

bool RDA5807M_detection();

int RDA5807M_init(const RDA5807M_SETTING *pSetting);

int RDA5807M_enableOutput(RDA5807M_BOOL flag);

int RDA5807M_isOutputEnable(RDA5807M_BOOL *pFlag);

int RDA5807M_unmute(RDA5807M_BOOL flag);

int RDA5807M_isUnmute(RDA5807M_BOOL *pFlag);

int RDA5807M_setBB(RDA5807M_BOOL flag);

int RDA5807M_isBB(RDA5807M_BOOL *pFlag);

int RDA5807M_setFreq(unsigned long freq);

int RDA5807M_getFreq(unsigned long *pFreq);

int RDA5807M_seek(RDA5807M_BOOL isUp, RDA5807M_BOOL dontWrap);

int RDA5807M_isSeekingComplete(RDA5807M_BOOL *pFlag);

int RDA5807M_isSeekingFailed(RDA5807M_BOOL *pFlag);

int RDA5807M_stopSeeking(void);

int RDA5807M_setAFCDisable(RDA5807M_BOOL flag);

int RDA5807M_getAFCDisable(RDA5807M_BOOL *pFlag);

int RDA5807M_setSeekSNRThrshold(unsigned char threshold);

int RDA5807M_getSeekSNRThrshold(unsigned char *pThreshold);

int RDA5807M_setVolume(unsigned char volume);

int RDA5807M_getVolume(unsigned char *pVolume);

int RDA5807M_setSoftBlendThreshold(unsigned char threshold);

int RDA5807M_getSoftBlendThreshold(unsigned char *pThreshold);

int RDA5807M_setSoftBlendEnable(RDA5807M_BOOL flag);

int RDA5807M_isSoftBlendEnable(RDA5807M_BOOL *pFlag);

int RDA5807M_isRDSReady(RDA5807M_BOOL *pFlag);

int RDA5807M_isRDSSynced(RDA5807M_BOOL *pFlag);

int RDA5807M_isBlockEFound(RDA5807M_BOOL *pFlag);

int RDA5807M_isStereo(RDA5807M_BOOL *pFlag);

int RDA5807M_getRSSI(unsigned char *pRSSI);

int RDA5807M_isStation(RDA5807M_BOOL *pFlag);

int RDA5807M_isFMReady(RDA5807M_BOOL *pFlag);

int RDA5807M_getBLERA(unsigned char *pBLERA);

int RDA5807M_getBLERB(unsigned char *pBLERB);

int RDA5807M_getRDSA(unsigned short *pRDSA);
int RDA5807M_getRDSB(unsigned short *pRDSB);
int RDA5807M_getRDSC(unsigned short *pRDSC);
int RDA5807M_getRDSD(unsigned short *pRDSD);

#endif
