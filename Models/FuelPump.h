/*
 * FuelPump.h
 *
 *  Created on: 18 Feb 2014
 *      Author: Jon
 */

#ifndef FUELPUMP_H_
#define FUELPUMP_H_

#include <string>
#include "Vehicle.h"

namespace std {


class FuelPump {
public:
	FuelPump(string);
	bool isInUse();
	string getFuelType();
	void pump(Vehicle*);
	void pump();
	virtual ~FuelPump();
private:
	string fuelType;
	int flowRate;
};

} /* namespace std */


#endif /* FUELPUMP_H_ */
