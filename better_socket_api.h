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
    else
    {
        printf("create_ipv4_socket(): Socket created.\n");
    }
    if (reusable == 1) 
    {
        int opt = 1;
        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1)
        {
            perror("create_ipv4_socket(): Error setting socket to reusable.");
            exit(1);
        } 
        else 
        {
            printf("create_ipv4_socket(): Socket is reusable.\n");
        }
    }
    else
    {
        printf("create_ipv4_socket(): Socket is NOT set to reusable.\n");
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
    
*/
void bind_socket(int socket_fd, struct sockaddr_in* sockaddr_in_pointer)
{
    if (bind(socket_fd, (struct sockaddr*) sockaddr_in_pointer, sizeof(*sockaddr_in_pointer)) < 0)
    {
        perror("Bind failed.");
        exit(1);
    }
    else
    {
        printf("bind_socket(): Sucessful bind.\n");
    }
}

