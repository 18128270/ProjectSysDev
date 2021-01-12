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
    cout << "Server: WemosTunnel to " << name <<" up" << endl;
    memset(incBuffer, 0, sizeof(incBuffer));
}

int WemosTunnel::sendCommand(char command[1024]) 
{
    // connect to WEMOS using address and port
    init();
    
    if (connect(c_socket, (struct sockaddr *)&wemos_addr, sizeof(wemos_addr)) < 0) 
    { 
        cerr << "<<< WEMOS Connection Failed";
        close(c_socket); 
        exit(EXIT_FAILURE);
    } 
    // Sent max 100 chars. sizeof(command)didn't work.
    if ((sent = send(c_socket, command, 100, 0)) < 0)
    {
        // check for can't read bytes
        cerr << "<<< WEMOS bytes sent failed "<< sent;
        close(c_socket);
        exit(EXIT_FAILURE);
    };
    
    cout << "Server: Sending "<< sent << " (amount of bytes) " << " the command is " << command << " to " << name << endl;
    // Read the incoming msg, store in incBuffer
    if (bytesBuffer = read(c_socket, incBuffer, sizeof(incBuffer)) < 0)
    {
        // check for can't read bytes
        cerr << "<<< WEMOS bytes read failed "<< sent;
        close(c_socket);
        exit(EXIT_FAILURE);
    }

    // confert incBuffer[] to a string to use the str.find function
    string str = incBuffer;
    size_t ack = str.find("0");
//
    //TODO
    //if (ack!=string::npos)
   // {
   //     // prints WEMOS : acknowledged
   //     cout <<name << ":" << incBuffer << endl;
   //     memset(incBuffer, 0, sizeof(incBuffer)); 
   //     close(c_socket);
   //     return 0; 
   //     
   // } else
   // {
        // prints WEMOS : command : return of that command
        cout << name <<": "<< command << " reports: " << str << endl;
        // alphanumeric to integer converter method
        val = atoi(incBuffer);                                          // alphanumeric to integer.
        // clear incBuffer to reuse
        memset(incBuffer, 0, sizeof(incBuffer));                        
        // close the socket after everything is done
        close(c_socket);                                                
        return(val);
   // }
}

