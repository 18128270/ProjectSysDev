#include "WemosTunnel.h"
#include <vector>

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

	vector<WemosTunnel> list;

	WemosTunnel bed(8080,"192.168.4.10","bed");
    WemosTunnel chair(8081,"192.168.4.11","chair");
    WemosTunnel column(8082,"192.168.4.12","column");
    WemosTunnel door(8083,"192.168.4.13","door");
    WemosTunnel fridge(8084,"192.168.4.14","fridge");
    WemosTunnel tablelamp(8085,"192.168.4.15","tablelamp");
    WemosTunnel wall(8086,"192.168.4.16","wall");

	list.push_back(bed);
	list.push_back(chair);
	list.push_back(column);
	list.push_back(door);
	list.push_back(fridge);
	list.push_back(tablelamp);
	list.push_back(wall);

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
