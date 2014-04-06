/*
 * Main.cpp
 *
 *  Created on: 6 Apr 2014
 *      Author: Jon
 */

#include "..\Models\FuelStation.h"
#include <iostream>

using namespace std;


int main(int argc, char * argv[]) {
	char begin;
	char again = 'y';

	while(again == 'y'){
		cout << "Begin simulation? y/n" << endl;
		cin >> begin;

		if(begin == 'y'){
			FuelStation* station = new FuelStation();
			station->vehicleArrivedAt();
		}

		cout << "Run again? y/n" << endl;
		cin >> again;
	}
}

