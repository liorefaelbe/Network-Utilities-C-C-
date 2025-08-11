#ifndef __ILRD_SERVER_HPP__
#define __ILRD_SERVER_HPP__

#include <vector>       // vector
#include <sys/select.h> // select
#include <arpa/inet.h>  // socket

using namespace std;

namespace ilrd_166_7
{
class Server
{
public:
    explicit Server(unsigned short port);
    ~Server();
    void Run(); // throw exception if fails
                // While running typing "ping" in the terminal would print "pong" in response.
                // Stdin "quit" stops the function
private:
    unsigned short m_port;
    vector<int>m_fd_vec;
    fd_set m_select_bitmap;

    int m_udp_fd;
    int m_tcp_fd;
    int m_max_fd;

    bool m_is_run;

    void InitSockets();
    void CloseSockets();
    void SetSelect();
    void InputHandler();
    void UDPHandler();
    void TCPHandler();
    void AcceptHandler();
};
} //ilrd_166_7

#endif //__ILRD_SERVER_HPP__