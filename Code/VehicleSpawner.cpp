/*
 * VehicleSpawner.cpp
 *
 *  Created on: 28 Mar 2014
 *      Author: Jon
 */

#include "VehicleSpawner.h"
#include "../Models/Vehicle.h"
#include <iostream>
#include <string>
#include<conio.h>
#include<stdlib.h>
#include<time.h>


VehicleSpawner::VehicleSpawner() {	}

Vehicle VehicleSpawner::Spawn(int numToSpawn){
    srand(time(NULL));

    int x = 0;

    Vehicle vehicleArray[] = new Vehicle();

    for (int i = 0; i < numToSpawn; i++){
    	x = rand() % 50+1;
    }

	return NULL;
}

 /* namespace std */
