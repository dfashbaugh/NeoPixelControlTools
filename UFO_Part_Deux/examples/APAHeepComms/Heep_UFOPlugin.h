#pragma once
#include "UFO_Types.h"
#include "Communication_Intf.h"
#include "Heep_API.h"
#include "UFO_Utility.h"

UFOSettings mySettings;


//char deviceName [] = "ESPNewEEPROM";
//char deviceName [] = "HuzzahEEPROM";
char deviceName [] = "UFO Light";

char controlName0 [] = "Turn On";
Control control0;

char controlName1 [] = "Color1";
Control control1;

char controlName2 [] = "Pattern";
Control control2;

void InitializeHeepDevice()
{
	SetupHeepDevice(deviceName, 6);

	  control0.controlName = controlName0;
	  control0.controlID = 0;
	  control0.controlDirection = 0;
	  control0.controlType = 0;
	  control0.highValue = 100;
	  control0.lowValue = 0;
	  control0.curValue = 0;
	  AddControl(control0);

	  control1.controlName = controlName1;
	  control1.controlID = 1;
	  control1.controlDirection = 0;
	  control1.controlType = 1;
	  control1.highValue = 100;
	  control1.lowValue = 0;
	  control1.curValue = 100;
	  AddControl(control1);

	  control2.controlName = controlName2;
	  control2.controlID = 2;
	  control2.controlDirection = 0;
	  control2.controlType = 1;
	  control2.highValue = 3;
	  control2.lowValue = 1;
	  control2.curValue = 1;
	  AddControl(control2);

	  SetupHeepTasks();
  CreateInterruptServer(); 
}

class Heep_Comms : public Communication_Intf 
{
public:
	Heep_Comms() {
		Serial.println("Startup");
		InitializeHeepDevice();
	};

	virtual ~Heep_Comms() {};

	virtual UFOSettings GetCommData() {
		PerformHeepTasks();

		mySettings.colors.Color1.Red = map(GetControlValueByID(1), 0, 100, 0, 255);
		mySettings.colors.Color1.Green = map(GetControlValueByID(1), 0, 100, 0, 255);
		mySettings.colors.Color1.Blue = map(GetControlValueByID(1), 0, 100, 0, 255);

		if(GetControlValueByID(0) == 0)
		{
			mySettings.colors.Color1.Red = 0;
			mySettings.colors.Color1.Green = 0;
			mySettings.colors.Color1.Blue = 0;
		}

		mySettings.patternID = GetControlValueByID(2);

		return mySettings; 
	};
	
};