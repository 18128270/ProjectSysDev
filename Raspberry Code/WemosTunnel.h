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
class WemosTunnel {
public:
	WemosTunnel(int DestPort, const char* DestAdd, string name) :
		DestPort(DestPort), DestAdd(DestAdd), name(name) {}

	// initialize the socket to Wemos
	int init();

	// send the command to Wemos
	int sendCommand(char command[1024]);

    string name;                       // string name contains the name of the hardware it belongs to.
    
protected:

private:
    // string name;                    // string name contains the name of the hardware it belongs to.
    int DestPort;                      // destPort is the destination port of the socket server.
    const char* DestAdd;               // destAdd is the destination ipaddress of the socket server.
    char command[1024];                // command is the char that is being sent to the WEMOS. Wemos knows what to do with this command. See conversion table for list of commands.

    int c_socket;                       // in use for outgoing client socket.
    struct sockaddr_in wemos_addr;      // file descriptor for binding port and IP to c_socket

    int bytesBuffer;                    // checker to see if the buffer is empty
    int val;                            // tmp val for converts
    char incBuffer[1024];               // char array for incBuffer from WEMOS
    int sent;                           // checker to see if all bytes are sent to WEMOS

};