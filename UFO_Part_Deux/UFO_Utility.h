#ifndef ARDUINO
	#define PC_DEBUG
#else
	#include <Arduino.h>
#endif

#ifdef PC_DEBUG
	#include <iostream>
	using namespace std;
#endif

void DebugPrint(char* myString)
{
#ifdef PC_DEBUG
	cout << myString << endl;
#else
	Serial.println(myString);
#endif
}