#include <UFO.h>
#include "AdafruitNeoPixel_UFOPlugin.h"
#include "SerialCommand_UFOPlugin.h"

SerialCommand_Comms* myComms;
Adafruit_NeoPixel_LED_Driver* myDriver;
UFO* myUFO;

void setup()
{
	Serial.begin(115200);
	Serial.println("Started up");
	SerialCommand_Comms* myComms = new SerialCommand_Comms();
	Adafruit_NeoPixel_LED_Driver* myDriver = new Adafruit_NeoPixel_LED_Driver(10, 6);
	myUFO = new UFO(myDriver, myComms);
}

void loop()
{
	myUFO->RunUFO();

	delay(30);
}