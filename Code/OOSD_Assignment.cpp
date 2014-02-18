//============================================================================
// Name        : OOSD_Assignment.cpp
// Author      : Jonathan Sterling
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "../Models/Vehicle.h"
#include "../Models/AutoFuelPump.h"


using namespace std;

Vehicle * v;
string s;

int main() {
	v = new Vehicle("Jaguar");

	s = v->toStringg();

	cout << "The brand is: " << s << endl;

	return 0;
}
