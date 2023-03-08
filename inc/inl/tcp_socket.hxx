#include <stdexcept>
#include <unistd.h>  //close()
#include <arpa/inet.h> //inet_addr
#include <fcntl.h>   // fcntl 
#include <string.h> //memset
#include <iostream>

constexpr int fail = -1;

namespace net {

inline Socket::Socket()
: m_descriptor(-1)
, m_sin()
, m_sinLen(sizeof(m_sin))
{
    memset(&m_sin, 0 ,sizeof(m_sin));
    createSocket();
}

inline Socket::Socket(int a_descript)
: m_descriptor(a_descript)
, m_sin()
, m_sinLen(sizeof(m_sin))
{
    memset(&m_sin, 0 ,sizeof(m_sin));
}

inline Socket::~Socket() 
{
    close();
}


inline void Socket::close() const 
{
    ::close(m_descriptor);
}

inline void Socket::createSocket() 
{
    m_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (m_descriptor < 0) {
        throw std::runtime_error("socket failed");
    }
}  

inline int& Socket::descriptor()  
{
    return m_descriptor;
}

inline struct sockaddr_in& Socket::sockAddr() 
{
    return m_sin;
}

inline socklen_t& Socket::sinLen()
{
    return m_sinLen;
}

inline void Socket::configSocket(const char* a_ip, int a_port )
{
    memset(&m_sin, 0 ,sizeof(m_sin));
    m_sin.sin_family = AF_INET;
    m_sin.sin_addr.s_addr = inet_addr(a_ip);
    m_sin.sin_port = htons(a_port);
}

inline void Socket::SetBlocking(bool a_blocking)
{
    //std::cout << "asdasda" << m_descriptor << "12";
    int flags = fcntl(m_descriptor, F_GETFL, 0); 
    //std::cout << "flags = " << flags;
    if (flags == fail) {
        throw std::runtime_error("error at fcnt F_GETEL");
    }
    flags = a_blocking ? (flags & ~O_NONBLOCK) : (flags | O_NONBLOCK);
    if (fcntl(m_descriptor, F_SETFL, flags) == fail) {
        throw std::runtime_error("error at fcnt F_SETFL");
    }
}



} //net 