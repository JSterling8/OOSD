/*
 * FuelStation.h
 *
 *  Created on: 6 Apr 2014
 *      Author: Jon
 */

#ifndef FUELSTATION_H_
#define FUELSTATION_H_

#import "FuelPump.h"

namespace std {

class FuelStation {
public:
	FuelStation();
	void vehicleArrivedAt();
	void generatePumps();
private:
	FuelPump pumps[];
};

} /* namespace std */

#endif /* FUELSTATION_H_ */
