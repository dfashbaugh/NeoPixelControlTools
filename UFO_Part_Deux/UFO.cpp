#include "UFO.h"
#include "UFO_Utility.h"
#include "User_Options.h"

#define MAX_FRAME_NO 1000000000
#define MIDDLE_FRAME_NO 10000000
#define MIN_FRAME_NO 200

UFO::UFO(LED_Driver_Intf* _LED_Driver, Communication_Intf* _Comm_Interface, unsigned long _minimumFrameTime, int _sideStripLength)
	: curFrame(MIDDLE_FRAME_NO)
	, LED_Driver(_LED_Driver)
	, Comm_Interface(_Comm_Interface)
	, sideStripLength(_sideStripLength)
	, minimumFrameTime(_minimumFrameTime)
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

	if(GetMilliseconds() - timeTracker > minimumFrameTime)
	{
		timeTracker = GetMilliseconds();
		curFrame += curSettings.rate;

		if(curFrame <= MIN_FRAME_NO)
			curFrame = MIDDLE_FRAME_NO;
		else if(curFrame >= MAX_FRAME_NO)
			curFrame = MIDDLE_FRAME_NO;

		for(int i = 0; i < LED_Driver->GetNumberOfLEDs(); i++)
		{
			int mappedLED = Mappings[curSettings.mappingID]->RunMapping(i, curFrame, sideStripLength);
			Color curLEDColor = Patterns[curSettings.patternID]->RunPattern(mappedLED, curFrame, curSettings.colors, LED_Driver->GetNumberOfLEDs());

#ifndef ARDUINO
			std::cout << "Cur LED: " << i << "; Cur ColorRGB: " << curLEDColor.Red << curLEDColor.Green << curLEDColor.Blue << std::endl;
#endif

			LED_Driver->SetLEDColor(i, curLEDColor);
		}

		LED_Driver->Show();
	}
	
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

	SetPattern(new Gradient());

	SetPattern(new DripGradient());
}

void UFO::FillDefaultMappings()
{
	SetMapping(new ForwardMap());

	SetMapping(new HorizontalMap());

	SetMapping(new VerticalMap());
}
