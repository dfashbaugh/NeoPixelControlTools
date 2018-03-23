#include <UFO.h>
#include "SachemAPA_UFOPlugin.h"
#include "SerialCommand_UFOPlugin.h"

SerialCommand_Comms* myComms;
Sachem_APA_Driver myDriver(100);
UFO* myUFO;

void setup()
{
	Serial.begin(115200);
	Serial.println("Started up");
	SerialCommand_Comms* myComms = new SerialCommand_Comms();
	myUFO = new UFO(&myDriver, myComms);

	Serial.println("Created UFO");
}

void loop()
{
	myUFO->RunUFO();

	delay(30);
}
