#include "WemosTunnel.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

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

    // run the if checks for incoming commands
    void CheckIncCommands();

protected:

private:
    struct sockaddr_in address;
    socklen_t addrlen;

	int m_port;					        // master_Port that the server runs on
	int m_socket;				        // Internal FD for master socket
	int phpsocket;				        // client socket since only php will connect phpsocket
    
    int bytesBuff;                      // Amount of incoming bytes, testing purposes
    char incBuffer[1024];               // stores incoming buffer from Wemos

};
