#pragma once
#include "comm_sock_include.h"
#include "comm_include.h"

class TcpLister
{
public:
    explicit TcpLister(unsigned short port, string name = "anonymous");
    //������move����, �������忽������, ȷ�����ᷢ������
    TcpLister(TcpLister&&);
    ~TcpLister();

    void Start();

    socket_fd_t Accept();
    socket_fd_t Accept(struct sockaddr_storage&);

    string Name() { return name_; }
    unsigned short Port() { return static_cast<unsigned short>(port_); }
    socket_fd_t Socket() { return tcp_lister_sock_;}

private:
    socket_fd_t tcp_lister_sock_{static_cast<socket_fd_t>(-1)};

    string name_{"anonymous"};
    int port_{0};
};

