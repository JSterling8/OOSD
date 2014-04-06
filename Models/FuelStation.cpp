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
#include <deque>
#include <map>

namespace std {

#define LENGTH 100

bool arrived[LENGTH];
vector<FuelPump> pumps;
deque<Vehicle*> vehicleDeque;
map<string, bool> fuelTypes;

FuelStation::FuelStation() {
	// Initialize random seed:
	srand ( time(NULL) );

	// Set all of our fuel types to be false, because no pumps have been built yet.
	fuelTypes.insert(std::pair<string, int>("Diesel", false));
	fuelTypes.insert(std::pair<string, int>("Premium", false));
	fuelTypes.insert(std::pair<string, int>("Regular", false));
	fuelTypes.insert(std::pair<string, int>("Electric", false));

	// Fill the station with pumps.
	generatePumps();
}

void FuelStation::generatePumps() {
	// We can have 1-10 pumps
	pumps.reserve(rand() % 10 + 1);

	// This will be used to determing the pump's fuel type.
	int typeDecider = 0;

	string fuelType;

	// Loop through our pumps vector and randomly put in different types of pumps
	for (unsigned int i = 0; i < pumps.size(); ++i){
		// This is an int from 1-4 that will be used to determing the pump's fuel type.
		typeDecider = rand() % 4 + 1;

		if (typeDecider == 1){
			fuelType = "Diesel";
			if (!fuelTypes[fuelType]){
				fuelTypes[fuelType] = true;
			}
		}
		else if (typeDecider == 2){
			fuelType = "Premium";
			if (!fuelTypes[fuelType]){
				fuelTypes[fuelType] = true;
			}
		}
		else if (typeDecider == 3){
			fuelType = "Regular";
			if (!fuelTypes[fuelType]){
				fuelTypes[fuelType] = true;
			}
		}
		else if (typeDecider == 4){
			fuelType = "Electric";
			if (!fuelTypes[fuelType]){
				fuelTypes[fuelType] = true;
			}
		}
		pumps[i] = FuelPump(fuelType);
	}
}

/**
 * Uses POisson distribution to see if a vehicle has arrived at any second.
 */
void FuelStation::vehicleArrivedAt() {
	double bar = 10.0 * exp(-0.1);
	int pumpIndex = -1;
	for( int interval = 0; interval < LENGTH; ++interval ) {
		int dice = rand() % 10 + 1;
		// Handle vehicles arriving
		if ( dice > bar ) {
			arrived[interval] = true;
			Vehicle* v = generateRandomVehicle();
			cout << "Vehicle arrived at time: " << interval << endl;
			// Does this station have the fuel this vehicle needs?
			if (fuelTypes[v->getFuelType()]){
				// Is there a pump of the right type free?
				pumpIndex = getPump(v->getFuelType());
				// If there is a pump free (i.e., if pumpIndex isn't -1)
				if (pumpIndex >= 0){
					pumps[pumpIndex].setVehicleAtPump(v);
				}
				// If no pump is free, add the Vehicle to the end of the queue.
				else{
					vehicleDeque.push_back(v);
				}
			}
			else {
				cout << "Vehicle could not be served.  No pumps of that type." << endl;
				cout << "Vehicles fuel type: " << v->getFuelType() << endl;
				cout << "Diesel here: " << fuelTypes["Diesel"] << endl;
				cout << "Premium here: " << fuelTypes["Premium"] << endl;
				cout << "Regular here: " << fuelTypes["Regular"] << endl;
				cout << "Electric here: " << fuelTypes["Electric"] << endl;
				delete v;
			}
		}
		else {
			arrived[interval] = false;
		}

		// Loop through any pumps with vehicles and call the pump function.
		for (unsigned int j = 0; j < pumps.size(); ++j){
			if (pumps[j].isInUse()){
				pumps[j].pump();
			}
		}


		// Loop through any waiting vehicles
		for (unsigned int i = 0; i < vehicleDeque.size(); ++i){
			if (!vehicleDeque.empty()){
				Vehicle* temp = vehicleDeque.front();
				vehicleDeque.pop_front();

				pumpIndex = getPump(temp->getFuelType());

				// If there is a pump free (i.e., if pumpIndex isn't -1)
				if (pumpIndex >= 0){
					pumps[pumpIndex].setVehicleAtPump(temp);
				}
				else{
					vehicleDeque.push_back(temp);
				}
			}
		}

		// TODO If the pumping is complete log the data.
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

	string fuelType;

	// Randomly assigns a fuel type.
	int typeDecider = rand() % 4 + 1;

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
	return new Vehicle(fuelRemaining, tankSize, fuelType);
}

/**
 * @param fuelType the type of fuel needed.
 * @returns The index of a free pump with the right fuel type.  If none exists, it returns -1.
 */
int FuelStation::getPump(string fuelType){
	// Loop through the pumps.
	for(unsigned int i = 0; i < pumps.size(); ++i){
		// If a pump of the correct fuel type is available, return its index in the FuelPump vector.
		if (pumps[i].getFuelType() == fuelType && !pumps[i].isInUse()){
			return i;
		}
	}

	return -1;
}


} /* namespace std */
