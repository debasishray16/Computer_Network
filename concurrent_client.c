#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define buffer_size 1024

int main(){
    int sock=0;
    strut sockaddr_in serv_Addr;
    char buffer[BUFFER_SIZE];

    if ((sock=socket(AF_INET,SOCK_STREAM,0))<0){
        printf("Socket creation error.");
        exit(EXIT_FAILURE);
    }

    serv_Addr.sin_family = AF_INET;
    serv_Addr.sin_addr.s_addr=INADDR_ANY;
    serv_Addr.sin_port = htons(PORT);


    if (connect(sock,(struct sockaddr*)&serv_Addr,sizeof(serv_Addr))<0){
        printf("Connection failed");
    }

    int valread=read(sock,buffer,BUFFER_SIZE);
    printf("Server Date and Time:%s\n",buffer);
    return 0;
}