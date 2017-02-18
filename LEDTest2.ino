#include <TimerOne.h>
#include "LPD6803.h"

//Example to control LPD6803-based RGB LED Modules in a strand
// Original code by Bliptronics.com Ben Moyes 2009
//Use this as you wish, but please give credit, or at least buy some of my LEDs!

// Code cleaned up and Object-ified by ladyada, should be a bit easier to use

/*****************************************************************************/

// Choose which 2 pins you will use for output.
// Can be any valid output pins.
int dataPin = 2;       // 'yellow' wire
int clockPin = 3;      // 'green' wire
int =a;
// Don't forget to connect 'blue' to ground and 'red' to +5V

// Timer 1 is also used by the strip to send pixel clocks

// Set the first variable to the NUMBER of pixels. 20 = 20 pixels in a row
LPD6803 strip = LPD6803(24, dataPin, clockPin);


void setup() {
  strip.setCPUmax(50);  // start with 50% CPU usage. up this if the strand flickers or is slow
  // Start up the LED counter
  strip.begin();
  // Update the strip, to start they are all 'off'
  strip.show();
  Serial.begin(9600);
}


void loop() {
  if (Serial.available()) {
    a = Serial.parseInt();
   }
  if (a==0) {
    colorWipe(1,4,Color(0,255,0), 50);
    colorWipe(5,9,Color(255,0,0),50);
    
    }
   else if (a == 1) {
      colorWipe(1,4, Color(255,0,0),50);
      colorWipe(5,9, Color(9,255,0),50);
  }

}


void colorWipe(int d, int e, uint16_t c, uint8_t wait) {
  int i;
  
  for (i=d-1; i < e+1; i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

/* Helper functions */

// Create a 15 bit color value from R,G,B
unsigned int Color(byte r, byte g, byte b)
{
  //Take the lowest 5 bits of each value and append them end to end
  return( ((unsigned int)g & 0x1F )<<10 | ((unsigned int)b & 0x1F)<<5 | (unsigned int)r & 0x1F);
}

//Input a value 0 to 127 to get a color value.
//The colours are a transition r - g -b - back to r
unsigned int Wheel(byte WheelPos)
{
  byte r,g,b;
  switch(WheelPos >> 5)
  {
    case 0:
      r=31- WheelPos % 32;   //Red down
      g=WheelPos % 32;      // Green up
      b=0;                  //blue off
      break; 
    case 1:
      g=31- WheelPos % 32;  //green down
      b=WheelPos % 32;      //blue up
      r=0;                  //red off
      break; 
    case 2:
      b=31- WheelPos % 32;  //blue down 
      r=WheelPos % 32;      //red up
      g=0;                  //green off
      break; 
  }
  return(Color(r,g,b));
}

    
    
