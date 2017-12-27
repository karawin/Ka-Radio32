/*
 * rda5807Task.c
 *
 *  Created on: 13.12.2017
 * 
 *		jp Cocatrix
 * Copyright (c) 2017, jp Cocatrix
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
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "rda5807Task.h"
#include "interface.h"
 
 
  // ----- actual RDS values
  uint8_t rdsGroupType;
  uint16_t rdsTP, rdsPTY;
  uint8_t _textAB, _last_textAB, _lastTextIDX;

  // Program Service Name
  char _PSName1[10]; // including trailing '\00' character.
  char _PSName2[10]; // including trailing '\00' character.
  char programServiceName[10];    // found station name or empty. Is max. 8 character long.

  uint16_t _lastRDSMinutes; ///< last RDS time send to callback.

  char _RDSText[64 + 2];
 
unsigned short pRDSA;
unsigned short pRDSB;
unsigned short pRDSC;
unsigned short pRDSD;

 
 
 
 
 
 // some usefull functions
 //-----------------------
 // seek up
 void seekUp()
 {
	RDA5807M_seek(true, false);
	initRds();	
}
 // seek down
 void seekDown()
{
	RDA5807M_seek(false, false);
	initRds();	
 }
 // Wait for seek complete. false if no station found
 bool seekingComplete()
 {
 	RDA5807M_BOOL res;
	vTaskDelay(1);
	do{
		RDA5807M_isSeekingFailed(&res);
		if (res) return false;
		RDA5807M_isSeekingComplete(&res);		
	} while (!res);
	return true;
 }
 // get frequency
 float getFrequency()
 {
 		unsigned long freq;
		RDA5807M_getFreq(&freq);	
		float temp = (freq)/1000.0; // Calculate freq float in MHz		
		return temp;
}
 
////////////////////////////////
// main task
void rda5807Task(void *pvParams)
{
	RDA5807M_BOOL pFlag;
 // init the FM radio
	RDA5807M_SETTING rxSetting={
	.clkSetting={
		.isClkNoCalb=RDA5807M_FALSE,
		.isClkDirInp=RDA5807M_FALSE,
		.freq=RDA5807M_CLK_FREQ_32_768KHZ,
	},
	.useRDS=RDA5807M_TRUE,
	.useNewDMMethod=RDA5807M_TRUE,
	.isDECNST50us=RDA5807M_FALSE,
	.system={
		.band=RDA5807M_BAND_87_108_MHZ,
		.is6576Sys=RDA5807M_FALSE,
		.space=RDA5807M_SPACE_100_KHZ
	}
	};

	RDA5807M_init(&rxSetting);
	RDA5807M_setFreq(89900);
	RDA5807M_enableOutput(RDA5807M_TRUE);
	RDA5807M_setVolume(15);
	RDA5807M_unmute(RDA5807M_TRUE); 
 	
	while (1)
	{
		vTaskDelay(10);
//		RDA5807M_getRDSA(&pRDSA);
		RDA5807M_isRDSReady(&pFlag);
		if (pFlag == RDA5807M_TRUE)
		{
			unsigned char pBLERA;
			unsigned char pBLERB;
			unsigned short pBlock[4];
			RDA5807M_getBLERA(&pBLERA);
			RDA5807M_getBLERB(&pBLERB);
			if ((pBLERA >= 1) || (pBLERB >= 1)) {/*printf("BLE: %x  %x\n",pBLERA,pBLERB);*/continue;}
			RDA5807M_getRDSA(&pRDSA);
			//RDA5807M_isBlockEFound(&pFlag);
			//if (!pFlag) printf("RDSA: %x\n",pRDSA);
			xSemaphoreTake(semI2C, portMAX_DELAY);
			RDA5807M_readRegOnly( pBlock,3) ;
			pRDSB = pBlock[0];
			pRDSC = pBlock[1];
			pRDSD = pBlock[2];
/*			
			pRDSA = pBlock[0];
			pRDSB = pBlock[1];
			pRDSC = pBlock[2];
			pRDSD = pBlock[3];
*/			
/*			RDA5807M_readRegOnly( &pRDSB,1) ;
			RDA5807M_readRegOnly( &pRDSC,1) ;
			RDA5807M_readRegOnly( &pRDSD,1) ;*/
			xSemaphoreGive(semI2C);
/*			RDA5807M_getRDSB(&pRDSB);
//			printf("RDSB: %x\n",pRDSB);
			RDA5807M_getRDSC(&pRDSC);
//			printf("RDSC: %x\n",pRDSC);
			RDA5807M_getRDSD(&pRDSD);
//			printf("RDSD: %x\n",pRDSD);
*/
			processData(pRDSA, pRDSB, pRDSC, pRDSD);
		}

	}
	vTaskDelete( NULL ); 
}

void initRds(){
    // reset all the RDS info.
    strcpy(_PSName1, "--------");
    strcpy(_PSName2, _PSName1);
    strcpy(programServiceName, "        ");
    memset(_RDSText, 0, sizeof(_RDSText));
    _lastTextIDX = 0;
}

