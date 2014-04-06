/*
 * FuelStation.cpp
 *
 *  Created on: 6 Apr 2014
 *      Author: Jon
 */

#include "FuelStation.h"

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

namespace std {

#define LENGTH 100

bool arrived[LENGTH];
vector<FuelPump> pumps;

FuelStation::FuelStation() {
	// Initialize random seed:
	srand ( time(NULL) );
	generatePumps();
}

void FuelStation::generatePumps() {
	// We can have 1-10 pumps
	pumps.reserve(rand() % 10 + 1);

	// Type decider is just used
	int typeDecider = 0;

	// Loop through our pumps vector and randomly put in different types of pumps
	for (unsigned int i = 0; i < pumps.size(); ++i){
		typeDecider = rand() % 4 + 1;
		string fuelType;
		if (typeDecider == 1){
			fuelType = "Diesel";
		}
		else if (typeDecider == 2){
			fuelType = "Premium";
		}
		else if (typeDecider == 3){
			fuelType = "Regular";
		}
		else if (typeDecider == 4){
			fuelType = "Electric";
		}
		pumps[i] = FuelPump(fuelType);
	}
}

void FuelStation::vehicleArrivedAt() {
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
