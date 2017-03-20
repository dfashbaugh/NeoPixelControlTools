#include "UFO.h"

#define UFO_START_FRAME 999999

UFO::UFO()
	: curFrame(UFO_START_FRAME)
{
	FillDefaultPatterns();
	FillDefaultMappings();
}

UFO::~UFO()
{

}

void UFO::RunUFO()
{
	curFrame += curSettings.rate;
}

void UFO::FillDefaultPatterns()
{
	Pattern_Intf* SolidColorPattern = new SolidColor();
	Patterns[SolidColorPattern->GetIDNumber()] = SolidColorPattern;
}

void UFO::FillDefaultMappings()
{
	Mapping_Intf* ForwardMapping = new ForwardMap();
	Mappings[ForwardMapping->GetIDNumber()] = ForwardMapping;
}
