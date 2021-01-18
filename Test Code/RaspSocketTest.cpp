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


#define PORT 8080

#define DestAdd "192.168.178.57"
#define DestPort 8181

using namespace std;

int main(){
    // initialize Server Socket(listener)
    int listener,phpSocket, bytesIn;
    socklen_t addrlen;
    struct sockaddr_in address;
    char incBuffer[1024] = {0};
    if ((listener = socket(AF_INET,SOCK_STREAM,0)) == 0){
        cerr << ("socket failed");
        exit(EXIT_FAILURE);
    }
    
    cout << "Socket Connection is up and about" << endl;

    // bind Port&IP to socket
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;//INADDR_ANY;inet_addr("localhost");
    address.sin_port = htons(PORT);

    if (bind(listener,(struct sockaddr *)&address,sizeof(address)) < 0){
        cerr << ("bind failed");
        exit(EXIT_FAILURE);
    }

    // Start Listener    
    if (listen(listener, 3) < 0){
        cerr << ("not listening");
        exit(EXIT_FAILURE);
    }

while(1){

    // Accept incoming (from PHP socket)
    char incBuffer[1024] = {0};
    cout << "<<<< clearing buffer >>>>" << endl;
    addrlen = sizeof(struct sockaddr_in);
    cout << "Waiting for incoming messages" << endl;

    if ((phpSocket = accept(listener,(struct sockaddr *)&address,&addrlen)) < 0){
        cerr << "Accepting failed";
        exit(EXIT_FAILURE);
    }
       
    if (bytesIn = read(phpSocket, incBuffer, 1024) <= 0) {
        cout << "test" << endl;
    }

    cout << "Here is the message: " << incBuffer << endl;
    send(phpSocket, incBuffer, sizeof(incBuffer), 0);
    
    // Do something based on incoming message
    if(!strcmp(incBuffer,incBuffer)){

        // initialize new outgoing Socket to WEMOS 
        int WemosSock = 0, bytesOut; 
        struct sockaddr_in wemos_addr;  
        char outBuffer[1024] = {0}; 
        if ((WemosSock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
        { 
            cerr << "<<< WEMOS Socket creation error"; 
            exit(EXIT_FAILURE); 
        } 
        // Bind DestADD & PORT to new outgoing WEMOS Socket
        wemos_addr.sin_family = AF_INET; 
        wemos_addr.sin_port = htons(DestPort); 
        
        if(inet_pton(AF_INET, DestAdd, &wemos_addr.sin_addr) <= 0)  
        { 
            cerr << "<<< WEMOS Invalid address/ Address not supported"; 
            close(WemosSock);
            exit(EXIT_FAILURE); 
        }

        // Connect to outgoing WEMOS Socket
        if (connect(WemosSock, (struct sockaddr *)&wemos_addr, sizeof(wemos_addr)) < 0) 
        { 
            cerr << "<<< WEMOS Connection Failed";
            close(WemosSock); 
            exit(EXIT_FAILURE);
        } 

        // Send something to WEMOS
        send(WemosSock, outBuffer, sizeof(outBuffer), 0); 
        cout << "Server: Sending message to WEMOS" << endl;
        bytesOut = read(WemosSock, outBuffer, 1024); 
        cout << "here is the buffer: " << outBuffer << endl;
        cout <<"<<< Wemos close connection" << endl;
        
        //Clean close outgoing socket but keep incoming open
        close(WemosSock);
    }
}
}
