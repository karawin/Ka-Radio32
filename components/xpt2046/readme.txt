Adapted to KaRadio32 esp_idf
See the original at http://www.ars-informatica.ca/eclectic/calibrated-xpt2046-touch-library-for-arduino-and-compatibles/


This revised library is based on Paul Stoffregen's XPT2046_Touchscreen at https://github.com/PaulStoffregen/XPT2046_Touchscreen, please see the GitHub repository for basic usage. It works with ESP8266-based chips, uses SPI, supports and documents IRQ functionality, reports pressure values, and compensates for fluctuations on initial touch readings, and does so cleanly.

The XPT2046_Touchscreen_calibrated modification adds a calibrate function to convert touch screen coordinates to pixel values. This function and revised library are not Digistump Oak specific.

The sample sketch used to derive calibration parameters, touch_XPT2046_digistump_oak_calibration.ino, is Oak-only, but should be very easily adapted to any Arduino-type processor using the Adafruit graphics library - likely would only need to have pin definitions changed, and possibly the screen controller library (ILI9341 in this example).

Sketch touch_XPT2046_digistump_oak.ino is also for the Digistump Oak, but would be adapted just as easily. As written it displays raw touch values. Uncomment the 

//  ts.calibrate(-.00114, -.0653, 254, -.0885, -.00125, 348, 320, 240, 1);

line and it will now show pixel coordinates. The calibration parameters above are particular to my test screen, but may work with other screens using the ILI9341 and XPT2046 controllers.

Usage: the first six parameters are the calibration values we get from touch_XPT2046_digistump_oak_calibration, and the next two are the screen width and height in the screen orientation you will be using. The final optional parameter sets the screen rotation; 0 gives the original unrotated orientation, 1 defines a 90 degree counter-clockwise rotation, 2 defines 180 degrees counter-clockwise, and 3 is 270 degrees. This matches most screens with most graphics libraries - but not all. Please check.

Users of the Digistump Oak should note that their version of SPI.h may cause erroneous values. See more at http://www.ars-informatica.ca/eclectic/digistump-oak-with-a-touch-enabled-display-screen-circuit-and-code/. The entire project is described starting at http://www.ars-informatica.ca/eclectic/tutorial-digistump-oak-with-a-touch-enabled-display-screen/. 

Three-point calibration has been implemented using Fang and Chang's _Calibration in touch-screen systems_, http://www.ti.com/lit/an/slyt277/slyt277.pdf, Analog Applications Journal, 2007.

The modified software is released under the same conditions as the original. Specifically, permission is hereby granted to use, copy, modify, merge, publish, distribute, sublicense, etc. copies of the Software, provided that  the original copyright notice and permission are included in all copies or derived works.


