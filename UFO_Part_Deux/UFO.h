#include "DefaultPatterns.h"
#include "DefaultMappings.h"

class UFO 
{
public:
	UFO();
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

	unsigned long curFrame;	
	Pattern_Intf* Patterns[80];
	Mapping_Intf* Mappings[80];

	void FillDefaultPatterns();
	void FillDefaultMappings();
};