#pragma once

#ifndef ARDUINO
#include <stdlib.h>
#define RANDOM(maxVal) rand()%maxVal 
#else
#include <Arduino.h>
#define RANDOM(maxVal) random(maxVal)
#endif

struct Color
{
	Color() {Red = 0; Green = 0; Blue = 0;};
	Color(int r, int g, int b) {Red = r; Green = g; Blue = b;};

	int Red;
	int Green;
	int Blue;
};

struct PatColors
{
	PatColors() {};
	PatColors(Color c1, Color c2) {Color1 = c1; Color2 = c2; };

	Color Color1;

	Color Color2;
};

struct UFOSettings
{
	UFOSettings() {rate = 1;
				   brightness = 255;
				   patternID = 1;
				   mappingID = 1; };

	int rate;
	int brightness;
	int patternID;
	int mappingID;
	PatColors colors;
};