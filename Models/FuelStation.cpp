/*
 * FuelStation.cpp
 *
 *  Created on: 6 Apr 2014
 *      Author: Jon
 */

#include "FuelStation.h"
#include "Vehicle.h"

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <iostream>
#include "winsock2.h"
#include "conio.h"
#include <cstdio>

#define SERVER_PORT 12345
#define BUF_SIZE 4096 // block transfer size
#define QUEUE_SIZE 10
#define IPAddress "127.0.0.1" // Local to the system - Loop back address

namespace std {

#define LENGTH 100

bool arrived[LENGTH];
vector<FuelPump*> pumps;
deque<Vehicle*> vehicleDeque;
map<string, bool> fuelTypes;
int numOfPumps;

FuelStation::FuelStation() {
	// Initialize random seed:
	srand ( time(NULL) );

	// We have to erase any pumps that exist from previous runs of the simulation.
	fuelTypes.erase("Diesel");
	fuelTypes.erase("Premium");
	fuelTypes.erase("Regular");
	fuelTypes.erase("Electric");

	// Set all of our fuel types to be false, because no pumps have been built yet.
	fuelTypes.insert(std::pair<string, int>("Diesel", false));
	fuelTypes.insert(std::pair<string, int>("Premium", false));
	fuelTypes.insert(std::pair<string, int>("Regular", false));
	fuelTypes.insert(std::pair<string, int>("Electric", false));

	// Fill the station with pumps.
	generatePumps();
}

void FuelStation::generatePumps() {
	numOfPumps = rand() % 10 + 1;
	// We can have 1-10 pumps
	pumps.reserve(numOfPumps);

	// This will be used to determing the pump's fuel type.
	int typeDecider = 0;

	string fuelType;

	// Loop through our pumps vector and randomly put in different types of pumps
	for (int i = 0; i < numOfPumps; i++){
		// This is an int from 1-4 that will be used to determing the pump's fuel type.
		typeDecider = rand() % 4 + 1;
		if (typeDecider == 1){
			fuelType = "Diesel";
			if (!fuelTypes[fuelType]){
				fuelTypes.erase(fuelType);
				fuelTypes.insert(std::pair<string, int>(fuelType, true));
			}
		}
		else if (typeDecider == 2){
			fuelType = "Premium";
			if (!fuelTypes[fuelType]){
				fuelTypes.erase(fuelType);
				fuelTypes.insert(std::pair<string, int>(fuelType, true));
			}
		}
		else if (typeDecider == 3){
			fuelType = "Regular";
			if (!fuelTypes[fuelType]){
				fuelTypes.erase(fuelType);
				fuelTypes.insert(std::pair<string, int>(fuelType, true));
			}
		}
		else if (typeDecider == 4){
			fuelType = "Electric";
			if (!fuelTypes[fuelType]){
				fuelTypes.erase(fuelType);
				fuelTypes.insert(std::pair<string, int>(fuelType, true));
			}
		}
		pumps[i] = new FuelPump(fuelType);
	}
}

/**
 * Uses Poisson distribution to see if a vehicle has arrived at any second.
 */
void FuelStation::vehicleArrivedAt() {
	double bar = 10.0 * exp(-0.1);
	int pumpIndex = -1;
	for( int interval = 0; interval < LENGTH; ++interval ) {
		// Loop through any waiting vehicles before adding new ones.
		for (unsigned int i = 0; i < vehicleDeque.size(); ++i){
			if (!vehicleDeque.empty()){
				Vehicle* temp = vehicleDeque.front();
				vehicleDeque.pop_front();

				pumpIndex = getPump(temp->getFuelType());

				// If there is a pump free (i.e., if pumpIndex isn't -1)
				if (pumpIndex >= 0){
					pumps[pumpIndex]->setVehicleAtPump(temp);
					cout << "Added a queued vehicle to a freed pump." << endl;
				}
				else{
					vehicleDeque.push_front(temp);
					cout << "Still no pump free, so the vehicle continues to wait." << endl;
				}
			}
		}

		int dice = rand() % 10 + 1;
		// Handle vehicles arriving
		if ( dice > bar ) {
			arrived[interval] = true;
			Vehicle* v = generateRandomVehicle();
			cout << "Vehicle arrived at time: " << interval << endl;
			// Does this station have the fuel this vehicle needs?
			if (fuelTypes[v->getFuelType()]){
				// Is there a pump of the right type free?
				pumpIndex = getPump(v->getFuelType());
				// If there is a pump free (i.e., if pumpIndex isn't -1)
				if (pumpIndex >= 0){
					pumps[pumpIndex]->setVehicleAtPump(v);
				}
				// If no pump is free, add the Vehicle to the end of the queue.
				else{
					vehicleDeque.push_back(v);
					cout << "There are no pumps available.  Vehicle added to deque. " << endl;
				}
			}
			else {
				cout << "Vehicle could not be served.  No pumps of type: " << v->getFuelType() << endl;
				delete v;
			}
		}
		else {
			arrived[interval] = false;
		}

		// Loop through any pumps with vehicles and call the pump function.
		for (int j = 0; j < numOfPumps; ++j){
			if (pumps[j]->isInUse()){
				if(pumps[j]->pump()){
					sendToServer(pumps[j]->getVehicleAtPump());
				}
			}
		}

		// TODO If the pumping is complete log the data.
	}
}

/**
 * Randomly generates a vehicle.
 * We need a random amount of fuel currently in the tank, a tank size,
 * and a fuel type.
 *
 * @returns A random vehicle.
 */
Vehicle* FuelStation::generateRandomVehicle() {
	// Tank size is between 1 and 30.
	int tankSize = rand() % 30 + 1;

	// Fuel remaining is between 0 and tankSize-1.
	int fuelRemaining = tankSize - (rand() % tankSize + 1);

	// The vehicle's ID.
	int vehicleId = rand() % 100 + 1;

	string fuelType;

	// Randomly assigns a fuel type.
	int typeDecider = rand() % 4 + 1;

	if (typeDecider == 1){
		fuelType = "Diesel";
	}
	else if (typeDecider == 2){
		fuelType = "Premium";
	}
	else if (typeDecider == 3){
		fuelType = "Regular";
	}
	else if (typeDecider == 4){
		fuelType = "Electric";
	}

	// Returns a Vehicle with the three random variables calculated above.
	return new Vehicle(vehicleId, fuelRemaining, tankSize, fuelType);
}

/**
 * @param fuelType the type of fuel needed.
 * @returns The index of a free pump with the right fuel type.  If none exists, it returns -1.
 */
int FuelStation::getPump(string fuelType){
	// Loop through the pumps.
	for(int i = 0; i < numOfPumps; ++i){
		// If a pump of the correct fuel type is available, return its index in the FuelPump vector.
		if (pumps[i]->getFuelType() == fuelType && !pumps[i]->isInUse()){
			return i;
		}
	}

	return -1;
}

void FuelStation::sendToServer(Vehicle* v){
	WORD		wVersionRequested;
	WSADATA		wsaData;
	SOCKADDR_IN target; //Socket address information
	SOCKET		s;
	int			err;
	int			bytesSent;
	// char		buf[50] = v->toCharArray();


	// while(1) {
		//--- INITIALIZATION -----------------------------------
		wVersionRequested = MAKEWORD( 1, 1 );
		err = WSAStartup( wVersionRequested, &wsaData );

		if ( err != 0 ) {
			printf("WSAStartup error %ld", static_cast<long>( WSAGetLastError() ) );
			WSACleanup();
			// return false;
		}
		//------------------------------------------------------

		//---- Build address structure to bind to socket.--------
		target.sin_family = AF_INET; // address family Internet
		target.sin_port = htons (SERVER_PORT); //Port to connect on
		target.sin_addr.s_addr = inet_addr (IPAddress); //Target IP
		//--------------------------------------------------------


		// ---- create SOCKET--------------------------------------
		s = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP); //Create socket
		if (s == INVALID_SOCKET)
		{
			printf("socket error %ld" , static_cast<long>( WSAGetLastError() ) );
			WSACleanup();
			// return false; //Couldn't create the socket
		}
		//---------------------------------------------------------


		//---- try CONNECT -----------------------------------------
		if (connect(s, (SOCKADDR *)&target, sizeof(target)) == SOCKET_ERROR)
		{
			printf("connect error %ld", static_cast<long>( WSAGetLastError() ) );
			WSACleanup();
			// return false; //Couldn't connect
		}
		//-----------------------------------------------------------

		//---- SEND bytes -------------------------------------------
		char* toSend = v->toCharArray();

		// scanf( "%s", toSend );  //was gets(buf)
		bytesSent = send( s, toSend, 50, 0 );
		printf( "Bytes Sent: %ld \n", static_cast<long>( bytesSent ) );
		//------------------------------------------------------------
		closesocket( s );
		WSACleanup();
	// }

	_getche();  //was getche()
	// return 0;
}

} /* namespace std */
