#include <stdio.h>      // printf
#include <string.h>     // strlen
#include <unistd.h>     // sleep
#include <arpa/inet.h>  // socket
#include <stdlib.h>     // atoi

#include "network_utils.h" // utils

#define BUFFER_SIZE (0x400)

int main(int argc, char* argv[])
{
    (void)argc;

    struct sockaddr_in recv_addr = {0};
    char buffer[BUFFER_SIZE] = {0};

    int sockfd = SocketCreate(SOCK_DGRAM, &recv_addr, atoi(argv[1]));
    SocketBind(sockfd, &recv_addr);

    for (int i = 0; i < 5; ++i)
    {
        UDPReceiveFrom(sockfd, buffer, BUFFER_SIZE, 0, &recv_addr);
    }

    SocketClose(sockfd);
    
    return (0);
}