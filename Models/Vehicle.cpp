/*
 * Vehicle.cpp
 *
 *  Created on: 18 Feb 2014
 *      Author: Jon
 */

#include "Vehicle.h"

namespace std {

int fuelRemaining;
int tankSize;
string fuelType;

Vehicle::Vehicle(int fuelLeft, int sizeOfTank, string typeOfFuel) {
	if (sizeOfTank <= 0){
		sizeOfTank = 10;
	}

	// Just a quick check to see if someone is trying to initialize a car with either no fuel or too much fuel.
	if (fuelLeft <= 0 || fuelLeft > sizeOfTank){
		fuelLeft = sizeOfTank;
	}

	fuelRemaining = fuelLeft;
	tankSize = sizeOfTank;
	fuelType = typeOfFuel;
}

int maxFueCanAdd() {
	return (tankSize-fuelRemaining);
}

int getFuelRemaining() {
	return fuelRemaining;
}


int getTankSize(){
	return tankSize;
}

string getFuelType(){
	return fuelType;
}

void addFuel(int amountToAdd){
	// Only adds as much fuel as the tank can hold.
	if ((fuelRemaining + amountToAdd) <= tankSize){
		fuelRemaining += amountToAdd;
	}
	else {
		fuelRemaining = tankSize;
	}
}


Vehicle::~Vehicle() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
