#ifndef ARDUINO
#include <iostream>
#include "UFO.h"

using namespace std;

int main(void)
{
	cout << "Begin Testing" << endl;

	Simulation_LED_Driver* myDriver = new Simulation_LED_Driver(40);
	Simulation_Communication* myComms = new Simulation_Communication();

	UFO myUFO(myDriver, myComms);
	myUFO.RunUFO();

	return 0;
}

#endif