#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
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
    Stream sockets only.
*/
void send_all(int sockfd, char buffer[])
{
    int buflen = sizeof((char*)buffer)/sizeof(char);
    char* buff_ptr = buffer;
    while (buflen > 0)
    {
        int i = send(sockfd, buff_ptr, buflen, 0);
        if (i < 0) 
        {
            perror("fail");
            exit(1);
        }
        buff_ptr += i;
        buflen -= i;
    }
}

/*
    This function can be used as the default recv call, it 
    ensures that all of the data in the buffer is read.
    This is specific to stream sockets only.
*/
int recv_all(int sockfd, char buffer[])
{
    int buflen = sizeof((char*)buffer)/sizeof(char);
    char* bptr = buffer;
    int bytes_to_read = buflen;
    while (bytes_to_read > 0)
    {
        int i = recv(sockfd, bptr, buflen, 0);
        if (i < 0) return -1;
        if (i == 0) return 0;
        bptr += i;
        bytes_to_read -= i;
    }
    return 1;
}



























