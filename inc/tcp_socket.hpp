#ifndef TCPSOCKET_HPP
#define TCPSOCKET_HPP

#include <netinet/in.h> //struct sockaddr_int, socklent_t

namespace net {

class Socket {
public:
    Socket();
    Socket(int a_descript);
    Socket(const Socket& a_other) = delete;
    Socket &operator=(const Socket& a_other) = delete;
    ~Socket();

    int& descriptor();
    struct sockaddr_in& sockAddr();
    socklen_t& sinLen();
    void configSocket(const char* a_ip, int a_port=4466);
    void SetBlocking(bool a_blocking);
    
private:
    void createSocket(); 
    void close() const;
    
private: 
    int m_descriptor;
    struct sockaddr_in m_sin;
    socklen_t m_sinLen;
};

} // net 

# include "inl/tcp_socket.hxx"

#endif // TCPSOCKET_HPP