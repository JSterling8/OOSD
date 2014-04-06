/*
 * AutoFuelPump.h
 *
 *  Created on: 18 Feb 2014
 *      Author: Jon
 */

#ifndef AUTOFUELPUMP_H_
#define AUTOFUELPUMP_H_

#include "FuelPump.h"
#include <string>


class AutoFuelPump : public FuelPump {
public:
	AutoFuelPump(std::string, int);
	~AutoFuelPump();

private:
	std::string steve;
};


#endif /* AUTOFUELPUMP_H_ */
