#pragma once
#include "UFO_Types.h"

class Communication_Intf
{
public:
	Communication_Intf() {};
	virtual ~Communication_Intf() {};

	virtual UFOSettings GetCommData() = 0;
};

class Simulation_Communication : public Communication_Intf 
{
public:
	Simulation_Communication() {};
	virtual ~Simulation_Communication() {};

	virtual UFOSettings GetCommData() {UFOSettings mySettings; mySettings.colors.Color1.Red = 50; mySettings.patternID = STRIPE_ID; return mySettings; };
};