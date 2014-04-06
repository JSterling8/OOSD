//============================================================================
// Name        : OOSD_Assignment.cpp
// Author      : Jonathan Sterling
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================



#include <iostream>
#include "winsock2.h"
#include "conio.h"
#include <cstdio>

#define SERVER_PORT 12345
#define BUF_SIZE 4096 // block transfer size
#define QUEUE_SIZE 10
#define IPAddress "127.0.0.1" // Local to the system - Loop back address

using namespace std;




int collectResponse( SOCKET & );

int main(int argc, char * argv[]) {

	std::cout << "Is the server running?" << std::endl; //
	std::cout << "Requires a running server to make a connection?" << std::endl; //
	std::cout << "Enter a few characters maximum 9" << std::endl;
	WORD		wVersionRequested;
	WSADATA		wsaData;
	SOCKADDR_IN target; //Socket address information
	SOCKET		s;
	int			err;
	int			bytesSent;
	char		buf[10] = "hi hello";


	while(1) {
		//--- INITIALIZATION -----------------------------------
		wVersionRequested = MAKEWORD( 1, 1 );
		err = WSAStartup( wVersionRequested, &wsaData );

		if ( err != 0 ) {
			printf("WSAStartup error %ld", static_cast<long>( WSAGetLastError() ) );
			WSACleanup();
			return false;
		}
		//------------------------------------------------------

		//---- Build address structure to bind to socket.--------
		target.sin_family = AF_INET; // address family Internet

		//TODO change back to SERVER_PORT instead of magic number 12345 and same for IPAddress and "127.0.0.1"
		target.sin_port = htons (SERVER_PORT); //Port to connect on
		target.sin_addr.s_addr = inet_addr (IPAddress); //Target IP
		//--------------------------------------------------------


		// ---- create SOCKET--------------------------------------
		s = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP); //Create socket
		if (s == INVALID_SOCKET)
		{
			printf("socket error %ld" , static_cast<long>( WSAGetLastError() ) );
			WSACleanup();
			return false; //Couldn't create the socket
		}
		//---------------------------------------------------------


		//---- try CONNECT -----------------------------------------
		if (connect(s, (SOCKADDR *)&target, sizeof(target)) == SOCKET_ERROR)
		{
			printf("connect error %ld", static_cast<long>( WSAGetLastError() ) );
			WSACleanup();
			return false; //Couldn't connect
		}
		//-----------------------------------------------------------

		//---- SEND bytes -------------------------------------------

		scanf( "%s", buf );  //was gets(buf)
		bytesSent = send( s, buf, 10, 0 );
		printf( "Bytes Sent: %ld \n", static_cast<long>( bytesSent ) );
		collectResponse( s );
		//------------------------------------------------------------
		closesocket( s );
		WSACleanup();
	}

	_getche();  //was getche()
	return 0;
}

int collectResponse(SOCKET & socket ) {
	char ACK_Buffer[12] = { };
	int bytesRecv = recv( socket, ACK_Buffer, 12, 0 );
	printf("BytesRecv: %d : %s\n ", bytesRecv,ACK_Buffer);
	return
			bytesRecv;
}


