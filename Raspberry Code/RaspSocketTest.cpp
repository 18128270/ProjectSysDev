#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <fcntl.h>

#define PORT 8181

using namespace std;

int main(){
    int server_fd,new_socket, valread;
    int n;
    socklen_t addrlen;
    struct sockaddr_in address;
    char buffer[1024] = {0};
    if ((server_fd = socket(AF_INET,SOCK_STREAM,0)) == 0){
        cout<<("socket failed"\n);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;//INADDR_ANY;inet_addr("localhost");
    address.sin_port = htons(PORT);

    cout<<"\nworking";

    if (bind(server_fd,(struct sockaddr *)&address,sizeof(address)) < 0){
        cout<<("bind failed\n");
    }
    while(1){
        listen(server_fd,3);
        addrlen = sizeof(struct sockaddr_in);
        cout<<("*************************\n");
        new_socket = accept(server_fd,(struct sockaddr *)&address,&addrlen);
        cout<<("*************************\n");
        
        if (new_socket > 0){
            valread = read(new_socket, buffer, 1024);
            string query(buffer);
            string strl(query);
            string s, d;
            istringstream iss(strl);
            iss >> s;
            iss >> d;
            const char* source = s.c_str();
            const char* dest = d.c_str();
            printf("Here is the message: %s %s\n",source,dest);
            n = write(new_socket, "I got your message", 18);
        }
    }
    close(new_socket);
    return close(server_fd);
}