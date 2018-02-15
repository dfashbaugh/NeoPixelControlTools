#include "Pattern_Intf.h"

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



