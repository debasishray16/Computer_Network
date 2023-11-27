#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    char buffer[BUFFER_SIZE] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("Bind Failure");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        exit(EXIT_FAILURE);
    }

    printf("Server listening.....");
    if (new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&address) < 0)
    {
        printf("Accept error.");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        memset(buffer, 0, BUFFER_SIZE);
        int valread = read(new_socket, buffer, BUFFER_SIZE);
        if (valread > 0)
        {
            printf("CLient: %s\n", buffer);

            printf("Server: ");
            fgets(buffer, BUFFER_SIZE, , stdin);
            send(new_socket, buffer, strlen(buffer), 0);
        }
    }
    return 0;
}