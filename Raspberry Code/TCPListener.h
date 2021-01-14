#include "WemosTunnel.h"


using namespace std;

#pragma once
class TCPListener
{
public:
	
	TCPListener(int port) :
		m_port(port) { }

	// initialize the listener
	int init();

	// run the listener
	int run();

    // checks for incoming commands and do shit, returns output of the command to php
    int CheckIncCommands();

	

protected:

private:
    struct sockaddr_in address;
    socklen_t addrlen;

	int m_port;					        // master_Port that the server runs on
	int m_socket;				        // Internal FD for master socket
	int phpsocket;				        // client socket since only php will connect phpsocket
    
    int bytesBuff;                      // Amount of incoming bytes, testing purposes
    char incBuffer[1024];               // stores incoming buffer from Wemos
	char outBuffer[100];
	int val;							// return value of the checkfunction
};
