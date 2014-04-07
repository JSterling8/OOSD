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
	int numOfStations;
	int vehicleFrequency;

	while(again == 'y'){
		numOfStations = 0;

		while(numOfStations < 1 || numOfStations > 100){
			cout << "How many fuel stations do you want to simulate? (1-100)" << endl;
			cin >> numOfStations;
			if (numOfStations < 1 || numOfStations > 100){
				cout << "Please enter a number from 1-100." << endl;
			}
		}



		FuelStation* stations[numOfStations];
		for (int i = 0; i < numOfStations; ++i){
			stations[i] = new FuelStation(10);
			cout << "Fuel station " << i+1 << ":" << endl;
			stations[0]->vehicleArrivedAt();
		}

		cout << "Run again? y/n" << endl;
		cin >> again;
	}
}

