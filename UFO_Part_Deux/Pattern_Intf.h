#pragma once

class Pattern_Intf 
{
public:
	virtual Pattern_Intf() {};
	virtual ~Pattern_Intf() = 0;

	virtual void RunPattern(int ledNum, int Frame, PatColors Colors) = 0;
};