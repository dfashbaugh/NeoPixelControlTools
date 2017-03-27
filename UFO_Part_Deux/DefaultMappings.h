#include "Mapping_Intf.h"

#define FORWARD_ID 1
class ForwardMap : public Mapping_Intf 
{
public:
	ForwardMap() {};
	virtual ~ForwardMap() {};
	virtual int RunMapping(int ledNum, int Frame) {return ledNum;};
	virtual int GetIDNumber() {return FORWARD_ID; };
};