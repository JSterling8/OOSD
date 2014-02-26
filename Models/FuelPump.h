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
	FuelPump(std::string);
	std::string toString();
	virtual ~FuelPump();
private:
	std::string bob;
};


#endif /* FUELPUMP_H_ */
