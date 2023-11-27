#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        perror("socket could not be created");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(server_addr, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("connection failed.");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server.");

    char message[1024];

    while (1)
    {
        printf("Client: ");
        fgets(message, sizeof(message), stdin);
        send(client_socket, message, strlen(message), 0);

        if (recv(client_socket, message, sizeof(message), 0) <= 0)
        {
            perror("Received failed");
            break;
        }

        printf("Server: %s",message);
    }

    close(client_socket);
    return 0;
}