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
bool full;

Vehicle::Vehicle(int vehicleId, int fuelLeft, int sizeOfTank, string typeOfFuel) {
	if (sizeOfTank <= 0){
		sizeOfTank = 10;
	}

	// Just a quick check to see if someone is trying to initialize a car with either no fuel or too much fuel.
	// Makes sure that the tank isn't full when it goes to the station too, because there's no point in trying
	// to refuel when you don't need anymore fuel.
	if (fuelLeft <= 0 || fuelLeft >= sizeOfTank){
		fuelLeft = 0;
	}

	fuelRemaining = fuelLeft;
	tankSize = sizeOfTank;
	fuelType = typeOfFuel;
	full = false;
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
		full = true;
	}

	return full;
}


Vehicle::~Vehicle() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
