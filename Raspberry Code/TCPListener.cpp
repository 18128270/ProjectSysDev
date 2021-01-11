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
        memset(incBuffer, 0, sizeof(incBuffer)); //clear buffer to be sure
        if (bytesBuff = read(phpsocket, incBuffer, sizeof(incBuffer)) <= 0) 
        {
            cout << "TCPListener::run :: test" << endl;
        }

        cout << "Here is the message: " << incBuffer << endl;
        send(phpsocket, incBuffer, sizeof(incBuffer), 0);
        close(phpsocket);
        return 0;
}

void TCPListener::CheckIncCommands()
{
    WemosTunnel Bed(8080,"192.168.178.57","Bed");
    WemosTunnel Chair(8080,"192.168.178.31","Chair");
    WemosTunnel Column(8080,"192.168.178.32","Column");
    WemosTunnel Door(8080,"192.168.178.33","Door");
    WemosTunnel Fridge(8080,"192.168.178.34","Fridge");
    WemosTunnel TabelLamp(8080,"192.168.178.35","TabelLamp");
    WemosTunnel Wall(8080,"192.168.178.36","Wall");

    // First check for destination 
    if (!strcmp(incBuffer, "bed on")) 
    {   
    Bed.sendCommand("0");
    }
    if (!strcmp(incBuffer, "bed off")) 
    {   
    Bed.sendCommand("1");
    }
    memset(incBuffer, 0, sizeof(incBuffer)); //clear buffer to be sure
}
   // if (!strcmp(incBuffer, "Chair"))
   // {
   //     send(phpsocket, incBuffer, sizeof(incBuffer), 0);
//
   // }scp leds nig2000@192.168.178.21:/home/nig2000/OOPR/
   // if (!strcmp(incBuffer, "Column"))
   // {
   //     send(phpsocket, incBuffer, sizeof(incBuffer), 0);
   // }
   // if (!strcmp(incBuffer, "Door"))
   // {
   //     send(phpsocket, incBuffer, sizeof(incBuffer), 0);
//
   // }
   // if (!strcmp(incBuffer, "Fridge"))
   // {
   //     send(phpsocket, incBuffer, sizeof(incBuffer), 0);
   // }
   // if (!strcmp(incBuffer, "TableLamp"))
   // {
   //     send(phpsocket, incBuffer, sizeof(incBuffer), 0);
   // }
   // if (!strcmp(incBuffer, "Wall"))
   // {
   //     send(phpsocket, incBuffer, sizeof(incBuffer), 0);
   // }
