/*
 * VehicleSpawner.h
 *
 *  Created on: 28 Mar 2014
 *      Author: Jon
 */

#ifndef VEHICLESPAWNER_H_
#define VEHICLESPAWNER_H_

#include "../Models/Vehicle.h"

// namespace std {

class VehicleSpawner {
public:
	VehicleSpawner();
	Vehicle Spawn(int);
};

// } /* namespace std */

#endif /* VEHICLESPAWNER_H_ */
