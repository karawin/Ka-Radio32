// common data for ucg or u8g
// to avoid double space (only one type of screen per conf.

#include "addoncommon.h"
#include "stdlib.h"

  uint16_t y ;		//Height of a line
  uint16_t yy;		//Height of screen
  uint16_t x ;		//Width
  uint16_t z ;		// an internal offset for y

  struct tm *dt;
  uint16_t volume;

  char station[BUFLEN]; //received station
  char title[BUFLEN];	// received title
  char nameset[BUFLEN]; // the local name of the station

  char* lline[LINES] ; // array of ptr of n lines 
  uint8_t  iline[LINES] ; //array of index for scrolling
  uint8_t  tline[LINES] ;
  uint8_t  mline[LINES] ; // mark to display


  char nameNum[5] ; // the number of the current station
  char genre[BUFLEN/2]; // the local name of the station


