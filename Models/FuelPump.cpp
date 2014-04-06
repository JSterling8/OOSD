/*
 * FuelPump.cpp
 *
 *  Created on: 18 Feb 2014
 *      Author: Jon
 */

#include "FuelPump.h"
#include "Vehicle.h"
#include <string>
#include <cstdlib>

namespace std {

bool inUse;
Vehicle* vehicleAtPump;

FuelPump::FuelPump(std::string fuelType) {
	FuelPump::fuelType = fuelType;

	if (fuelType == "Diesel"){
		FuelPump::flowRate = 10;
	}
	else if (fuelType == "Regular" || fuelType == "Premium"){
		FuelPump::flowRate = 15;
	}
	else if (fuelType == "Electric"){
		FuelPump::flowRate = 2;
	}
	// Default flow rate for unknown/miscellanious fuel types:
	else {
		FuelPump::flowRate = 8;
	}

	inUse = false;
}

bool FuelPump::isInUse(){
	return inUse;
}

string FuelPump::getFuelType(){
	return fuelType;
}

void FuelPump::pump(Vehicle* v){
	vehicleAtPump = v;
}

void FuelPump::pump(){
	bool full = vehicleAtPump->addFuel(1);

	if(full){
		isInUse = false;
	}
}


FuelPump::~FuelPump() {
	// Auto-generated destructor stub
}

} /* namespace std */
