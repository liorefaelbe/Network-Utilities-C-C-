/*
	Author: Lior Refael Berkovits
	Reviewed by: Yehonatan
	Date: 08/04/2025
*/

#include <iostream>     	// ostream, istream
#include <fstream>  		// ofstream
#include <cstring>       	// string   
#include <unistd.h>			// STDIN_FILENO

#include "server.hpp"       // Server
#include "network_utils.h"  // utils

using namespace std;
namespace ilrd_166_7
{
static const size_t buff_size = 0x2000;
static const size_t req_q_size = 3;

static const char* message = "Pong";
static char buffer[buff_size] = {0};
static size_t log_i = 0;

enum message_type {TIMEOUT, STDIN_PING, STDIN_QUIT, TCP_ACCEPT, TCP_RCV, UDP_RCV};

/*******************************Forward-Declaration*************************************************/

static int CheckInput(void);
static int Max(int a, int b);
static void Log(message_type type, const int fd);

/***********************************Constractors****************************************************/

Server::Server(unsigned short port) : m_port(port), m_is_run(true)
{
	InitSockets();
}

Server::~Server()
{
	CloseSockets();
}

/***********************************Member-Functions************************************************/

void Server::Run()
{
	TCPListen(m_tcp_fd, req_q_size, m_port);

	while (m_is_run)
	{
		SetSelect();

		if (FD_ISSET(STDIN_FILENO, &m_select_bitmap) != 0 && CheckInput() == 1)
		{
			InputHandler();
		}

		if (FD_ISSET(m_udp_fd, &m_select_bitmap) != 0)
		{
			UDPHandler();
		}

		if (FD_ISSET(m_tcp_fd, &m_select_bitmap) != 0)
		{
			TCPHandler();
		}

		AcceptHandler();
	}
}

/**********************************Private-Functions************************************************/

void Server::InitSockets()
{
	struct sockaddr_in tcp_addr;
	memset(&tcp_addr, 0, sizeof(tcp_addr));

	m_tcp_fd = SocketCreate(SOCK_STREAM, &tcp_addr, m_port);
	SocketBind(m_tcp_fd, &tcp_addr);

	struct sockaddr_in udp_addr;
	memset(&udp_addr, 0, sizeof(udp_addr));

	m_udp_fd = SocketCreate(SOCK_DGRAM, &udp_addr, m_port);
	SocketBind(m_udp_fd, &udp_addr);

	m_max_fd = Max(m_tcp_fd, m_udp_fd);
}

void Server::CloseSockets()
{
	vector<int>::iterator it = m_fd_vec.begin();
	vector<int>::iterator end = m_fd_vec.end();

	for (; it != end; ++it)
	{
		SocketClose(*it);
	}
}

void Server::SetSelect()
{
	FD_ZERO(&m_select_bitmap);

	FD_SET(STDIN_FILENO, &m_select_bitmap);
	FD_SET(m_tcp_fd, &m_select_bitmap);
	FD_SET(m_udp_fd, &m_select_bitmap);

	timeval timeout = {7,0};
	if (select(m_max_fd + 1, &m_select_bitmap, NULL, NULL, &timeout) == 0)
	{
		Log(TIMEOUT, -1);
	}
}

void Server::InputHandler()
{
	m_is_run = false;
}

void Server::UDPHandler()
{
	struct sockaddr_in client_add;
	memset(&client_add, 0, sizeof(client_add));

	memset(&buffer, 0, buff_size);
	UDPReceiveFrom(m_udp_fd, buffer, buff_size, 0, &client_add);

	Log(UDP_RCV, m_udp_fd);

	UDPSendTo(m_udp_fd, message, strlen(message) + 1, &client_add);
}

void Server::TCPHandler()
{

	struct sockaddr_in send_add;
	int client_fd = TCPAccept(m_tcp_fd, &send_add, m_port);

	Log(TCP_ACCEPT, client_fd);

	m_fd_vec.push_back(client_fd);
	FD_SET(client_fd, &m_select_bitmap);

	m_max_fd = Max(m_max_fd, client_fd);
}

void Server::AcceptHandler()
{
	vector<int>::iterator it = m_fd_vec.begin();
	vector<int>::iterator end = m_fd_vec.end();

	for (; it != end; ++it)
	{
		if (FD_ISSET(*it, &m_select_bitmap) != 0)
		{
			memset(&buffer, 0, buff_size);
			if (TCPReceive(*it, buffer, buff_size) == 1)
			{
				Log(TCP_RCV, *it);
				m_fd_vec.erase(it);
			}
			else
			{
				TCPSend(*it, message, strlen(message) + 1);
			}
		}
	}
}

/*************************************Static-Functions**********************************************/

static int CheckInput(void)
{
	string buffer;

	getline(cin, buffer);
	if (buffer == "ping")
	{
		Log(STDIN_PING, STDIN_FILENO);
		cout << "\033[33mpong\033[0m\n";
	}
	else if (buffer == "quit")
	{
		Log(STDIN_QUIT, STDIN_FILENO);
		cout << "\033[36mServer quiting, bye!\033[0m\n";
		return (1);
	}

	return (0);
}

static int Max(int a, int b)
{
	return ((a > b) ? a : b);
}

static void Log(message_type type, const int fd)
{
	ofstream log("Log.txt", ios::app);
	
	switch (type)
	{
		case TIMEOUT:
			log << "Log" << log_i << ": No requests received";
			break;
		case STDIN_PING:
			log << "Log" << log_i << ": Stdin received: ping";
			break;
		case STDIN_QUIT:
			log << "Log" << log_i << ": Stdin received: quit";
			break;
		case TCP_ACCEPT:
			log << "Log" << log_i << ": TCP client accepted";
			break;
		case TCP_RCV:
			log << "Log" << log_i << ": TCP message received";
			break;
		case UDP_RCV:
			log << "Log" << log_i << ": UDP message received";
			break;
		++log_i;
	}
	
	log << ".	| File descriptor: " << fd << endl;
}
}