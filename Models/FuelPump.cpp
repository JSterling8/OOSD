/**
 * FuelPump.cpp
 *
 *  Created on: 18 Feb 2014
 *  @author: Jonathan Sterling
 */

#include "FuelPump.h"
#include "Vehicle.h"
#include <string>
#include <cstdlib>
#include <iostream>

namespace std {

bool inUse;
Vehicle* vehicleAtPump;
int pumpLoop;

FuelPump::FuelPump(std::string fuelType) {
	FuelPump::fuelType = fuelType;

	if (fuelType == "Diesel"){
		FuelPump::flowRate = 10;
	}
	else if (fuelType == "Regular" || fuelType == "Premium"){
		FuelPump::flowRate = 15;
	}
	else if (fuelType == "Electric"){
		FuelPump::flowRate = 3;
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

void FuelPump::setVehicleAtPump(Vehicle* v){
	vehicleAtPump = v;
	inUse = true;
	pumpLoop = 0;
}

Vehicle* FuelPump::getVehicleAtPump(){
	return vehicleAtPump;
}

/**
 * @return full Whether or not the vehicle is now full.
 */
bool FuelPump::pump(){
	bool full = false;

	if ((pumpLoop + flowRate) >= 15){
		full = vehicleAtPump->addFuel(1);
		pumpLoop = 0;
	}

	if(full){
		inUse = false;
	}

	pumpLoop++;
	return full;
}


FuelPump::~FuelPump() {
	// Auto-generated destructor stub
}

} /* namespace std */
