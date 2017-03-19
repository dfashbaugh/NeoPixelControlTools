#include "Pattern_Intf.h"

#define SOLID_COLOR_ID 1
class SolidColor : Pattern_Intf 
{
	SolidColor() {};
	virtual ~SolidColor() {};
	virtual Color RunPattern(int ledNum, int Frame, PatColors Colors) {return Colors.Color1;};
	virtual int GetIDNumber() {return SOLID_COLOR_ID; };
};