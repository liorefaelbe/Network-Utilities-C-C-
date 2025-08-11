#include <stdio.h>      // printf
#include <string.h>     // strlen
#include <unistd.h>     // sleep
#include <arpa/inet.h>  // socket
#include <stdlib.h>     // atoi

#include "network_utils.h" // utils

#define BUFFER_SIZE (0x400)
#define REQ_Q_SIZE (3)

/*******************************Main****************************************/

int main(int argc, char* argv[])
{
    (void)argc;

    int port_bind = atoi(argv[1]);
    int port_send = atoi(argv[2]);

    struct sockaddr_in listen_add = {0};
    struct sockaddr_in send_add = {0};

    char buffer[BUFFER_SIZE] = {0};
    char* message[] = {"1: Pong", "2: Pong", "3: Pong", "4: Pong", "5: Pong"};
    
    int server_fd = SocketCreate(SOCK_STREAM, &listen_add, port_bind);

    SocketBind(server_fd, &listen_add);

    TCPListen(server_fd, REQ_Q_SIZE, port_bind);
    
    int new_socket = TCPAccept(server_fd, &send_add, port_send);

    for (int i = 0; i < 5; ++i)
    {
        TCPReceive(new_socket, buffer, BUFFER_SIZE);
        sleep(1);
        TCPSend(new_socket, message[i], strlen(message[i]) + 1);

        printf("\n");
    }

    SocketClose(server_fd);
    SocketClose(new_socket);
 
    return (0);
}