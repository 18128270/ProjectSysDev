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
    
    // err handling
    if (connect(c_socket, (struct sockaddr *)&wemos_addr, sizeof(wemos_addr)) < 0) 
    { 
        cerr << "<<< WEMOS Connection Failed to: " << name << endl;
        close(c_socket); 
        exit(EXIT_FAILURE);
    } 

    // Send max 100 chars. sizeof(command)didn't work.
    if ((sent = send(c_socket, command, 25, 0)) < 0)
    {
        // check for can't send bytes
        cerr << "<<< WEMOS bytes  "<< sent << "sent to : " << name << " failed." << endl;
        close(c_socket);
        exit(EXIT_FAILURE);
    };
    
    cout << "Server: Sending "<< sent << " bytes" << " the command is: " << command << " to " << name << endl;
    // Read the incoming msg, store in incBuffer
    if (bytesBuffer = read(c_socket, incBuffer, sizeof(incBuffer)) < 0)
    {
        // check for can't read bytes
        cerr << "<<< WEMOS bytes read failed "<< sent;
        close(c_socket);
        exit(EXIT_FAILURE);
    }

    // convert incBuffer[] to a string to use the str.find function
    string str = incBuffer;
    size_t ack = str.find("ACK");

    // if wemos repons is ACK return 1, which means the command has been executed by wemos, 
    // else returns either bool or analog values sent by wemos
    if (ack!=string::npos)
    {
        // prints WEMOS : command : reports : acknowledged
        cout <<name << ": " << command << " reports: " << str << endl;
        // clear incBuffer to reuse
        memset(incBuffer, 0, sizeof(incBuffer)); 
        // close the socket
        close(c_socket);
        return 1; 
        
    } else
    {
        // prints WEMOS : command : reports: return of that command
        cout << name << ": " << command << " reports: " << str << endl;
        // alphanumeric to integer converter method
        val = atoi(incBuffer);                              
        // clear incBuffer to reuse
        memset(incBuffer, 0, sizeof(incBuffer));                        
        // close the socket
        close(c_socket);                                                
        return(val);
    }
}

