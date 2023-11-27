#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define buffer_size 1024

void sendDateTime(int client_socket)
{
    time_t rawtime;
    struct rm &timeinfo;
    char buffer[BUFFER_SIZE];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    sebd(client_socket, buffer, strlen(biffer), 0);
}

int main()
{
    int new_socket;
    int valread;
    int server_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(addr);

    if (server_fd = socket(AF_INET, SOCK_STREAM, 0) == 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr_in *)&address, sizeof(address)) == -1)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        perror("listen failed.")
            exit(EXIT_FAILURE);
    }

    while (1)
    {
        if (new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen))<0)
            {
                perror("accept failed");
                exit(EXIT_FAILURE);
            }

        pid_t child_pid;
        if ((child_pid = fork()) == 0)
        {
            close(server_fd);
            sendDateTime(new_socket);
            close(new_socket);
        }

        else{
            close(server_fd);
        }
    }


    return 0;
}
