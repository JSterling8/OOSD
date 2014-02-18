/*
 * Vehicle.cpp
 *
 *  Created on: 18 Feb 2014
 *      Author: Jon
 */

#include "Vehicle.h"

namespace std {


Vehicle::Vehicle(string brandEntered) {
	Vehicle::brand = brandEntered;

}

string Vehicle::toStringg() {
	return brand;
}


Vehicle::~Vehicle() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
