#pragma once
#include "UFO_Types.h"

////////////////////////////////
///// DEBUG PRINTING ///////////
////////////////////////////////
#ifndef ARDUINO
	#define PC_DEBUG
	extern unsigned long milliseconds;
	unsigned long GetMilliseconds();
#else
	#include <Arduino.h>
	unsigned long GetMilliseconds();
#endif

#ifdef PC_DEBUG
	#include <iostream>
	#include <String>
	using namespace std;
#endif

#ifdef PC_DEBUG
void DebugPrint(std::string myString);
#else
void DebugPrint(char* myString);
#endif

////////////////////////////////////
/////// Control Functions //////////
///////////////////////////////////
#include "UFO_Types.h"

int lerp(int a, int b, float t);
Color lerpColor(Color a, Color b, float t);
Color Wheel(int WheelPos);