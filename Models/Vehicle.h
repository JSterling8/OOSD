/**
 * Vehicle.h
 *
 *  Created on: 18 Feb 2014
 *      @author: Jonathan Sterling
 */

#ifndef VEHICLE_H_
#define VEHICLE_H_

#include <iostream>
#include <string>

namespace std {

class Vehicle {
public:
	Vehicle(int, int, int, string);
	char* toCharArray();
	int getFuelRemaining();
	int getTankSize();
	string getFuelType();
	bool addFuel(int);
	virtual ~Vehicle();
private:

};

} /* namespace std */

#endif /* VEHICLE_H_ */
