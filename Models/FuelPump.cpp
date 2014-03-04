/*
 * FuelPump.cpp
 *
 *  Created on: 18 Feb 2014
 *      Author: Jon
 */

#include "FuelPump.h"
#include <string>



FuelPump::FuelPump(std::string robert) {
	// TODO Auto-generated constructor stub
	this->bob = robert;
}

std::string FuelPump::toString(){
	return bob;
}

FuelPump::~FuelPump() {
	// TODO Auto-generated destructor stub
}
