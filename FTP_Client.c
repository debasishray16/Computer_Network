#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 12345

void receive_file(int socket, const char *file_name) {
    FILE *file = fopen(file_name, "wb");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char buffer[1024];
    int bytes_received;

    while ((bytes_received = recv(socket, buffer, sizeof(buffer), 0)) > 0) {
        fwrite(buffer, 1, bytes_received, file);
    }

    fclose(file);
}

int main() {
    int client_socket;
    struct sockaddr_in server_addr;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Error creating socket");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP address

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error connecting to server");
        return 1;
    }

    const char *file_name = "received_file.txt"; // Change this to the desired file name

    receive_file(client_socket, file_name);
    close(client_socket);

    printf("File received successfully.\n");

    return 0;
}

