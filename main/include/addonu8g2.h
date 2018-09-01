#ifndef ADDONU8G2_H_
#define ADDONU8G2_H_

void playingU8g2();
void namesetU8g2(char* ici);
void statusU8g2(char* label);
void icy0U8g2(char* ici);
void icy4U8g2(char* ici);
void metaU8g2(char* ici);
char* getNameNumU8g2();
void scrollU8g2();
void drawFrameU8g2(uint8_t mTscreen,struct tm *dt);
void drawTTitleU8g2(char* ttitle);
void drawNumberU8g2(uint8_t mTscreen,char* irStr);
void drawStationU8g2(uint8_t mTscreen,char* snum,char* ddot);
void drawVolumeU8g2(uint8_t mTscreen,char* aVolume);
void drawTimeU8g2(uint8_t mTscreen,struct tm *dt,unsigned timein);
void lcd_initU8g2(uint8_t* lcd_type);
void setVolumeU8g2(uint16_t vol);
void drawLinesU8g2();
//uint8_t getCharset();
//void setCharset(uint8_t cy);

#endif /* ADDONU8G2_H_ */