/*
 * Vehicle.h
 *
 *  Created on: 18 Feb 2014
 *      Author: Jon
 */

#ifndef VEHICLE_H_
#define VEHICLE_H_

#include <iostream>
#include <string>

namespace std {

class Vehicle {
public:
	Vehicle(int, int, string);
	string toStringg();
	int getFuelRemaining();
	int getTankSize();
	string getFuelType();
	void addFuel(int);
	virtual ~Vehicle();

private:

};

} /* namespace std */

#endif /* VEHICLE_H_ */
