#include "UFO.h"
#include "UFO_Utility.h"
#include "User_Options.h"

#define UFO_START_FRAME 999999



UFO::UFO(LED_Driver_Intf* _LED_Driver, Communication_Intf* _Comm_Interface)
	: curFrame(UFO_START_FRAME)
	, LED_Driver(_LED_Driver)
	, Comm_Interface(_Comm_Interface)
{
	FillDefaultPatterns();
	FillDefaultMappings();
}

UFO::~UFO()
{

}

void UFO::RunUFO()
{
	curSettings = Comm_Interface->GetCommData();
	curFrame += curSettings.rate;

	for(int i = 0; i < LED_Driver->GetNumberOfLEDs(); i++)
	{
		int mappedLED = Mappings[curSettings.mappingID]->RunMapping(i, curFrame);
		Color curLEDColor = Patterns[curSettings.patternID]->RunPattern(mappedLED, curFrame, curSettings.colors, LED_Driver->GetNumberOfLEDs());

#ifndef ARDUINO
		std::cout << "Cur LED: " << i << "; Cur ColorRGB: " << curLEDColor.Red << curLEDColor.Green << curLEDColor.Blue << std::endl;
#endif

		LED_Driver->SetLEDColor(i, curLEDColor);
	}

	LED_Driver->Show();
}

void UFO::SetPattern(Pattern_Intf* newPattern)
{
	Patterns[newPattern->GetIDNumber()] = newPattern;
}

void UFO::SetMapping(Mapping_Intf* newMapping)
{
	Mappings[newMapping->GetIDNumber()] = newMapping;
}

void UFO::FillDefaultPatterns()
{
	SetPattern(new SolidColor());

	SetPattern(new Stripe());

	SetPattern(new TotesRandom());

	SetPattern(new FlickerStrobe4(LED_Driver->GetNumberOfLEDs()));
}

void UFO::FillDefaultMappings()
{
	SetMapping(new ForwardMap());
}