void processData(unsigned short block1, unsigned short block2, unsigned short block3, unsigned short block4)
{
  // DEBUG_FUNC0("process");
  unsigned char  idx; // index of rdsText
  char c1, c2;
//  char *p;

//  unsigned short mins; ///< RDS time in minutes
//  unsigned char off;   ///< RDS time offset and sign

  // Serial.print('('); Serial.print(block1, HEX); Serial.print(' '); Serial.print(block2, HEX); Serial.print(' '); Serial.print(block3, HEX); Serial.print(' '); Serial.println(block4, HEX);

  if (block1 == 0) {
    // reset all the RDS info.
	initRds();	
// Send out empty data
	printf("programServiceName: %s\n",programServiceName);
	printf("_RDSText: %s\n",_RDSText);
//    if (_sendServiceName) _sendServiceName(programServiceName);
//    if (_sendText)        _sendText("");
    return;
  } // if

  // analyzing Block 2
  rdsGroupType = 0x0A | ((block2 & 0xF000) >> 8) | ((block2 & 0x0800) >> 11);
  rdsTP = (block2 & 0x0400);
  rdsPTY = (block2 & 0x0400);

  switch (rdsGroupType) {
  case 0x0A:
  case 0x0B:
    // The data received is part of the Service Station Name 
    idx = 2 * (block2 & 0x0003);

    // new data is 2 chars from block 4
    c1 = block4 >> 8;
    c2 = block4 & 0x00FF;

    // check that the data was received successfully twice
    // before publishing the station name

    if ((_PSName1[idx] == c1) && (_PSName1[idx + 1] == c2)) {
      // retrieved the text a second time: store to _PSName2
      _PSName2[idx] = c1;
      _PSName2[idx + 1] = c2;
      _PSName2[8] = '\0';

      if ((idx == 6) && strcmp(_PSName1, _PSName2) == 0) {
        if (strcmp(_PSName2, programServiceName) != 0) {
          // publish station name
          strcpy(programServiceName, _PSName2);
		  kprintf("##FM.NAME#: %s\n",programServiceName);
 //         if (_sendServiceName)
 //           _sendServiceName(programServiceName);
        } // if
      } // if
    } // if

    if ((_PSName1[idx] != c1) || (_PSName1[idx + 1] != c2)) {
      _PSName1[idx] = c1;
      _PSName1[idx + 1] = c2;
      _PSName1[8] = '\0';
      // Serial.println(_PSName1);
    } // if
    break;

  case 0x2A:
    // The data received is part of the RDS Text.
    _textAB = (block2 & 0x0010);
    idx = 4 * (block2 & 0x000F);

	
    if (idx < _lastTextIDX) {
      // the existing text might be complete because the index is starting at the beginning again.
      // now send it to the possible listener.
	  kprintf("##FM.TEXT#: %s\n",_RDSText);
 //     if (_sendText)
 //       _sendText(_RDSText);
    }
    _lastTextIDX = idx;

    if (_textAB != _last_textAB) {
      // when this bit is toggled the whole buffer should be cleared.
      _last_textAB = _textAB;
      memset(_RDSText, 0, sizeof(_RDSText));
      // Serial.println("T>CLEAR");
    } // if

	
    // new data is 2 chars from block 3
    _RDSText[idx] = (block3 >> 8); if(!isprint((int)_RDSText[idx]))  _RDSText[idx]= '_';  idx++;
    _RDSText[idx] = (block3 & 0x00FF); if(!isprint((int)_RDSText[idx]))  _RDSText[idx]= '_'; idx++;

    // new data is 2 chars from block 4
    _RDSText[idx] = (block4 >> 8);  if(!isprint((int)_RDSText[idx]))   _RDSText[idx]= '_';    idx++;
    _RDSText[idx] = (block4 & 0x00FF); if(!isprint((int)_RDSText[idx]))   _RDSText[idx]= '_'; idx++;

    // Serial.print(' '); Serial.println(_RDSText);
    // Serial.print("T>"); Serial.println(_RDSText);
    break;

  case 0x4A:
  /*
    // Clock time and date
    off = (block4)& 0x3F; // 6 bits
    mins = (block4 >> 6) & 0x3F; // 6 bits
    mins += 60 * (((block3 & 0x0001) << 4) | ((block4 >> 12) & 0x0F));

    // adjust offset
    if (off & 0x20) {
      mins -= 30 * (off & 0x1F);
    } else {
      mins += 30 * (off & 0x1F);
    }

    if (//(_sendTime) && 
		(mins != _lastRDSMinutes)) {
      _lastRDSMinutes = mins;
 //     _sendTime(mins / 60, mins % 60);
     printf("TIME: %d:%d\n",mins / 60,mins % 60);
    } // if
	*/
    break;

  case 0x6A:
    // IH
    break;

  case 0x8A:
    // TMC
    break;

  case 0xAA:
    // TMC
    break;

  case 0xCA:
    // TMC
    break;

  case 0xEA:
    // IH
    break;

  default:
    // Serial.print("RDS_GRP:"); Serial.println(rdsGroupType, HEX);
    break;
  }
} // processData()
 