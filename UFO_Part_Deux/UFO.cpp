#include "UFO.h"

#define UFO_START_FRAME 999999

UFO::UFO()
	: frame(UFO_START_FRAME)
{
	FillDefaultPatterns();
	FillDefaultMappings();
	SetDefaultSettings();
}

UFO::~UFO()
{

}

void UFO::RunUFO()
{

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

void UFO::SetDefaultSettings()
{
	curSettings.rate = 1;
	curSettings.brightness = 256;
	curSettings.patternID = 1;
	curSettings.mappingID = 1;

	Color color1(255,255,255);
	Color color2(0,0,0);
	PatColors colors(color1, color2);
	curSettings.colors = colors;
}