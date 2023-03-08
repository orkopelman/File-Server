#include <errno.h>       /* erno */
#include <iostream>

constexpr int optval = 1;
constexpr int connectionsNum = 10;

namespace net {

inline ServerSocket::ServerSocket() 
: m_socket()
{}

inline ServerSocket::ServerSocket(const char* a_ip, int a_port) 
: m_socket()
{
    initalizeServer( a_ip,  a_port);
}

inline void ServerSocket::declareReusable()
{
    if (setsockopt(m_socket.descriptor(), SOL_SOCKET, 
        SO_REUSEADDR, &optval, sizeof(optval)) < 0) {
	    throw std::runtime_error("reused failed");
    }
}

inline void ServerSocket::Bind(const char* a_ip, int a_port)
{
    m_socket.configSocket(a_ip, a_port);
    if (bind(m_socket.descriptor(), (struct sockaddr*) &(m_socket.sockAddr()),
         m_socket.sinLen()) < 0) {
        throw std::runtime_error("bind failed");
    }
}

inline void ServerSocket::Listen()
{
    if (listen(m_socket.descriptor(), connectionsNum) < 0) 
    {
	     throw std::runtime_error("listen failed");
    }
}

inline std::unique_ptr<ClientSocket> ServerSocket::Accept()
{
    std::unique_ptr<ClientSocket> acceptedPtr{new ClientSocket{}};

    int acceptedDescriptor = accept(m_socket.descriptor(),
                             reinterpret_cast<struct sockaddr*>(&(acceptedPtr->socket().sockAddr())),
                             &(acceptedPtr->socket().sinLen()));
    if (acceptedDescriptor < 0) {

        if (errno != EAGAIN && errno != EWOULDBLOCK) {
            throw std::runtime_error("Could not Accept new client");
        } else {
            throw Continued();
        }
    }
    acceptedPtr->socket().descriptor() = acceptedDescriptor;
    return acceptedPtr;
}


inline void ServerSocket::SetBlocking(bool a_blocking)
{
    int flags = fcntl(m_socket.descriptor(), F_GETFL, 0);
    if (flags == fail) {
        throw std::runtime_error("error at fcnt F_GETEL");
    }
    flags = a_blocking ? (flags & ~O_NONBLOCK) : (flags | O_NONBLOCK);
    if (fcntl(m_socket.descriptor(), F_SETFL, flags) == fail) {
        throw std::runtime_error("error at fcnt F_SETFL");
    }
}


inline void ServerSocket::initalizeServer(const char* a_ip, int a_port)
{
    SetBlocking(true);
    declareReusable();
    Bind(a_ip, a_port);
    Listen();
}


inline int& ServerSocket::descriptor()
{
    return m_socket.descriptor();
}


} // net 

