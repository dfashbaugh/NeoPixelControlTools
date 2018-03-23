#include <UFO.h>
#include "SachemAPA_UFOPlugin.h"
#include "Heep_UFOPlugin.h"

Heep_Comms* myComms;
Sachem_APA_Driver myDriver(100);
UFO* myUFO;

void setup()
{
	Serial.begin(115200);
	Serial.println("Started up");
	Heep_Comms* myComms = new Heep_Comms();
	myUFO = new UFO(&myDriver, myComms);

	Serial.println("Created UFO");
}

void loop()
{
	myUFO->RunUFO();

	delay(30);
}
