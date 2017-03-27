#include "UFO.h"
#include "UFO_Utility.h"
#include "User_Options.h"
#include "LED_Driver_Intf.h"
#include "Communication_Intf.h"

#define UFO_START_FRAME 999999

LED_Driver_Intf* LED_Driver;
Communication_Intf* Comm_Interface;

UFO::UFO()
	: curFrame(UFO_START_FRAME)
{
	FillDefaultPatterns();
	FillDefaultMappings();
	LED_Driver = GetLEDDriver(numLEDs);
	Comm_Interface = GetCommInterface();
}

UFO::~UFO()
{

}

void UFO::RunUFO()
{
	curSettings = Comm_Interface->GetCommData();
	curFrame += curSettings.rate;

	for(int i = 0; i < numLEDs; i++)
	{
		int mappedLED = Mappings[curSettings.mappingID]->RunMapping(i, curFrame);
		Color curLEDColor = Patterns[curSettings.patternID]->RunPattern(mappedLED, curFrame, curSettings.colors);
		LED_Driver->SetLEDColor(i, curLEDColor);
	}
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
