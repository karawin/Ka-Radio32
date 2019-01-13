#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <XPT2046_Touchscreen_calibrated.h>
#include <SPI.h>


// For the Digistump Oak, we're using these
#define TFT_DC  1
#define TFT_CS  6

// Add chip select for touch
#define T_CS    5


char s[10];
char s2[30];


Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
XPT2046_Touchscreen ts = XPT2046_Touchscreen(T_CS);


void setup() {
  pinMode(1, OUTPUT);
  
  pinMode(TFT_CS, OUTPUT);        //set TFT_CS low to communicate w screen
  digitalWrite(TFT_CS, LOW);
  pinMode(T_CS, OUTPUT);          //set T_CS high to disable touch input
  digitalWrite(T_CS, HIGH);

  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);


  tft.setCursor(20,20);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.print("Tap screen for values");
  tft.setCursor(35,43);
  tft.print("X:");
  tft.setCursor(35,62);
  tft.print("Y:");
  tft.setCursor(35,81);
  tft.print("Z:");

  ts.begin();
  
// Replace the following calibration factors as required by your screen, once derived using touch_XPT2046_digistump_oak_calibration.
// Last three parameters define the screen width and height at the current, and current rotation relative to default
//
//  ts.calibrate(-.00114, -.0653, 254, -.0885, -.00125, 348, 320, 240, 1);
}



////* MAIN LOOP

void loop() {
  delay(200);

  if (ts.touched()) {
    tft.fillRect(59, 43, 48, 53, ILI9341_BLACK);
                                        //black out X, Y, Z values
    s2[0] = 0;
    strcat(s2, "X: ");
    tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    TS_Point p = ts.getPoint();
    itoa(p.x, s, 10);
    tft.setCursor(59,43);
    tft.print(s);
    strcat(s2, s);
    strcat(s2, ", Y: ");
    itoa(p.y, s, 10);
    tft.setCursor(59,62);
    tft.print(s);
    strcat(s2, s);
    strcat(s2, ", Z: ");
    itoa(p.z, s, 10);
    tft.setCursor(59,81);
    tft.print(s);
    strcat(s2, s);
    Particle.publish("Touch sensor values", s2);
  }
}

