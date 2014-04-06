/*
 * FuelStation.cpp
 *
 *  Created on: 6 Apr 2014
 *      Author: Jon
 */

#include "FuelStation.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

namespace std {

#define LENGTH 100

bool arrived[LENGTH];

FuelStation::FuelStation() {
	// Initialize random seed:
	srand ( time(NULL) );
	generatePumps();
}

void generatePumps() {
	int numOfPumps = rand() % 10 + 1;
	FuelStation::pumps[numOfPumps];

	int typeDecider = 0;
	for (int i = 0; i < numOfPumps; ++i){
		typeDecider = rand() % 4 + 1;
		if (typeDecider == 1){
			FuelStation::pumps[i] = new FuelPump("Diesel");
		}
		else if (typeDecider == 2){
			FuelStation::pumps[i] = new FuelPump("Premium");
		}
		else if (typeDecider == 3){
			FuelStation::pumps[i] = new FuelPump("Regular");
		}
		else if (typeDecider == 4){
			FuelStation::pumps[i] = new FuelPump("Electric");
		}
	}
}

void vehicleArrivedAt() {



	double bar = 10.0 * exp(-0.1);
	for( int interval = 0; interval < LENGTH; ++interval ) {
		int dice = rand() % 10 + 1;
		// Handle vehicles arriving
		if ( dice > bar ) {
			arrived[interval] = true;
			cout << "Vehicle arrived at time: " << interval << endl;
			// Is there a pump free?
			// Yes - assign sales person
			// No - add customer to queue
		}
		else {
			arrived[interval] = false;
		}
		//Handle sales people and existing customers
		//Is there a customer waiting
		//Is a sales person available?

		//If the transaction is complete log the data.
	}
}

} /* namespace std */
