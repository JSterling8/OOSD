/*
 * FuelStation.cpp
 *
 *  Created on: 6 Apr 2014
 *      Author: Jon
 */

#include "FuelStation.h"
#include "Vehicle.h"

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
			Vehicle* v = generateRandomVehicle();
			cout << "Vehicle arrived at time: " << interval << endl;
			// Is there a pump of the right type free?

			// Yes - assign a pump
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

/**
 * Randomly generates a vehicle.
 * We need a random amount of fuel currently in the tank, a tank size,
 * and a fuel type.
 */
Vehicle* FuelStation::generateRandomVehicle() {
	// Tank size is between 1 and 30.
	int tankSize = rand() % 30 + 1;

	// Fuel remaining is between 0 and tankSize-1.
	int fuelRemaining = tankSize - (rand() % tankSize + 1);

	string typeOfFuel;

	// Randomly assigns a fuel type.
	int typeDecider = rand() % 4 + 1;
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

	// Returns a Vehicle with the three random variables calculated above.
	return new Vehicle(fuelRemaining, tankSize, typeOfFuel);
}

} /* namespace std */
