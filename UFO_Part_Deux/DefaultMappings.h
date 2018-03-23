#include "Mapping_Intf.h"

#define FORWARD_ID 1
class ForwardMap : public Mapping_Intf 
{
public:
	ForwardMap() {};
	virtual ~ForwardMap() {};
	virtual int RunMapping(int ledNum, int Frame, int sideStripLength) {return ledNum;};
	virtual int GetIDNumber() {return FORWARD_ID; };
};

#define HORIZONTAL_ID 2
class HorizontalMap : public Mapping_Intf
{
public:
	HorizontalMap() {};
	virtual ~HorizontalMap() {};
	virtual int RunMapping(int ledNum, int Frame, int sideStripLength) {
		return ledNum / (sideStripLength);
	};
	virtual int GetIDNumber() {return HORIZONTAL_ID; };
};

#define VERTICAL_ID 3
class VerticalMap : public Mapping_Intf
{
public:
	VerticalMap() {};
	virtual ~VerticalMap() {};
	virtual int RunMapping(int ledNum, int Frame, int sideStripLength) {
		int returnValue = ledNum % (sideStripLength);

  		if( (ledNum / (sideStripLength)) % 2)
  		{
    		returnValue = (sideStripLength - 1) - returnValue;
  		}

  		return returnValue;
	};
	virtual int GetIDNumber() {return VERTICAL_ID; };
};