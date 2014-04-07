/*
 * FuelStation.h
 *
 *  Created on: 6 Apr 2014
 *      Author: Jon
 */

#ifndef FUELSTATION_H_
#define FUELSTATION_H_

#include "FuelPump.h"
#include "Vehicle.h"

namespace std {

class FuelStation {
public:
	FuelStation(int);
	void vehicleArrivedAt();
	void generatePumps();
	Vehicle* generateRandomVehicle();
	int getPump(string);
	void sendToServer(Vehicle*);
};

} /* namespace std */

#endif /* FUELSTATION_H_ */
