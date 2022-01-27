
#ifndef ADDONCOMMON_H
#define ADDONCOMMON_H
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#define BUFLEN  256
#define LINES	9

extern   uint16_t y ;		//Height of a line
extern   uint16_t yy;		//Height of screen
extern   uint16_t x ;		//Width
extern   uint16_t z ;		// an internal offset for y

extern   struct tm *dt;
extern   uint16_t volume;

extern   char station[BUFLEN]; //received station
extern   char title[BUFLEN];	// received title
extern   char nameset[BUFLEN]; // the local name of the station

extern   char* lline[LINES] ; // array of ptr of n lines 
extern   uint8_t  iline[LINES] ; //array of index for scrolling
extern   uint8_t  tline[LINES] ;
extern   uint8_t  mline[LINES] ; // mark to display


extern   char nameNum[5] ; // the number of the current station
extern   char genre[BUFLEN/2]; // the local name of the station
#endif