#include "TCPListener.h"
#include "WemosTunnel.h"


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
    cout << "Waiting for incoming messages" << endl;
    if ((phpsocket = accept(m_socket, (struct sockaddr*)&address, &addrlen)) < 0) 
    {
        cerr << "Accepting failed";
        exit(EXIT_FAILURE);
    }

    // Read the incoming msg, store in incBuffer
    if (bytesBuff = read(phpsocket, incBuffer, sizeof(incBuffer)) <= 0) 
    {

    }
    // cool int to string convert to be able to use send().
    val = CheckIncCommands();
    tmp = sprintf(outBuffer,"%d",val);
    send(phpsocket, outBuffer, sizeof(outBuffer), 0);
    // after the outBuffer is sent back to PHP close the socket for the next command.
    close(phpsocket);
    // clear buffers so no old commands gets used.
    memset(outBuffer, 0, sizeof(outBuffer));
    memset(incBuffer, 0, sizeof(incBuffer)); 

    return 0;
}

int TCPListener::CheckIncCommands()
{
    // define classes with port number, ipadd, name. (name is only used for Str.find and cout)
    WemosTunnel Bed(8080,"192.168.178.57","Bed");
    WemosTunnel Chair(8080,"192.168.178.31","Chair");
    WemosTunnel Column(8080,"192.168.178.32","Column");
    WemosTunnel Door(8080,"192.168.178.33","Door");
    WemosTunnel Fridge(8080,"192.168.178.34","Fridge");
    WemosTunnel Tablelamp(8080,"192.168.178.35","TableLamp");
    WemosTunnel Wall(8080,"192.168.178.36","Wall");



    // First check for destination 
    // incBuffer[]convert to String for use in str.find
    string str(incBuffer);
    // size_t init for the if's
    size_t bed = str.find(Bed.name);
    size_t chair = str.find(Chair.name);
    size_t column = str.find(Column.name);
    size_t door = str.find(Door.name);
    size_t fridge = str.find(Fridge.name);
    size_t tablelamp = str.find(Tablelamp.name);
    size_t wall = str.find(Wall.name);

    // check the incoming command for destination.
    // if the command contains "bed" send command to right class.
    if (bed!=string::npos)
    {
        return(Bed.sendCommand(incBuffer));
    }
    if (chair!=string::npos)
    {
        return(Chair.sendCommand(incBuffer));
    }
    if (column!=string::npos)
    {
        return(Column.sendCommand(incBuffer));
    }
    if (door!=string::npos)
    {
        return(Door.sendCommand(incBuffer));
    }
    if (fridge!=string::npos)
    {
        return(Fridge.sendCommand(incBuffer));
    }
    if (tablelamp!=string::npos)
    {
        return(Tablelamp.sendCommand(incBuffer));
    }
    if (wall!=string::npos)
    {
        return(Wall.sendCommand(incBuffer));
    }
    // empty str
    str = "";
}