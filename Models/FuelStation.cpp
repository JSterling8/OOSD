/**
 * FuelStation.cpp
 *
 * The client portion of this class is adapted from code developed by Dr. Christopher Newman.
 *
 *  Created on: 6 Apr 2014
 *      @author: Jonathan Sterling
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

#define LENGTH 100					// The length of the boolean arrived array.

bool arrived[LENGTH];				// A log of all of the time units in which vehicles either arrive or do not arrive.
vector<FuelPump*> pumps;			// A vector of all of the pumps that this fuel station has.
deque<Vehicle*> vehicleDeque;		// A queue of vehicles waiting for a pump.
map<string, bool> fuelTypes;		// The types of fuels offered by this fuel station.
int numOfPumps;						// The total number of pumps this fuel station has.
int vehicleFrequency;				// The frequency in which vehicles come (used in Poisson distribution).

/**
 *
 * @param frequency The frequency in which vehicles come (used in Poisson distribution).
 */
FuelStation::FuelStation(int frequency) {
	// Initialize random seed:
	srand ( time(NULL) );

	vehicleFrequency = frequency;

	// We have to erase any pumps that exist from previous runs of the simulation.
	// This is because map entries cannot be overridden.  They must be erased then rewritten.
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

/**
 * Generates between 1 and 10 pumps of random fuel types.
 */
void FuelStation::generatePumps() {
	// We can have 1-10 pumps
	numOfPumps = rand() % 10 + 1;
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
			// If we don't already have this fuel type, make sure that we note that we now have it.
			if (!fuelTypes[fuelType]){
				fuelTypes.erase(fuelType);
				fuelTypes.insert(std::pair<string, int>(fuelType, true));
			}
		}
		else if (typeDecider == 2){
			fuelType = "Premium";
			// If we don't already have this fuel type, make sure that we note that we now have it.
			if (!fuelTypes[fuelType]){
				fuelTypes.erase(fuelType);
				fuelTypes.insert(std::pair<string, int>(fuelType, true));
			}
		}
		else if (typeDecider == 3){
			fuelType = "Regular";
			// If we don't already have this fuel type, make sure that we note that we now have it.
			if (!fuelTypes[fuelType]){
				fuelTypes.erase(fuelType);
				fuelTypes.insert(std::pair<string, int>(fuelType, true));
			}
		}
		else if (typeDecider == 4){
			fuelType = "Electric";
			// If we don't already have this fuel type, make sure that we note that we now have it.
			if (!fuelTypes[fuelType]){
				fuelTypes.erase(fuelType);
				fuelTypes.insert(std::pair<string, int>(fuelType, true));
			}
		}
		// Initializes the random fuel pump in our vector.
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
			// If there are vehicles in the queue.
			if (!vehicleDeque.empty()){
				// Take the first vehicle.
				Vehicle* temp = vehicleDeque.front();
				vehicleDeque.pop_front();

				// See if any pumps are available for the first vehicle.
				pumpIndex = getPump(temp->getFuelType());

				// If there is a pump free (i.e., if pumpIndex isn't -1)
				if (pumpIndex >= 0){
					// Add the vehicle at the front of the queue to the freed pump.
					pumps[pumpIndex]->setVehicleAtPump(temp);
					cout << "Added a queued vehicle to a freed pump." << endl;
				}
				else{
					// Put the vehicle at the back of the queue.
					// It goes to the back because if it's electric then it could hold everyone up for ages.
					vehicleDeque.push_back(temp);
					cout << "Still no pump free, so the vehicle continues to wait." << endl;
				}
			}
		}

		int dice = rand() % vehicleFrequency + 1;
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
			// The fuel type this vehicle needs to does not exist at this fuel station.
			else {
				cout << "Vehicle could not be served.  No pumps of type: " << v->getFuelType() << endl;
				delete v;
			}
		}
		// Else no vehicles arrived at this time interval.
		else {
			arrived[interval] = false;
		}

		// Loop through any pumps with vehicles and call the pump function.
		for (int j = 0; j < numOfPumps; ++j){
			if (pumps[j]->isInUse()){
				// If this iteration of pump() fills the vehicle, send a log of the filling to the main server.
				if(pumps[j]->pump()){
					sendToServer(pumps[j]->getVehicleAtPump());
				}
			}
		}
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

/**
 * This method sends data about the most recently filled vehicle to the central server.
 *
 * @param v The vehicle who's just had its tank filled.
 */
void FuelStation::sendToServer(Vehicle* v){
	WORD		wVersionRequested;
	WSADATA		wsaData;
	SOCKADDR_IN target; //Socket address information
	SOCKET		s;
	int			err;
	int			bytesSent;


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
		cout << endl << "Press enter to continue..." << endl;
		//------------------------------------------------------------
		closesocket( s );
		WSACleanup();

	_getche();  //was getche()
}

} /* namespace std */
