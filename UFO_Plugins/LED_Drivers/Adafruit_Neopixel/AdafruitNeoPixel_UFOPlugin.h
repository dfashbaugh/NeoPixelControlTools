#include "LED_Driver_Intf.h"

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Adafruit_NeoPixel strip(50, 6, NEO_GRB + NEO_KHZ800);

class Adafruit_NeoPixel_LED_Driver : public LED_Driver_Intf
{
public:
	Adafruit_NeoPixel_LED_Driver (unsigned long numLEDs, int pin) 
		: strip(numLEDs, pin, NEO_GRB + NEO_KHZ800)
	{
		#if defined (__AVR_ATtiny85__)
    	if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  		#endif

		NumberOfLEDs = numLEDs; 
		strip.begin();
  		strip.show(); // Initialize all pixels to 'off'
	};
	virtual ~Adafruit_NeoPixel_LED_Driver() {};

	virtual void SetLEDColor(unsigned long LEDNum, Color LEDColor) {
		strip.setPixelColor(LEDNum, strip.Color(LEDColor.Red, LEDColor.Green, LEDColor.Blue));
	};

	virtual void Show() {strip.show(); };

	virtual unsigned long GetNumberOfLEDs() {return NumberOfLEDs; };

private:
	unsigned long NumberOfLEDs;
	Adafruit_NeoPixel strip;
};
