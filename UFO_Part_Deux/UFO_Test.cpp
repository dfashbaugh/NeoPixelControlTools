#ifndef ARDUINO
#include <iostream>
#include "UFO.h"

using namespace std;

int main(void)
{
	cout << "Begin Testing" << endl;

	UFO myUFO;
	myUFO.RunUFO();

	return 0;
}

#endif