#include "Socket.h"

#include <iostream>
#include <stdexcept>
#include <sys/socket.h>
#define BUFFER_SIZE 1024


Socket_server::Socket_server(int port, int client_count = -1) {
    m_addr.sin_family = AF_INET;
    m_addr.sin_addr.s_addr = INADDR_ANY;
    m_addr.sin_port = htons(port);
    m_server = socket(AF_INET, SOCK_STREAM, 0);
    m_socket_size = sizeof(m_server);
    
    if (bind(m_server, (struct sockaddr*)&m_addr,sizeof(m_addr)) < 0) {
        throw std::runtime_error("Error: bind");
    }
    if (client_count == -1) {
        client_count = SOMAXCONN;
    } 
    if (listen(m_server, client_count) < 0) {
        throw std::runtime_error("Error: listen!");
    }
    else {
        std::cout << "Server start listen: port " << port << std::endl;
    }
    m_client_count = client_count;
    m_count = 0;
    m_client_array = {};
}

void Socket_server::crate_client(const std::string& client_name) {
    if (!(m_count < m_client_count || m_client_count == -1)) {
        throw std::runtime_error("Error: client count out of range!");
    }
    for (const auto& i : m_client_array) {
        if (i.first == client_name) {
            throw std::runtime_error("Error: krknutyun");
        }
    }
    int new_client = accept(m_server, (struct sockaddr*)&m_addr, &m_socket_size); 
    m_client_array[client_name] = new_client;
    m_count++;
}

void Socket_server::send_ms(const std::string& data, const std::string& client_name) {
    if (BUFFER_SIZE < data.length()){
        throw std::runtime_error("Error: larger than expected");
    }
    char buffer[BUFFER_SIZE];
    int i {};
    for (; i < data.length(); i++) {
        buffer[i] = data[i];
    }
    buffer[i] = '\0';
    send(m_client_array[client_name], buffer, BUFFER_SIZE, 0);
}

std::string Socket_server::recv_ms(const std::string& client_name) {
    int buffer[BUFFER_SIZE];
    int check = recv(m_client_array[client_name], buffer, BUFFER_SIZE, 0);
    if (check < 0) {
        throw std::runtime_error("Error!!");
    }
    std::string result { "" };
    for (int i {}; buffer[i]; ++i) {
        result += buffer[i];
    }
    return result;
}

Socket_server::~Socket_server() {
    for (auto& i : m_client_array) {
        close(i.second);
    }
    close(m_server);
}
