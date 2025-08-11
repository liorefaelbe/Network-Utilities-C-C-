#include <stdio.h>      // printf
#include <string.h>     // strlen
#include <unistd.h>     // sleep
#include <arpa/inet.h>  // socket
#include <stdlib.h>     // atoi
\
#include "network_utils.h" // utils

#define BUFFER_SIZE (0x400)

/*******************************Main****************************************/

int main(int argc, char* argv[])
{
    (void)argc;

    int port = atoi(argv[1]);

    struct sockaddr_in server_add = {0};
    struct sockaddr_in client_add = {0};

    char buffer[BUFFER_SIZE] = {0};
    const char* message[] = {"1: Pong", "2: Pong", "3: Pong", "4: Pong", "5: Pong"};

    int server_fd = SocketCreate(SOCK_DGRAM, &server_add, port);

    SocketBind(server_fd, &server_add);

    printf("Server binded on port %d\n", port);
    
    for (int i = 0; i < 5; ++i)
    {
        UDPReceiveFrom(server_fd, buffer, BUFFER_SIZE, 0, &client_add);
        sleep(1);
        UDPSendTo(server_fd, message[i], strlen(message[i]) + 1, &client_add);

        printf("\n");
    }

    SocketClose(server_fd);
 
    return (0);
}