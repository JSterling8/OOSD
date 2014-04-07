/**
 * Vehicle.cpp
 *
 *  Created on: 18 Feb 2014
 *      @author: Jonathan Sterling
 */

#include "Vehicle.h"
#include "LoyaltyCard.h"
#include<stdio.h>

namespace std {

int fuelRemaining;				// The amount of fuel left in this vehicle's tank.
int tankSize;					// The maximum amount of fuel that this vehicle can hold.
string fuelType;				// The type of fuel this vehicle requires.
int amountFilled;				// The total amount added to the tank at the last fillup.
bool full;						// Whether or not the vehicle's fuel tank is full.
LoyaltyCard* loyaltyCard;		// The loyalty card attributed to this vehicle.

/**
 *
 * @param id The id of the loyalty card attached to the vehicle.
 * @param fuelLeft The amount of fuel remaining in the vehicle's fuel tank.
 * @param sizeOfTank The maximum capacity of the fuel tank.
 * @param typeOfFuel The Type of fuel that this vehicle requires.
 */
Vehicle::Vehicle(int id, int fuelLeft, int sizeOfTank, string typeOfFuel) {
	// The size of the fuel tank must be positive.
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
	amountFilled = sizeOfTank-fuelLeft;
	tankSize = sizeOfTank;
	fuelType = typeOfFuel;
	loyaltyCard = new LoyaltyCard(id);
	full = false;
}

/**
 *
 * @return fuelRemaining The amount of fuel in the fuel tank.
 */
int Vehicle::getFuelRemaining() {
	return fuelRemaining;
}

/**
 *
 * @return tankSize The maximum amount of fuel this vehicle's tank can hold.
 */
int Vehicle::getTankSize(){
	return tankSize;
}

/**
 *
 * @return The type of fuel that this vehicle requires.
 */
string Vehicle::getFuelType(){
	return fuelType;
}

/**
 *
 * @param amountToAdd How much fuel to add to the vehicle.
 * @return Whether or not the vehicle's tank is  full.
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

/**
 * @return A character representation of this vehicle for sending to the main office.
 */
char* Vehicle::toCharArray(){
	int timeToFill = 0;

	if (fuelType == "Diesel"){
		timeToFill = amountFilled*5;
	}
	else if (fuelType == "Regular" || fuelType == "Premium"){
		timeToFill = amountFilled;
	}
	else if (fuelType == "Electric"){
		timeToFill = amountFilled*12;
	}

	static char numstr[50];
	sprintf(numstr, "ID: %d Fuel Added: %d Time to Fill: %d", loyaltyCard->getId(), amountFilled, timeToFill);

	return numstr;
}


Vehicle::~Vehicle() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
