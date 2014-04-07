/**
 * Main.cpp
 *
 *  Created on: 6 Apr 2014
 *      @author: Jonathan Sterling
 */

#include "..\Models\FuelStation.h"
#include <iostream>

using namespace std;


int main(int argc, char * argv[]) {
	// The loop control character.  By default it is set to 'y' so the application runs at least once.
	char again = 'y';

	// The number of stations in the simulation.
	int numOfStations;

	while(again == 'y'){
		numOfStations = 0;

		// Ask the user for a number of stations in the simulation.  Loop until they enter a valid number.
		while(numOfStations < 1 || numOfStations > 100){
			cout << "How many fuel stations do you want to simulate? (1-100)" << endl;
			cin >> numOfStations;
			if (numOfStations < 1 || numOfStations > 100){
				cout << "Please enter a number from 1-100." << endl;
			}
		}

		FuelStation* stations[numOfStations];

		// Loop through every fuel station and run the simulation in each of them.
		for (int i = 0; i < numOfStations; ++i){
			stations[i] = new FuelStation(10);
			cout << "Fuel station " << i+1 << ":" << endl;
			stations[i]->vehicleArrivedAt();
			delete stations[i];
		}

		// Start the program again from the beginning?
		cout << "Run again? y/n" << endl;
		cin >> again;
	}
}

