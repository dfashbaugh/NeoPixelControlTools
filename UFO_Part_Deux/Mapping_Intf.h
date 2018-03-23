#pragma once

class Mapping_Intf 
{
public:
	Mapping_Intf() {};
	virtual ~Mapping_Intf() {};

	virtual int RunMapping(int ledNum, int Frame, int sideStripLength) = 0;
	virtual int GetIDNumber() = 0;
};