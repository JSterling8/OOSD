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

	while(again == 'y'){
		numOfStations = 0;

		cout << "Begin simulation? y/n" << endl;
		cin >> begin;

		while(numOfStations < 1 || numOfStations > 100){
			cout << "How many fuel stations do you want to simulate? (1-100)" << endl;
			cin >> numOfStations;
			if (numOfStations < 1 || numOfStations > 100){
				cout << "Please enter a number from 1-100." << endl;
			}
		}



		if(begin == 'y'){
			FuelStation* stations[numOfStations];
			for (int i = 0; i < numOfStations; ++i){
				stations[i] = new FuelStation();
				cout << "Fuel station " << i+1 << ":" << endl;
				stations[0]->vehicleArrivedAt();
			}
		}

		cout << "Run again? y/n" << endl;
		cin >> again;
	}
}

