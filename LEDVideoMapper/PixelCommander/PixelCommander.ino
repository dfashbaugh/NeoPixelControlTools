#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

//#define RGBW

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      240

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.

#ifdef RGBW
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGBW + NEO_KHZ800);
#else
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#endif



int incomingByte = 0;   // for incoming serial data
int numBytes = 0;   // for incoming serial data
int intArray[] = {0,0,0,0};

int led2Light = 0;

void setup() {
        Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
        pixels.begin(); // This initializes the NeoPixel library.
        pixels.show();
}

void loop() {

    if(Serial.available() > 2)
    {
        Serial.println("InHere");
        for(int i = 0; i < pixels.numPixels(); i++)
        {
            pixels.setPixelColor(i, pixels.Color(0,0,0));
        }

        led2Light = Serial.parseInt();

        #ifdef RGBW
            pixels.setPixelColor(led2Light, pixels.Color(255,0,0));
        #else
            pixels.setPixelColor(led2Light, pixels.Color(0,255,0));
        #endif
        pixels.show();
    }


  delay(5);       
}