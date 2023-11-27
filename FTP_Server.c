#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#define PORT 12345
#define MAX_CONNECTIONS 5

void send_file(int client_socket, const char *file_name) {
    FILE *file = fopen(file_name, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char buffer[1024];
    int bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        send(client_socket, buffer, bytes_read, 0);
    }

    fclose(file);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(struct sockaddr_in);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Error creating socket");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error binding socket");
        return 1;
    }

    if (listen(server_socket, MAX_CONNECTIONS) == -1) {
        perror("Error listening for connections");
        return 1;
    }

    printf("FTP Server listening on port %d...\n", PORT);

    client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_size);
    if (client_socket == -1) {
        perror("Error accepting client connection");
        return 1;
    }

    const char *file_name = "example.txt"; // Change this to the desired file name

    send_file(client_socket, file_name);
    close(client_socket);
    close(server_socket);

    return 0;
}

