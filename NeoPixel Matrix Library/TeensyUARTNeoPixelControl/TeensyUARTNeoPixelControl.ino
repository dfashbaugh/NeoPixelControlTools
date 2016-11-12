#include <FastLED.h>

#define NUM_LEDS 640
#define MEMORY_SIZE NUM_LEDS*3

byte drawingMemory[MEMORY_SIZE];

CRGB leds1[64];
CRGB leds2[64];
CRGB leds3[64];
CRGB leds4[64];
CRGB leds5[64];
CRGB leds6[64];
CRGB leds7[128];
CRGB leds8[128];

long memoryCounter = 0;

int recvState = 0;
void CheckForDelimeter(byte recvInfo)
{
	if(recvInfo == 's' && recvState == 0)
		recvState = 1;
	else if(recvInfo == 't' && recvState == 1)
		recvState = 2;
	else if(recvInfo == 'a' && recvState == 2)
		recvState = 3;
	else if(recvInfo == 'r' && recvState == 3)
		recvState = 4;
	else if(recvInfo == 't' && recvState == 4)
	{
		recvState = 0;
		memoryCounter = 0;
	}
	else
		recvState = 0;
}

void setup()
{
	Serial.begin(500000);
	FastLED.addLeds<WS2812B, 2,  GRB>(leds1, 64);
    FastLED.addLeds<WS2812B, 14, GRB>(leds2, 64);
    FastLED.addLeds<WS2812B, 7,  GRB>(leds3, 64);
    FastLED.addLeds<WS2812B, 8,  GRB>(leds4, 64);
    FastLED.addLeds<WS2812B, 6,  GRB>(leds5, 64);
    FastLED.addLeds<WS2812B, 20, GRB>(leds6, 64);
    FastLED.addLeds<WS2812B,  21, GRB>(leds7, 128);
    FastLED.addLeds<WS2812B,  5, GRB>(leds8, 128);
   	FastLED.show();
}

long lastMillis = 0;

void loop ()
{
	if(Serial.available())
	{
		byte recvInfo = Serial.read();

		if(memoryCounter < MEMORY_SIZE)
		{
			recvInfo = map(recvInfo, 0, 255, 0, 128);
			drawingMemory[memoryCounter] = recvInfo;
			memoryCounter++;
		}

		CheckForDelimeter(recvInfo);
	}

	if(memoryCounter == MEMORY_SIZE)
	{

		for(int i = 0; i < NUM_LEDS; i++)
		{
			CRGB myColor;
			myColor.green = drawingMemory[i*3];
			myColor.red = drawingMemory[i*3+1];
			myColor.blue = drawingMemory[i*3+2];

			if(i < 64) // Strip 1
				leds1[i] = myColor;
			else if(i < 128) // Strip 2
				leds2[i%64] = myColor;
			else if(i < 192) // Strip 3
				leds3[i%64] = myColor;
			else if(i < 256) // Strip 4
				leds4[i%64] = myColor;
			else if(i < 320) // Strip 5
				leds5[i%64] = myColor;
			else if(i < 384) // Strip 6
				leds6[i%64] = myColor;
			else if(i < 512) // Strip 7
				leds7[i%128] = myColor;
			else if(i < 640) // Strip 8
				leds8[i%128] = myColor;
		}

         FastLED.show();
	}
}

