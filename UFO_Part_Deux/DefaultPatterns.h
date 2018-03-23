#include "Pattern_Intf.h"
#include "UFO_Utility.h"

#define USER_PATTERN_ID_START 20 // Use this for patterns that are non default. Add every time a new pattern is created.

#define SOLID_COLOR_ID 1
class SolidColor : public Pattern_Intf 
{
public:
	SolidColor() {};
	virtual ~SolidColor() {};
	virtual Color RunPattern(int ledNum, int Frame, PatColors Colors, int totalLEDs) {return Colors.Color1;};
	virtual int GetIDNumber() {return SOLID_COLOR_ID; };
};

#define STRIPE_ID 2
class Stripe : public Pattern_Intf
{
public:
	Stripe() {};
	virtual ~Stripe() {};
	virtual Color RunPattern(int ledNum, int Frame, PatColors Colors, int totalLEDs) {
		int s = 6;
		if( (ledNum + Frame)/s % s < s/2)
			return Colors.Color1;
		return Colors.Color2;
	}
	virtual int GetIDNumber() {return STRIPE_ID; };
};

#define TOTES_RANDOM_ID 3
class TotesRandom : public Pattern_Intf
{
public:
	TotesRandom() {};
	virtual ~TotesRandom() {};
	virtual Color RunPattern(int ledNum, int frame, PatColors Colors, int totalLEDs){
		if ((ledNum + frame/10) % 2 == 0) 
    		return Color(RANDOM(255), RANDOM(255), RANDOM(255));
  		return Color(0, 0, 0);
	};

	virtual int GetIDNumber() {return TOTES_RANDOM_ID; };
};

#define FLICKER_STROBE_4_ID 4
class FlickerStrobe4 : public Pattern_Intf
{
public:
	FlickerStrobe4(int numLEDs) {
		selectLED1 = RANDOM(numLEDs);
		selectLED2 = RANDOM(numLEDs);
		selectLED3 = RANDOM(numLEDs);
		selectLED4 = RANDOM(numLEDs);
	};

	virtual ~FlickerStrobe4() {};
	virtual Color RunPattern(int ledNum, int frame, PatColors Colors, int totalLEDs){
  
		  if (ledNum == selectLED1 || 
		      ledNum == selectLED2) {
		    return Colors.Color1;;
		  } else if (ledNum == selectLED3 || 
		             ledNum == selectLED4) {
		    return Colors.Color2;
		  } 

		  return Color(0,0,0);
	};

	virtual int GetIDNumber() {return FLICKER_STROBE_4_ID; };

private:
	int selectLED1;
	int selectLED2;
	int selectLED3;
	int selectLED4;
};

#define GRADIENT_ID 5
class Gradient : public Pattern_Intf
{
public:
	Gradient(){};
	virtual ~Gradient() {};

	virtual Color RunPattern(int ledNum, int frame, PatColors Colors, int totalLEDs){
  		int r = 50;
  		if( ((ledNum + frame) / r) % 2 == 0)
  		{
  			return lerpColor(Colors.Color2, Colors.Color1, ((ledNum + frame) % r) / (float)r);
  		}
  		else
  		{
  			return lerpColor(Colors.Color1, Colors.Color2, ((ledNum + frame) % r) / (float)r);
  		}	
	};

	virtual int GetIDNumber() {return GRADIENT_ID; };
};

#define DRIP_GRADIENT_ID 6
class DripGradient : public Pattern_Intf
{
public:
	DripGradient(){};
	virtual ~DripGradient() {};

	virtual Color RunPattern(int ledNum, int frame, PatColors Colors, int totalLEDs){
  		int r = 50;
  		return lerpColor(Colors.Color1, Colors.Color2, ((ledNum + frame) % r) / (float)r);
	};

	virtual int GetIDNumber() {return DRIP_GRADIENT_ID; };
};

