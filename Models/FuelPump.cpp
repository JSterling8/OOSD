/*
 * FuelPump.cpp
 *
 *  Created on: 18 Feb 2014
 *      Author: Jon
 */

#include "FuelPump.h"
#include <string>



FuelPump::FuelPump(std::string& fuelType, int flowRate) {
	FuelPump::fuelType = fuelType;
	FuelPump::flowRate = flowRate;
}



FuelPump::~FuelPump() {
	// TODO Auto-generated destructor stub
}
