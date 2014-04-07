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

bool inUse;					// Whether or not this pump has a vehicle at it.
Vehicle* vehicleAtPump;		// The vehicle currently at the pump.
int pumpLoop;				// Used to control how long it takes to refuel the vehicle.  See the pump() method for more details.


/**
 *
 * @param fuelType The type of fuel that the pump has.  Used to set the flow rate.
 */
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

/**
 *
 * @return inUse Whether or not the fuel pump has a vehicle at it.  True means there's a vehicle at the pump and vice-versa.
 */
bool FuelPump::isInUse(){
	return inUse;
}

/**
 *
 * @return fuelType The type of fuel that the pump has.
 */
string FuelPump::getFuelType(){
	return fuelType;
}

/**
 *
 * @param v The vehicle which is at the pump.
 */
void FuelPump::setVehicleAtPump(Vehicle* v){
	vehicleAtPump = v;
	inUse = true;
	pumpLoop = 0;
}

/**
 *
 * @return vehicleAtPump The vehicle currently at the pump.
 */
Vehicle* FuelPump::getVehicleAtPump(){
	return vehicleAtPump;
}

/**
 * @return full Whether or not the vehicle is now full.
 */
bool FuelPump::pump(){
	bool full = false;

	// If the pumpLoop plus the flow rate is 15 or greater, add 1 unit of fuel to the vehicle.
	if ((pumpLoop + flowRate) >= 15){
		full = vehicleAtPump->addFuel(1);
		pumpLoop = 0;
	}

	// If the vehicle is now full, it will drive off, so the pump is now free.
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
