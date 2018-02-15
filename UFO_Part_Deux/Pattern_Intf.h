#pragma once

#include "UFO_Types.h"

class Pattern_Intf 
{
public:
	Pattern_Intf() {};
	virtual ~Pattern_Intf() {};

	virtual Color RunPattern(int ledNum, int Frame, PatColors Colors, int totalLEDs) = 0;
	virtual int GetIDNumber() = 0;
};