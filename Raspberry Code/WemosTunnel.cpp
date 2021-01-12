#include "WemosTunnel.h"

int WemosTunnel::init() 
{

    // initialize new outgoing Socket to WEMOS
    if ((c_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        cerr << "<<< WEMOS Socket creation error";
        exit(EXIT_FAILURE);
    }

    // Bind DestADD & PORT to new outgoing WEMOS Socket
    wemos_addr.sin_family = AF_INET;
    wemos_addr.sin_port = htons(DestPort);
    if (inet_pton(AF_INET, DestAdd, &wemos_addr.sin_addr) <= 0) 
    {
        cerr << "<<< WEMOS Invalid address or Port is not correct";
        close(c_socket);
            exit(EXIT_FAILURE);
    }
    cout << "WemosTunnel to " << name <<" up" << endl;
    memset(incBuffer, 0, sizeof(incBuffer));
}

int WemosTunnel::sendCommand(char command[5]) 
{
    init();

    if (connect(c_socket, (struct sockaddr *)&wemos_addr, sizeof(wemos_addr)) < 0) 
    { 
        cerr << "<<< WEMOS Connection Failed";
        close(c_socket); 
        exit(EXIT_FAILURE);
    } 

    send(c_socket, command, sizeof(command), 0);
    cout << "Server: Sending "<< command << " to " << name << endl;
    
    // Read the incoming msg, store in incBuffer
    if (bytesBuffer = read(c_socket, incBuffer, sizeof(incBuffer)) < 0)
    {
        cout << "test" << endl;
    }

    cout << name << ":" << incBuffer << endl;
    memset(incBuffer, 0, sizeof(incBuffer));
    close(c_socket);

}