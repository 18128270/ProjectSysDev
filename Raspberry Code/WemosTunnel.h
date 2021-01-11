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
class WemosTunnel
{
public:
	
	WemosTunnel(int DestPort, const char* DestAdd, string name) :
		DestPort(DestPort), DestAdd(DestAdd), name(name)  { }

	// initialize the socket to Wemos
	int init();

	// send the command to Wemos
	int sendCommand(char command[5]);
    
protected:

private:
    string name;                    // String name contains the name of the hardware it belongs to.
    int DestPort;                   // DestPort is the destination port of the socket server.
    const char* DestAdd;            // DestAdd is the destination ipaddress of the socket server.

    char command[5];                // Command is the char that is being sent to the WEMOS. Wemos knows what to do with this command. See conversion table for list of commands.

    int c_socket;                   // in use for outgoing client socket.
    struct sockaddr_in wemos_addr;  // File descriptor for binding port and IP to c_socket

    
    int bytesBuffer;
    char incBuffer[1024];

};
