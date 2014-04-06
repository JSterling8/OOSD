/*
 * FuelPump.h
 *
 *  Created on: 18 Feb 2014
 *      Author: Jon
 */

#ifndef FUELPUMP_H_
#define FUELPUMP_H_

#include <string>

class FuelPump {
public:
	FuelPump(std::string&, int);

	virtual ~FuelPump();
private:
	std::string fuelType;
	int flowRate;
};


#endif /* FUELPUMP_H_ */
