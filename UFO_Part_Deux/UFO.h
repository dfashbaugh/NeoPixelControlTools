#include "DefaultPatterns.h"
#include "DefaultMappings.h"

class UFO 
{
public:
	UFO();
	~UFO();

	void RunUFO();

private:
	unsigned long frame;	
	Pattern_Intf* Patterns[80];
	Mapping_Intf* Mappings[80];

	void FillDefaultPatterns();
	void FillDefaultMappings();
};