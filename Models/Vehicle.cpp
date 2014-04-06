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

int Vehicle::maxFuelCanAdd() {
	return (tankSize-fuelRemaining);
}

int Vehicle::getFuelRemaining() {
	return fuelRemaining;
}


int Vehicle::getTankSize(){
	return tankSize;
}

string Vehicle::getFuelType(){
	return fuelType;
}

/**
 *
 * @param amountToAdd How much fuel to add to the vehicle.
 * @return Whether or not it's full.
 */
bool Vehicle::addFuel(int amountToAdd){
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
