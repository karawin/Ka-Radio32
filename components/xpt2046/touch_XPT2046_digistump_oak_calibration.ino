#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <XPT2046_Touchscreen.h>
#include <SPI.h>


//definitions, initialize parameters

#define TFT_DC  1                       //default pins for the Digistump Oak
#define TFT_CS  6

#define T_CS    5                       //chip select for touch


char s[30];                             //character arrays for text strings
char s2[30];

uint16_t calA[] = {15, 10};             //calibration points must be independent, i.e. not line up
uint16_t calB[] = {80, 280};
uint16_t calC[] = {200, 170};

uint16_t calA_raw[] = {0, 0};           //store raw touch data for calibration points
uint16_t calB_raw[] = {0, 0};
uint16_t calC_raw[] = {0, 0};

uint8_t calCount = 0;                   //track which point has been activated


Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
XPT2046_Touchscreen ts = XPT2046_Touchscreen(T_CS);


//SETUP

void setup() {
  pinMode(1, OUTPUT);
  
  pinMode(TFT_CS, OUTPUT);              //set TFT_CS low to communicate w screen
  digitalWrite(TFT_CS, LOW);
  pinMode(T_CS, OUTPUT);                //set T_CS high to disable touch input
  digitalWrite(T_CS, HIGH);

  tft.begin();                          //set up our screen
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);

  tft.setTextSize(1);                   //these should be self-explanatory
  tft.setCursor(20,43);
  tft.print("touch stylus to target centre");

  tft.setTextSize(2);
  tft.setCursor(20,25);
  tft.print("Calibrate Touch:");
  tft.setCursor(35,63);
  tft.print("X:");
  tft.setCursor(35,82);
  tft.print("Y:");
  tft.setCursor(35,101);
  tft.print("Z:");

  calibrationPoint(calA[0], calA[1]);   //display first calibration point

  ts.begin();                           //initialize touch screen
}


//MAIN LOOP

void loop() {
  if (ts.touched()) {                   //check for screen touch
    tft.fillRect(59, 63, 48, 54, ILI9341_BLACK);
                                        //black out X, Y, Z values
    TS_Point p = ts.getPoint();         //get touch data
    itoa(p.x, s, 10);                   //convert X data to char array
    tft.setCursor(59,63);
    tft.print(s);                       //and display
    itoa(p.y, s, 10);                   //same for Y value
    tft.setCursor(59,82);
    tft.print(s);
    itoa(p.z, s, 10);                   //and Z (pressure)
    tft.setCursor(59,101);
    tft.print(s);

    if (calCount == 0) {                //first calibration point?
      calA_raw[0] = p.x;                //store values
      calA_raw[1] = p.y; 

      tft.fillRect(calA[0]-6, calA[1]-6, 13, 13, ILI9341_BLACK);
                                        //black out calibration point
      delay(500);                       //give user time to take stylus off screen so as not to read same values into next calibration point
      calibrationPoint(calB[0], calB[1]);
                                        //and display the next calibration point
    }
    else if (calCount == 1) {           //do the same for the second calibration point
      calB_raw[0] = p.x;
      calB_raw[1] = p.y;

      tft.fillRect(calB[0]-6, calB[1]-6, 13, 13, ILI9341_BLACK);
      delay(500);
      calibrationPoint(calC[0], calC[1]);
    }
    else if (calCount == 2) {           //and third
      calC_raw[0] = p.x;
      calC_raw[1] = p.y;

      tft.fillRect(calC[0]-6, calC[1]-6, 13, 13, ILI9341_BLACK);

      tft.setTextSize(2);               //get ready to display calibration parameters
      tft.setCursor(20,130);
      tft.print("Parameters:");
      tft.setCursor(35,155);
      tft.print("X:");
      tft.setCursor(35,209);
      tft.print("Y:");

      //calculate calibration parameters

      int32_t delta = (calA_raw[0]-calC_raw[0])*(calB_raw[1]-calC_raw[1]) - (calB_raw[0]-calC_raw[0])*(calA_raw[1]-calC_raw[1]); 
      float alpha_x = (float)((calA[0]-calC[0])*(calB_raw[1]-calC_raw[1]) - (calB[0]-calC[0])*(calA_raw[1]-calC_raw[1])) / delta; 
      float beta_x = (float)((calA_raw[0]-calC_raw[0])*(calB[0]-calC[0]) - (calB_raw[0]-calC_raw[0])*(calA[0]-calC[0])) / delta;
      uint16_t delta_x = ((uint64_t)calA[0]*(calB_raw[0]*calC_raw[1]-calC_raw[0]*calB_raw[1]) - (uint64_t)calB[0]*(calA_raw[0]*calC_raw[1]-calC_raw[0]*calA_raw[1]) + (uint64_t)calC[0]*(calA_raw[0]*calB_raw[1]-calB_raw[0]*calA_raw[1])) / delta;
      float alpha_y = (float)((calA[1]-calC[1])*(calB_raw[1]-calC_raw[1]) - (calB[1]-calC[1])*(calA_raw[1]-calC_raw[1])) / delta; 
      float beta_y = (float)((calA_raw[0]-calC_raw[0])*(calB[1]-calC[1]) - (calB_raw[0]-calC_raw[0])*(calA[1]-calC[1])) / delta;
      uint16_t delta_y = ((uint64_t)calA[1]*(calB_raw[0]*calC_raw[1]-calC_raw[0]*calB_raw[1]) - (uint64_t)calB[1]*(calA_raw[0]*calC_raw[1]-calC_raw[0]*calA_raw[1]) + (uint64_t)calC[1]*(calA_raw[0]*calB_raw[1]-calB_raw[0]*calA_raw[1])) / delta;

      ftoa(alpha_x, s, 3);              //convert first parameter, a float value, to a character array
      tft.setCursor(59,155);
      tft.print(s);                     //and display
      ftoa(beta_x, s, 3);
      tft.setCursor(59,173);
      tft.print(s);  
      itoa(delta_x, s, 10);             //etc.
      tft.setCursor(59,191);
      tft.print(s);  
      ftoa(alpha_y, s, 3);
      tft.setCursor(59,209);
      tft.print(s);  
      ftoa(beta_y, s, 3);
      tft.setCursor(59,227);
      tft.print(s);  
      itoa(delta_y, s, 10);
      tft.setCursor(59,245);
      tft.print(s);  

      tft.setCursor(20,275);
      tft.print("[ Restart ]");
    }

    calCount++;
  }

  if (calCount == 4) {                  //finally, if another touch is detected
    tft.fillRect(0, 130, 240, 190, ILI9341_BLACK);
                                        //clear parameters from screen
    calibrationPoint(calA[0], calA[1]); //and start over
    calCount = 0;
  }

  delay(200);
}


