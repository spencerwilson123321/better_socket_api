#include "better_socket_api.h"

#define BACKLOG 5

int main(int argc, char* argv)
{
    
    // Defining the server port and ip that cients will connect to.
    char* ip = "10.0.0.159";
    int port = 8080;
    // Defining the server and client address struct.
    struct sockaddr_in server_sai, client_sai;
    int client_fd;

    // Create main server socket.
    int server_fd = create_ipv4_socket(1);
    // Create main server socket address structure.
    create_ipv4_address(&server_sai, ip, port);
    // Bind and listen for incoming connections.
    bind_socket(server_fd, &server_sai);
    server_listen(server_fd, BACKLOG);
    // Accept incoming connections.
    client_fd = server_accept(server_fd, &client_sai);
    printf("Client file descriptor: %d\n", client_fd);
    
    // Read data and echo back.
    
    
    // Close file descriptors when done with them.
    close(server_fd);
    close(client_fd);
    
    return 0;
}
