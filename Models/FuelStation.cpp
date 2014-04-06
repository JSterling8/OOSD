/*
 * FuelStation.cpp
 *
 *  Created on: 6 Apr 2014
 *      Author: Jon
 */

#include "FuelStation.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

namespace std {

#define LENGTH 100

bool arrived[LENGTH];

FuelStation::FuelStation() {
	// TODO Auto-generated constructor stub

}

void generatePumps() {

}

void vehicleArrivedAt() {

	// Initialize random seed:
	srand ( time(NULL) );

	 double bar = 10.0 * exp(-0.1);
	 for( int interval = 0; interval < LENGTH; ++interval ) {
		 int dice = rand() % 10 + 1;
		 //handle customers arriving
		 if ( dice > bar ) {
			 arrived[interval] = true;
			 cout << "Vehicle arrived at time: " << interval << endl;
			 // Is there a pump free?
			 // Yes - assign sales person
			 // No - add customer to queue
		 }
		 else {
			 arrived[interval] = false;
		 }
		 //Handle sales people and existing customers
		 //Is there a customer waiting
		 //Is a sales person available?

		 //If the transaction is complete log the data.
	 }
}

} /* namespace std */
