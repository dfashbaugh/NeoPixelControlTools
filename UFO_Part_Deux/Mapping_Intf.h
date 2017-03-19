#pragma once

class Mapping_Intf 
{
public:
	Mapping_Intf() {};
	virtual ~Mapping_Intf() = 0;

	virtual int RunMapping(int ledNum, int Frame) = 0;
	virtual int GetIDNumber() = 0;
};