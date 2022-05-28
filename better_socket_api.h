#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include <arpa/inet.h>


/* 
    Creates an IPv4 stream socket and makes it re-useable by default.
    Returns the socket descriptor as an integer.
*/
int create_ipv4_socket(int reusable)
{
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("create_ipv4_socket(): Socket creation failed.");
        exit(1);
    }
    if (reusable == 1) 
    {
        int opt = 1;
        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1)
        {
            perror("create_ipv4_socket(): Error setting socket to reusable...");
            exit(1);
        } 
    }
    return sockfd;
}

/*
    Given a pointer to a sockaddr_in struct, fill the fields with the given
    ip and port values.
*/
void create_ipv4_address(struct sockaddr_in* address_pointer, char* ip, int port)
{
    (*address_pointer).sin_family = AF_INET;
    (*address_pointer).sin_port = htons(port);
    inet_aton(ip, &(*address_pointer).sin_addr);
}

/*
    Binds the given socket using the given sockaddr_in struct.
*/
void bind_socket(int socket_fd, struct sockaddr_in* sockaddr_in_pointer)
{
    if (bind(socket_fd, (struct sockaddr*) sockaddr_in_pointer, sizeof(*sockaddr_in_pointer)) < 0)
    {
        perror("bind_socket(): Bind failed.");
        exit(1);
    }
}

/*
    Given the socket descriptor and backlog, start listening on the socket.
*/
void server_listen(int fd, int backlog)
{
    if (listen(fd, backlog) != 0)
    {
        perror("server_listen(): Listen failed.");
        exit(1);
    }
}

/*
    Accept connection on the given socket.
*/
int server_accept(int server_fd, struct sockaddr_in* client)
{
    int length = sizeof(*client);
    int client_fd = accept(server_fd, (struct sockaddr*) client, &length);
    if (client_fd < 0)
    {
        perror("server_accept(): Server accept failed...");
        exit(1);
    }
    return client_fd;
}

/*
    Attempts to connect a client socket to the given server defined at server_addr.
*/
void client_connect(int client_fd, struct sockaddr_in* server_addr)
{
    if ( connect(client_fd, (struct sockaddr*) server_addr, sizeof(*server_addr)) != 0 )
    {
        perror("client_connect(): ");
        exit(1);
    }
}

/*
    This function can be treated like a basic send function, it ensures that all
    data in the given buffer is sent to the destination.
*/
int send_all(int sockfd, const void* b)
{
    int bytes_sent;
    const char* buffer = b;
    int length = strlen(buffer);
    while (length > 0)
    {
        bytes_sent = send(sockfd, buffer, length, 0);
        if (bytes_sent <= 0)
        {
            return -1;
        }
        buffer += bytes_sent;
        length -= bytes_sent;
    }
    return 0;
}

/*
    This function can be treated like a basic recv function. It ensures that all of
    the data is read from the receive buffer. Returns -1 for failure, 0 for closed connection,
    and 1 for successful recv.
*/
int recv_all(int sockfd, const void* b)
{
    int bytes_read;
    const char* buffer = b;
    int length = strlen(buffer);
    int total = 0;
    while ((bytes_read = recv(sockfd, buffer, length-total, 0)) > 0)
    {
        total += bytes_read;
    }
    if (bytes_read == -1)
    {
        return -1;
    }
    else if (bytes_read == 0)
    {
        return 0;
    }
    return 1;
}



























