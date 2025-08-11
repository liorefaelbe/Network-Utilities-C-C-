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

    struct sockaddr_in server_add = {0};
        
    char buffer[BUFFER_SIZE] = {0};
    const char* message[] = {"1: Ping", "2: Ping", "3: Ping", "4: Ping", "5: Ping"};

    int client_fd = SocketCreate(SOCK_DGRAM, &server_add, atoi(argv[2]));

    ConvertIP(client_fd, argv[1], &server_add);
 
    for (int i = 0; i < 5; ++i)
    {
        UDPSendTo(client_fd, message[i], strlen(message[i]) + 1, &server_add);
        sleep(1);
        UDPReceiveFrom(client_fd, buffer, BUFFER_SIZE, 0, &server_add);
  
        printf("\n");
    }

    SocketClose(client_fd);

    return (0);
}
