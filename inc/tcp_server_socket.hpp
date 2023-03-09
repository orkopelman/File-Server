#ifndef TCPSERVERSOCKET_HPP
#define TCPSERVERSOCKET_HPP

#include <netinet/in.h> //struct sockaddr_int, socklent_t */

#include "tcp_socket.hpp"
#include "tcp_client_socket.hpp"
#include <memory>
#include <exception>

namespace net {

class Continued : public std::exception {
public:
    using std::exception::exception;
};

class ServerSocket {
public:
    ServerSocket();
    ServerSocket(const char* a_ip, int a_port=4466);
    ServerSocket(const ServerSocket& a_other) = delete;
    ServerSocket &operator=(const ServerSocket& a_other) = delete;
    ~ServerSocket() = default;
    
    void initalizeServer(const char* a_ip, int a_port=4466);

    std::unique_ptr<ClientSocket> Accept();
    
    int& descriptor();

    void SetBlocking(bool a_blocking);

private:
    void declareReusable();
    void Bind(const char* a_ip, int a_port=4466);
    void Listen();

private:
    Socket m_socket;
};


} // net 

#include "inl/tcp_server_socket.hxx"

#endif // TCPSERVERSOCKET_HPP