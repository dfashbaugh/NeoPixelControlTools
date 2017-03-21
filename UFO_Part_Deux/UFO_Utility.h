////////////////////////////////
///// DEBUG PRINTING ///////////
////////////////////////////////
#ifndef ARDUINO
	#define PC_DEBUG
#else
	#include <Arduino.h>
#endif

#ifdef PC_DEBUG
	#include <iostream>
	#include <String>
	using namespace std;
#endif

#ifdef PC_DEBUG
void DebugPrint(std::string myString)
{
	cout << myString << endl;
}
#else
void DebugPrint(char* myString)
{
	Serial.println(myString);
}
#endif

////////////////////////////////////
/////// Control Functions //////////
///////////////////////////////////
#include "UFO_Types.h"