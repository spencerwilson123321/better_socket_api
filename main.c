#include <stdio.h>
#include "better_socket_api.h"

#define BACKLOG 10

int main()
{
    int fd = create_ipv4_socket(1);
    struct sockaddr_in address;
    create_ipv4_address(&address, "10.0.0.159", 8080);
    bind_socket(fd, &address);
    server_listen(fd, BACKLOG);
    close(fd);
    return 0;
}


