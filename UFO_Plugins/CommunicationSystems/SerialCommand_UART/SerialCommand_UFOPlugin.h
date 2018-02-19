#pragma once
#include "UFO_Types.h"
#include "Communication_Intf.h"
#include "SerialCommand.h"

UFOSettings mySettings;
SerialCommand sCmd;

class SerialCommand_Comms : public Communication_Intf 
{
public:
	SerialCommand_Comms() {
		Serial.println("Startup");
		sCmd.addCommand("PATTERN",    SetPattern);  
		sCmd.addCommand("COLOR1",    SetColor1);  
		sCmd.addCommand("COLOR2",    SetColor2);  
		sCmd.addCommand("MAPPING", 	 SetMapping);
		sCmd.addCommand("RATE",		SetRate);
		sCmd.addCommand("BRIGHTNESS", SetBrightness);
	};

	virtual ~SerialCommand_Comms() {};

	virtual UFOSettings GetCommData() {
		sCmd.readSerial(); 
		return mySettings; 
	};

	static void SetBrightness()
	{
		char *arg;

		arg = sCmd.next();
		if (arg != NULL) {
			mySettings.brightness = atoi(arg);    // Converts a char string to an integer
			Serial.print("Brightness set to: "); Serial.println(mySettings.brightness);
		}
	}

	static void SetRate()
	{
		char *arg;

		arg = sCmd.next();
		if (arg != NULL) {
			mySettings.rate = atoi(arg);    // Converts a char string to an integer
			Serial.print("Rate set to: "); Serial.println(mySettings.rate);
		}
	}

	static void SetMapping()
	{
		char *arg;

		arg = sCmd.next();
		if (arg != NULL) {
			mySettings.mappingID = atoi(arg);    // Converts a char string to an integer
			Serial.print("Mapping set to: "); Serial.println(mySettings.mappingID);
		}
	}

	static void SetColor1()
	{
		char *arg;

		arg = sCmd.next();
		if (arg != NULL) {
			mySettings.colors.Color1.Red= atoi(arg);    // Converts a char string to an integer
		}

		arg = sCmd.next();
		if (arg != NULL) {
			mySettings.colors.Color1.Green = atoi(arg);    // Converts a char string to an integer
		}

		arg = sCmd.next();
		if (arg != NULL) {
			mySettings.colors.Color1.Blue = atoi(arg);    // Converts a char string to an integer
		}

		Serial.print("Color 1 set to: "); 
		Serial.print(mySettings.colors.Color1.Red);
		Serial.print(" ");
		Serial.print(mySettings.colors.Color1.Green);
		Serial.print(" ");
		Serial.println(mySettings.colors.Color1.Blue);
	}

	static void SetColor2()
	{
		char *arg;

		arg = sCmd.next();
		if (arg != NULL) {
			mySettings.colors.Color2.Red= atoi(arg);    // Converts a char string to an integer
		}

		arg = sCmd.next();
		if (arg != NULL) {
			mySettings.colors.Color2.Green = atoi(arg);    // Converts a char string to an integer
		}

		arg = sCmd.next();
		if (arg != NULL) {
			mySettings.colors.Color2.Blue = atoi(arg);    // Converts a char string to an integer
		}

		Serial.print("Color 2 set to: "); 
		Serial.print(mySettings.colors.Color2.Red);
		Serial.print(" ");
		Serial.print(mySettings.colors.Color2.Green);
		Serial.print(" ");
		Serial.println(mySettings.colors.Color2.Blue);
	}

	static void SetPattern()
	{
		char *arg;

		arg = sCmd.next();
		if (arg != NULL) {
			mySettings.patternID = atoi(arg);    // Converts a char string to an integer
			Serial.print("Pattern set to: "); Serial.println(mySettings.patternID);
		}
	}
	
};