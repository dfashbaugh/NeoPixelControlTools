#include "DefaultPatterns.h"
#include "DefaultMappings.h"
#include "LED_Driver_Intf.h"
#include "Communication_Intf.h"

class UFO 
{
public:
	UFO(LED_Driver_Intf* _LED_Driver, Communication_Intf* _Comm_Interface, unsigned long _minimumFrameTime = 30, int _sideStripLength = 1);
	~UFO();

	void RunUFO();

	// Setters
	void SetCurrentPattern     (int patternID)         {curSettings.patternID = patternID; };
	void SetCurrentMapping     (int mappingID)     	   {curSettings.mappingID = mappingID; };
	void SetCurrentRate        (int rate)          	   {curSettings.rate = rate;};
	void SetCurrentBrightness  (int brightness)    	   {curSettings.brightness = brightness; };
	void SetColors             (PatColors colors)  	   {curSettings.colors = colors; };
	void SetAllCurrentSettings (UFOSettings settings)  {curSettings = settings; };

	// Getters
	int GetCurrentPattern()          {return curSettings.patternID; };
	int GetCurrentMapping()          {return curSettings.mappingID; };
	int GetCurrentRate()             {return curSettings.rate; };
	int GetCurrentBrightness()       {return curSettings.brightness; };
	PatColors GetCurrentColors()     {return curSettings.colors; };
	UFOSettings GetCurrentSettings() {return curSettings; };

private:
	UFOSettings curSettings;

	LED_Driver_Intf* LED_Driver;
	Communication_Intf* Comm_Interface;

	unsigned long curFrame;	
	Pattern_Intf* Patterns[80];
	Mapping_Intf* Mappings[80];

	int sideStripLength;

	unsigned long minimumFrameTime;
	unsigned long timeTracker;

	void SetPattern(Pattern_Intf* newPattern);
	void SetMapping(Mapping_Intf* newMapping);

	void FillDefaultPatterns();
	void FillDefaultMappings();
};