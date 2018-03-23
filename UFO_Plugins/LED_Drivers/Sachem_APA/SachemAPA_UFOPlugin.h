#include "LED_Driver_Intf.h"

#include <VideoBoyAPA102.h>

// Adafruit_NeoPixel strip(50, 6, NEO_GRB + NEO_KHZ800);

class Sachem_APA_Driver : public LED_Driver_Intf
{
public:
	Sachem_APA_Driver (unsigned long numLEDs) 
		: Boys (numLEDs, 2.5, 255)
		, LEDPixels( (Pixels*)malloc(numLEDs*sizeof(Pixels)) )
		, NumberOfLEDs(numLEDs)
	{
		for(int i = 0; i < numLEDs; i++)
		{
			LEDPixels[i] = {0, 0, 0};
		}
	};
	virtual ~Sachem_APA_Driver() {};

	virtual void SetLEDColor(unsigned long LEDNum, Color LEDColor) {
		LEDPixels[LEDNum] = {LEDColor.Red, LEDColor.Green, LEDColor.Blue};
		
	};

	virtual void Show() {
		Boys.Show(LEDPixels); };

	virtual unsigned long GetNumberOfLEDs() {return NumberOfLEDs; };

private:
	Pixels* LEDPixels;
	unsigned long NumberOfLEDs;
	VideoBoy Boys;
};
