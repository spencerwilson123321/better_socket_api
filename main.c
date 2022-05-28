#include <stdio.h>
#include "better_socket_api.h"


int main()
{
    int fd = create_ipv4_socket(1);
    struct sockaddr_in address;
    create_ipv4_address(&address, "10.0.0.159", 8080);
    printf("Address struct port value: %d\n", ntohs(address.sin_port));
    printf("Address struct ip value: %s\n", inet_ntoa(address.sin_addr));
    bind_socket(fd, &address);
    server_listen();
    return 0;
}

