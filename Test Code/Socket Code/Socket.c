#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 8080 

//Destination moet een string zijn dus "192.168.178.49", define in raspberry program de verschillende Destinations.

//Data is wat je schrijft, Actuator is de actuator die je wilt aansturen op de gewenste WEMOS(Destination)

void SocketWrite(int Data, char *Actuator, char *Destination) { 
    int sockCreated = 0;  
    struct sockaddr_in serv_addr; 
    char *hello = "Hello from client"; //moet nog gefixt worden moet int Data zijn.
    char buffer[1024] = {0}; 
    if ((sockCreated = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, Destination, &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sockCreated, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    send(sockCreated, hello, strlen(hello), 0 ); 
    printf("Hello message sent\n"); 	//debug opties
} 

//Sensor is de sensor die je wilt uitlezen op de gewenste WEMOS(Destination)
char* SocketRead(char *Sensor , char *Destination) { 
    int sockCreated = 0; 
    int valread; 
    struct sockaddr_in serv_addr; 
    char buffer[1024] = {0}; 
    if ((sockCreated = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, Destination, &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sockCreated, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    }  
    valread = read(sockCreated, buffer, 1024); 
    printf("%s\n",buffer ); 	//debug opties
    return buffer; 
} 
