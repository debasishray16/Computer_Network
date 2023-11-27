#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server_socket == -1)
    {
        perror("Socket Creation Failed.");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Bind Connect Failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 5) == -1)
    {
        perror("Listen Failed");
        exit(EXIT_FAILURE);
    }

    printf("Connection established to port 8080");

    int client_socket;
    struct sockaddr_in client_addr;
    socklen_t addr_size = sizeof(client_addr);
    if (client_socket == -1)
    {
        perror("Accept Failed");
        exit(EXIT_FAILURE);
    }

    printf("Connection established with a client.");

    while (1)
    {
        if (recv(client_socket, message, strlen(message), 0) <= 0)
        {
            perror("Receive failed");
            break;
        }

        printf("Client: %s", message);

        printf("Server: ");
        fgets(message, sizeof(message), stdin);
        send(client_socket, message, strlen(message), 0);
    }

    close(client_socket);
    close(server_socket);

    return 0;
}