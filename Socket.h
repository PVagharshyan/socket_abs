#pragma once 

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <map>

class Socket_server {
private:
    int m_server;
    struct sockaddr_in m_addr;
    socklen_t m_socket_size;
    int m_client_count;
    std::map<std::string, int> m_client_array;
    int m_count;
public:
    Socket_server(int, int);
    void crate_client(const std::string&);
    void send_ms(const std::string&, const std::string&);
    std::string recv_ms(const std::string&);
    ~Socket_server();
};
