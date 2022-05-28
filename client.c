#include "better_socket_api.h"

#define BUFLEN 1024

int main(int argc, char* argv)
{
    
    // Defining the server port and ip that cients will connect to.
    char* server_ip = "10.0.0.159";
    int server_port = 8080;
    // Defining client address struct.
    struct sockaddr_in server_sai;
    int client_fd;
    char buffer[BUFLEN];

    // Create client socket.
    client_fd = create_ipv4_socket(1);
    
    // Create the server address structure.
    create_ipv4_address(&server_sai, server_ip, server_port);
    
    // Connect to the server.
    client_connect(client_fd, &server_sai);
    
    // User input
    memset(buffer, 0, BUFLEN);
    printf("Enter a message to send to the server: ");
    scanf("%s", buffer);
    // Send to the server.
    send_all(client_fd, buffer, 10);
    // Close the connection.
    close(client_fd);
    return 0;
}

