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

#ifndef RDA5807M_DATA_H
#define RDA5807M_DATA_H

//Data types
#define RDA5807M_BOOL				unsigned char
#define RDA5807M_TRUE				(0xff)
#define RDA5807M_FALSE				(0x00)

#define RDA5807M_OK					(0)
#define RDA5807M_ERR_FAILED			(-1)

enum {
	RDA5807M_CLK_FREQ_32_768KHZ=0,
	RDA5807M_CLK_FREQ_12MHZ,
	RDA5807M_CLK_FREQ_13MHZ,
	RDA5807M_CLK_FREQ_19_2MHZ,
	RDA5807M_CLK_FREQ_UNUSED,
	RDA5807M_CLK_FREQ_24MHZ,
	RDA5807M_CLK_FREQ_26MHZ,
	RDA5807M_CLK_FREQ_38_4MHZ
};

enum {
	RDA5807M_BAND_87_108_MHZ=0,
	RDA5807M_BAND_76_91_MHZ,
	RDA5807M_BAND_76_108_MHZ,
	RDA5807M_BAND_65_76MHZ
};

enum {
	RDA5807M_SPACE_100_KHZ=0,
	RDA5807M_SPACE_200_KHZ,
	RDA5807M_SPACE_50_KHZ,
	RDA5807M_SPACE_25_KHZ
};

typedef struct {
	struct {
		RDA5807M_BOOL isClkNoCalb;
		RDA5807M_BOOL isClkDirInp;
		unsigned char freq;
	} clkSetting;
	RDA5807M_BOOL useRDS;
	RDA5807M_BOOL useNewDMMethod;
	RDA5807M_BOOL isDECNST50us;
	struct {
		unsigned char band;
		RDA5807M_BOOL is6576Sys;
		unsigned char space;
	} system;
} RDA5807M_SETTING;

#endif
