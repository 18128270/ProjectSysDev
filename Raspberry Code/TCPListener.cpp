#include "TCPListener.h"
#include "WemosTunnel.h"
#include <vector>

int TCPListener::init() 
{
    // initialize Server Socket(listener)
    if ((m_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    {
        cerr << ("socket failed");
        exit(EXIT_FAILURE);
    }

    cout << "Socket Connection is up and about" << endl;

    // bind Port&IP to socket
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;   //INADDR_ANY;inet_addr("localhost");
    address.sin_port = htons(m_port);

    if (bind(m_socket, (sockaddr*)&address, sizeof(address)) < 0) 
    {
        cerr << ("bind failed");
        exit(EXIT_FAILURE);
    }

    // Start Listener    
    if (listen(m_socket, 3) < 0) 
    {
        cerr << ("not listening");
        exit(EXIT_FAILURE);
    }

    return 0;
}

int TCPListener::run() 
{
    // Accept incoming (from PHP socket)
    addrlen = sizeof(struct sockaddr_in);
    cout << " " << endl;
    cout << "=== Waiting for incoming messages ===" << endl;
    if ((phpsocket = accept(m_socket, (struct sockaddr*)&address, &addrlen)) < 0) 
    {
        cerr << "Accepting failed";
        exit(EXIT_FAILURE);
    }

    // Read the incoming msg, store in incBuffer
    if (bytesBuff = read(phpsocket, incBuffer, sizeof(incBuffer)) <= 0) 
    {

    }
    memset(outBuffer, 0, sizeof(outBuffer));

    // cool int to string convert to be able to use send().
    val = CheckIncCommands();
    sprintf(outBuffer,"%d",val);

    string str(incBuffer);
    if (str.find("Column check co2")!=string::npos && val == 1) {
        door.sendCommand("Door door open");
    }

    send(phpsocket, outBuffer, sizeof(outBuffer), 0);
    // after the outBuffer is sent back to PHP close the socket for the next command.
    close(phpsocket);

    memset(outBuffer, 0, sizeof(outBuffer));
    memset(incBuffer, 0, sizeof(incBuffer)); 

    return 0;
}

int TCPListener::CheckIncCommands()
{
    string str(incBuffer);

    for (int i = 0; i < list.size()-1; i++) {
        if(str.find(list.at(i).name) != string::npos) {
            str = "";
            return (list.at(i).sendCommand(incBuffer));
        }
    }

    str = "";
}