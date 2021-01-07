#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
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
    
    int server_fd,new_socket, valread;
    socklen_t addrlen;
    struct sockaddr_in address;
    char buffer[1024] = {0};
    if ((server_fd = socket(AF_INET,SOCK_STREAM,0)) == 0){
        cout<<("socket failed\n");
        exit(EXIT_FAILURE);
    }
    
    cout<<"Socket Connection is up and about\n";
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;//INADDR_ANY;inet_addr("localhost");
    address.sin_port = htons(PORT);

    if (bind(server_fd,(struct sockaddr *)&address,sizeof(address))<0){
        cout<<("bind failed\n");
        exit(EXIT_FAILURE);
    }    
    if (listen(server_fd, 3) < 0){
        cout<<("listening\n");
        exit(EXIT_FAILURE);
    }

while(1){
    char buffer[1024] = {0};
    cout<<("<<<< clearing buffer >>>>\n");
    addrlen = sizeof(struct sockaddr_in);
    cout<<("Waiting for incoming messages\n");
    if ((new_socket = accept(server_fd,(struct sockaddr *)&address,&addrlen))<0){
        cout<<("accept\n");
        exit(EXIT_FAILURE);
    }
       
    valread = read(new_socket, buffer, 1024);
    printf("Here is the message: %s\n",buffer);
    send(new_socket, buffer, sizeof(buffer), 0);
    
    
    if(!strcmp(buffer,buffer)){ //om DestAdd aan te geven.
        cout <<("<<<<<<<<<<<<<<<<<< Sending message to WEMOS >>>>>>>>>>>>>>>>>>\n");
    
        int WemosSock = 0, valread; 
        struct sockaddr_in serv_addr;  
        char buffer2[1024] = {0}; 
        if ((WemosSock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
        { 
            printf("\n <<< WEMOS Socket creation error \n"); 
            exit(EXIT_FAILURE); 
        } 
   
        serv_addr.sin_family = AF_INET; 
        serv_addr.sin_port = htons(DestPort); 
       
        // Convert IPv4 and IPv6 addresses from text to binary form 
        if(inet_pton(AF_INET, DestAdd, &serv_addr.sin_addr)<=0)  
        { 
            printf("\n <<< WEMOS Invalid address/ Address not supported \n"); 
            exit(EXIT_FAILURE); 
        } 
   
        if (connect(WemosSock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
        { 
            printf("\n <<< WEMOS Connection Failed \n"); 
            exit(EXIT_FAILURE);
        } 

        send(WemosSock, buffer, sizeof(buffer), 0); 
        cout<<("<<< WEMOS buffer sent\n");
        valread = read(WemosSock, buffer2, 1024); 
        printf("%s\n", buffer2);
        cout <<("<<< Wemos close connection\n");
        cout<<(" \n");
        close(WemosSock);
        cout <<("\n");
    }
}
}
