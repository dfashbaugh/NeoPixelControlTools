#pragma once

#include "UFO_Types.h"

class Pattern_Intf 
{
public:
	Pattern_Intf() {};
	virtual ~Pattern_Intf() = 0;

	virtual Color RunPattern(int ledNum, int Frame, PatColors Colors) = 0;
	virtual int GetIDNumber() = 0;
};