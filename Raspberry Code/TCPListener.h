#include "Bed.h"
#include "Chair.h"
#include "Column.h"
#include "Door.h"
#include "Fridge.h"
#include "TableLamp.h"
#include "Wall.h"
#include <vector>

using namespace std;

#pragma once
class TCPListener
{
public:
	
	TCPListener(int port) :
		m_port(port) {
			bed = Bed(8080,"192.168.4.10","Bed");
			chair = Chair(8081,"192.168.4.11","Chair");
			column = Column(8082,"192.168.4.12","Column");
			door = Door(8083,"192.168.4.13","Door");
			fridge = Fridge(8084,"192.168.4.14","Fridge");
			tablelamp = TableLamp(8085,"192.168.4.15","TableLamp");
			wall = Wall(8086,"192.168.4.16","Wall");

			list.push_back(bed);
			list.push_back(chair);
			list.push_back(column);
			list.push_back(door);
			list.push_back(fridge);
			list.push_back(tablelamp);
			list.push_back(wall);
		}

	// initialize the listener
	int init();

	// run the listener
	int run();

    // checks for incoming commands and do shit, returns output of the command to php
    int CheckIncCommands();

	vector<WemosTunnel> list;

	Bed bed;
	Chair chair;
	Column column;
	Door door;
	Fridge fridge;
	TableLamp tablelamp;
	Wall wall;

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