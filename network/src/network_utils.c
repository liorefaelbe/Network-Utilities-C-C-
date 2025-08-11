#include <stdio.h>      // printf
#include <stdlib.h>     // exit
#include <string.h>     // strlen
#include <unistd.h>     // close
#include <arpa/inet.h>  // socket

#include "network_utils.h" // utils

/*****************************TCP&UTP*******************************/

int SocketCreate(int socket_type, struct sockaddr_in* address, uint32_t port)
{
    int server_fd = socket(AF_INET, socket_type, 0);
    if (server_fd < 0)
    {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    int size = 1024 * 1024 * 4;
    if (setsockopt(server_fd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size)) < 0)
    {
        perror("setsockopt(SO_RCVBUF) failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    memset(address, 0, sizeof(*address));
    address->sin_family = AF_INET;
    address->sin_addr.s_addr = INADDR_ANY;
    address->sin_port = htons(port);

    return (server_fd);
}

void SocketBind(int server_fd, const struct sockaddr_in* address)
{
    if (bind(server_fd, (struct sockaddr*)address, sizeof(*address)) < 0)
    {
        perror("Bind failed");
        SocketClose(server_fd);
        exit(EXIT_FAILURE);
    }
}

void ConvertIP(int socket_fd, const char* ip, struct sockaddr_in* serv_addr)
{
    if (inet_pton(AF_INET, ip, &serv_addr->sin_addr) <= 0)
    {
        perror("Invalid address");
        SocketClose(socket_fd);
        exit(EXIT_FAILURE);
    }
}

void SocketClose(int socket_fd)
{
    close(socket_fd);
}

/*******************************TCP*********************************/

void TCPSend(int socket_fd, const char* message, uint32_t size)
{
    if (send(socket_fd, message, size, 0) == -1)
    {
        perror("Send failed");
        SocketClose(socket_fd);
        exit(EXIT_FAILURE);
    }
    printf("\033[0;32mTCP Message sent\033[0m\n");
}

int TCPReceive(int socket_fd, char* buffer, uint32_t size)
{
    int status = recv(socket_fd, buffer, size, 0);
    if (status == -1)
    {
        perror("Read failed");
        SocketClose(socket_fd);
        exit(EXIT_FAILURE);
    }
    else if (status == 0)
    {
        return (1);
    }

    printf("\033[35mTCP Received: \033[0m%s\n", buffer);

    return (0);
}

void TCPListen(int socket_fd, uint32_t req_q_size, uint32_t port)
{
    (void)port;
    if (listen(socket_fd, req_q_size) < 0)
    {
        perror("Listen failed");
        SocketClose(socket_fd);
        exit(EXIT_FAILURE);
    }
    printf("\033[36mTCP Server listening on port %d\033[0m\n", port);
}

int TCPAccept(int socket_fd, struct sockaddr_in* address, uint32_t port)
{
    address->sin_family = AF_INET;
    address->sin_addr.s_addr = INADDR_ANY;
    address->sin_port = htons(port);

    socklen_t addrlen = sizeof(*address);

    int new_socket = accept(socket_fd, (struct sockaddr*)address, &addrlen);
    if (new_socket < 0)
    {
        perror("Accept failed");
        SocketClose(socket_fd);
        exit(EXIT_FAILURE);
    }

    return (new_socket);
}

void TCPConnect(int socket_fd, const struct sockaddr_in* serv_addr)
{
    socklen_t len = sizeof(*serv_addr);

    if (connect(socket_fd, (struct sockaddr*)serv_addr, len) < 0)
    {
        perror("Connection failed");
        SocketClose(socket_fd);
        exit(EXIT_FAILURE);
    }
} 

/*******************************UTP*********************************/

void UDPSendTo(int socket_fd, const char* message, uint32_t size, const struct sockaddr_in* addr)
{
    socklen_t addr_len = sizeof(*addr);

    if (sendto(socket_fd, message, size, 0, (struct sockaddr*)addr, addr_len) < 0)
    {
        perror("Sendto failed");
        exit(EXIT_FAILURE);
    }
    printf("\033[0;32mUDP Message sent\033[0m\n");
}

void UDPReceiveFrom(int socket_fd, char* buffer, uint32_t size, int mode, const struct sockaddr_in* addr)
{
    socklen_t addr_len = sizeof(*addr);

    if (recvfrom(socket_fd, buffer, size, mode, (struct sockaddr*)addr, &addr_len) < 0) 
    {
        perror("Recvfrom failed");
        exit(EXIT_FAILURE);
    }
    printf("\033[35mUDP Received: \033[0m%s\n", buffer);
}

void UDPBroadcast(int socket_fd, struct sockaddr_in* broadcast_addr)
{

	inet_pton(AF_INET, "255.255.255.255", &broadcast_addr->sin_addr);

    int broadcast_enable = 1;

    if (setsockopt(socket_fd, SOL_SOCKET, SO_BROADCAST, &broadcast_enable, sizeof(broadcast_enable)) < 0)
    {
        perror("Setsockopt failed");
        exit(EXIT_FAILURE);
    }
}