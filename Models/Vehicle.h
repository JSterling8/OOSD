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
	Vehicle(string);
	string toStringg();
	virtual ~Vehicle();

private:
	string brand;

};

} /* namespace std */

#endif /* VEHICLE_H_ */
