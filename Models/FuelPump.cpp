/*
 * FuelPump.cpp
 *
 *  Created on: 18 Feb 2014
 *      Author: Jon
 */

#include "FuelPump.h"
#include <string>



FuelPump::FuelPump(std::string& fuelType) {
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
}



FuelPump::~FuelPump() {
	// TODO Auto-generated destructor stub
}
