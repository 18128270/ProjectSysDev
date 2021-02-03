#include "TCPListener.h"
#include "WemosTunnel.h"

int TCPListener::init() {
    // initialize server socket(listener)
    if ((m_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        cerr << ("socket failed");
        exit(EXIT_FAILURE);
    }

    cout << "Socket Connection is up and about" << endl;

    // bind port & IP to socket
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;   //INADDR_ANY;inet_addr("localhost");
    address.sin_port = htons(m_port);

    if (bind(m_socket, (sockaddr*)&address, sizeof(address)) < 0) {
        cerr << ("bind failed");
        exit(EXIT_FAILURE);
    }

    // start listener    
    if (listen(m_socket, 3) < 0) {
        cerr << ("not listening");
        exit(EXIT_FAILURE);
    }

    return 0;
}

int TCPListener::run() {
    // accept incoming (from PHP socket)
    addrlen = sizeof(struct sockaddr_in);
    cout << "" << endl;
    cout << "=== Waiting for incoming messages ===" << endl;
    if ((phpsocket = accept(m_socket, (struct sockaddr*)&address, &addrlen)) < 0) {
        cerr << "Accepting failed";
        exit(EXIT_FAILURE);
    }

    // read the incoming msg, store in incBuffer
    if (bytesBuff = read(phpsocket, incBuffer, sizeof(incBuffer)) <= 0) {}

    memset(outBuffer, 0, sizeof(outBuffer));

    // cool int to string convert to be able to use send().
    val = CheckIncCommands();
    sprintf(outBuffer,"%d",val);

    string str(incBuffer);
    if (str.find("Bed check force")!=string::npos && val == 1) {
        cout << "test" << endl;
        WemosTunnel Column(8082,"192.168.4.12","Column");
        Column.sendCommand("buzzer on");
    }

    send(phpsocket, outBuffer, sizeof(outBuffer), 0);
    // after the outBuffer is sent back to PHP close the socket for the next command.
    close(phpsocket);
    // clear buffers so no old commands gets used.
    memset(outBuffer, 0, sizeof(outBuffer));
    memset(incBuffer, 0, sizeof(incBuffer));

    return 0;
}

int TCPListener::CheckIncCommands() {
    // define classes with port number, ipadd, name. (name is only used for Str.find and cout)
    WemosTunnel Bed(8080,"192.168.4.10","Bed");
    WemosTunnel Chair(8081,"192.168.4.11","Chair");
    WemosTunnel Column(8082,"192.168.4.12","Column");
    WemosTunnel Door(8083,"192.168.4.13","Door");
    WemosTunnel Fridge(8084,"192.168.4.14","Fridge");
    WemosTunnel Tablelamp(8085,"192.168.4.15","TableLamp");
    WemosTunnel Wall(8086,"192.168.4.16","Wall");

    // first check for destination
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
    if (bed!=string::npos) {
        str = "";
        return(Bed.sendCommand(incBuffer));
    }

    if (chair!=string::npos) {
        str = "";
        return(Chair.sendCommand(incBuffer));
    }

    if (column!=string::npos) {
        str = "";
        return(Column.sendCommand(incBuffer));
    }

    if (door!=string::npos) {
        str = "";
        return(Door.sendCommand(incBuffer));
    }

    if (fridge!=string::npos) {
        str = "";
        return(Fridge.sendCommand(incBuffer));
    }

    if (tablelamp!=string::npos) {
        str = "";
        return(Tablelamp.sendCommand(incBuffer));
    }

    if (wall!=string::npos) {
        str = "";
        return(Wall.sendCommand(incBuffer));
    }

    str = "";
}