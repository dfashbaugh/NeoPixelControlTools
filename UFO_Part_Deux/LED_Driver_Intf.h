#pragma once
#include "UFO_Types.h"

class LED_Driver_Intf
{
public:
	LED_Driver_Intf () {};
	virtual ~LED_Driver_Intf() {};

	virtual void SetLEDColor(unsigned long LEDNum, Color LEDColor) = 0;
};

class Simulation_LED_Driver : public LED_Driver_Intf
{
public:
	Simulation_LED_Driver (unsigned long numLEDs) {NumberOfLEDs = numLEDs; };
	virtual ~Simulation_LED_Driver() {};

	virtual void SetLEDColor(unsigned long LEDNum, Color LEDColor) {};

private:
	unsigned long NumberOfLEDs;
};

LED_Driver_Intf* GetLEDDriver(unsigned long numLEDs)
{
	return new Simulation_LED_Driver(numLEDs);
}