//calibrationPoint() displays a calibration target on screen, using the Adafruit graphics functions

void calibrationPoint(uint16_t calX, uint16_t calY) {
  tft.drawCircle(calX, calY, 6, ILI9341_WHITE);
  tft.drawFastHLine(calX-4, calY, 9, ILI9341_WHITE);
  tft.drawFastVLine(calX, calY-4, 9, ILI9341_WHITE);
}


/*  Custom ftoa() function: converts float to string

Specifically: converts a float value to alphanumeric values in a zero-terminated char array, similar to itoa, and stores the result in the array specified by str.

Usage: ftoa (float value, char * str, uint8_t precision);

str should be an array long enough to contain any possible value. Precision indicates the number of significant figures in the result, not the number of decimals.

In this implementation, ftoa() handles floats with an integer component up to 4,294,967,295 in size; feel free to adapt to a uint64_t for an integer component of
up to 18,446,744,073,709,551,615. Since I don't need it, and it's faster, and uint64_t implementation in Arduino at times doesn't work, I've kept it as a uint_32
version. Also, if you need more than 10 significant figures in precision (*really???*) then you'll need to increase character array s1 accordingly - allow one
space for possible decimals, and one for zero-terminating the array */

void ftoa(float f, char *str, uint8_t precision) {
  uint8_t i, j, divisor = 1;
  int8_t log_f;
  int32_t int_digits = (int)f;                  //store the integer digits
  float decimals;
  char s1[12];

  memset(str, 0, sizeof(s));  
  memset(s1, 0, 10);

  if (f < 0) {                                  //if a negative number
    str[0] = '-';                               //start the char array with '-'
    f = abs(f);                                 //and store the number as its positive absolute value
  }

  log_f = ceil(log10(f));                       //determine the number of digits before the decimal

  if (log_f > 0) {                              //for a log value more than 0 (i.e. not a fraction between 0 and 1)
    if (log_f == precision) {                   //if the number of digits matches the number of significant figures desired
      f += 0.5;                                 //add 0.5 so when converting this number to integer, decimals >= 0.5 round up
      itoa(f, s1, 10);                          //itoa converts the number as integer to a char array
      strcat(str, s1);                          //append to either a '-' or nothing at all
    }
    else if ((log_f - precision) > 0) {         //if more integer digits than the number of significant digits desired
      i = log_f - precision;                    //calculate number of digits to discard
      for (j = 0; j < i; j++) divisor *= 10;    //calculate the number to divide by to isolate only our desired integer digits 
      f /= divisor;                             //divide
      f += 0.5;                                 //round 'er up when converting to int
      int_digits = (int)f;
      int_digits *= divisor;                    //and multiply back up to the original value, adjusted for significant figures
      itoa(int_digits, s1, 10);
      strcat(str, s1);
    }
    else {                                      //if more precision specified than there are integer digits,
      itoa(int_digits, s1, 10);
      strcat(str, s1);                          //and append
    }
  }

  else {                                        //for decimal fractions between 0 and 1, display leading 0
    s1[0] = '0';
    strcat(str, s1);
  }

  if (log_f < precision) {                      //if precision desired exceeds number of integer digits - process decimals
    strcat(str, ".");                           //append decimal point

    decimals = f - (int)f;                      //store decimal value as float
    i = precision - log_f;                      //number of decimals to read
    for (j = 0; j < i; j++) {                   //for each decimal,
      decimals *= 10;                           //multiply by 10 to convert it to an integer value
      if (j == (i-1)) decimals += 0.5;          //and if it's the last in our series, add 0.5 to round it
      itoa((int)decimals, s1, 10);              //append the integer to our character array
      strcat(str, s1);
      decimals -= (int)decimals;                //and remove it, storing the remaining the decimals back to the float
    }
  }
}


