#include <stdio.h>      // printf
#include <string.h>     // strlen
#include <unistd.h>     // sleep
#include <arpa/inet.h>  // socket
#include <stdlib.h>     // atoi

#include "network_utils.h" // utils

#define BUFFER_SIZE (0x400)

/*******************************Main****************************************/

int main(int argc, char* argv[])
{
    (void)argc;

    int port = atoi(argv[2]);

    struct sockaddr_in serv_addr = {0};

    char buffer[BUFFER_SIZE] = {0};
    char* message[] = {"1: Ping", "2: Ping", "3: Ping", "4: Ping", "5: Ping"};
    
    int client_fd = SocketCreate(SOCK_STREAM, &serv_addr, port);

    ConvertIP(client_fd, argv[1], &serv_addr);

    TCPConnect(client_fd, &serv_addr);
 
    /* for (int i = 0; i < 5; ++i)
    {
        TCPSend(client_fd, message[i], strlen(message[i]) + 1);
        sleep(1);
        TCPReceive(client_fd, buffer, BUFFER_SIZE);

        printf("\n");
    } */

    TCPSend(client_fd, message[0], strlen(message[0]) + 1);
    TCPReceive(client_fd, buffer, BUFFER_SIZE);

    SocketClose(client_fd);

    return (0);
}
