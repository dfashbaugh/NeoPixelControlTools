#pragma once

#include "UFO_Types.h"

class Pattern_Intf 
{
public:
	Pattern_Intf() {};
	virtual ~Pattern_Intf() = 0;

	virtual void RunPattern(int ledNum, int Frame, PatColors Colors) = 0;
};