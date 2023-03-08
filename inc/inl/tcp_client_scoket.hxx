#include <string.h> //memcpy
#include "protocol.hpp" //MTU

namespace net {

inline ClientSocket::ClientSocket()
: m_socket()
, m_buffer()
{
    clearBuffer();
}

inline ClientSocket::ClientSocket(int a_desciptr)
: m_socket(a_desciptr)
, m_buffer()
{
    clearBuffer();
}

inline ClientSocket::ClientSocket(const char* a_ip)
: m_socket()
, m_buffer()
{
    clearBuffer();
    Connect(a_ip);
}

inline void ClientSocket::Connect(const char* a_ip, int a_port)
{
    m_socket.configSocket(a_ip, a_port);
    if (connect(m_socket.descriptor(), 
        (struct sockaddr *) &m_socket.sockAddr(),
         m_socket.sinLen()) < 0) {
            throw std::runtime_error("connection failed");
        }
}

template<typename T>
size_t ClientSocket::Send(const T&  a_message) 
{
    clearBuffer();
    memcpy(m_buffer, &a_message, sizeof(a_message));

    ssize_t sent_bytes = send(m_socket.descriptor() , m_buffer, sizeof(a_message), 0);    
    if (sent_bytes < 0) {
        throw std::runtime_error("send failed");
    }
    return sent_bytes;
}

template<typename T>
size_t ClientSocket::Send(const T* a_buf, size_t a_bytesNum)
{
    ssize_t sent_bytes = send(m_socket.descriptor() , a_buf, a_bytesNum, 0);    
    if (sent_bytes < 0) {
        throw std::runtime_error("send failed");
    }
    //std::cout<<sent_bytes;
    return sent_bytes;
}

inline size_t ClientSocket::Send(std::string& a_dest) 
{
    return Send(a_dest.data(), a_dest.size());
}

template<typename T>
size_t ClientSocket::Send(const std::vector<T>& a_vec)
{
    size_t numOfElem = a_vec.size();
    const T* buf = a_vec.data();
    return Send(buf, numOfElem * sizeof(T));
}


template<typename T>
size_t ClientSocket::Recv(T& a_dest)
{
    ssize_t read_bytes = recv(m_socket.descriptor(), m_buffer, sizeof(a_dest), 0);
    if (read_bytes == 0) {
        throw std::runtime_error("connection is closed");
    }
    if (read_bytes < 0) {
        throw std::runtime_error("recv failed");
    }
    
    memcpy(&a_dest, m_buffer, sizeof(a_dest));
    clearBuffer();
    return read_bytes;
}


inline size_t ClientSocket::Recv(char* a_buffer, size_t a_size)
{
   
    if (a_buffer == NULL) {
        throw std::runtime_error("unintialiized buffer");
    }
    ssize_t read_bytes = recv(m_socket.descriptor(), a_buffer, a_size, 0);
    if (read_bytes == 0) {
        throw std::runtime_error("connection is closed");
    }
    if (read_bytes < 0) {
        throw std::runtime_error("recv failed");
    }
   
    return read_bytes;
}


inline size_t ClientSocket::Recv(std::string& a_dest)
{
    ssize_t read_bytes = recv(m_socket.descriptor(), m_buffer, sizeof(a_dest), 0);
    if (read_bytes == 0) {
        throw std::runtime_error("connection is closed");
    }
    if (read_bytes < 0) {
        throw std::runtime_error("recv failed");
    }
    
    a_dest.resize(read_bytes);
    memcpy(const_cast<char*>(a_dest.data()), m_buffer, read_bytes);
    clearBuffer();
    return read_bytes;
}

template<typename T>
size_t ClientSocket::Recv(std::vector<T>& a_vec)
{
    size_t numOfElem = a_vec.size();
    T* buf = new T[numOfElem];

    ssize_t read_bytes = recv(m_socket.descriptor(), buf, numOfElem * sizeof(T), 0);
    if (read_bytes == 0) {
        throw std::runtime_error("connection is closed");
    }
    if (read_bytes < 0) {
        throw std::runtime_error("recv failed");
    }
    
    for (size_t i=0; i<numOfElem;i++) {
        a_vec[i] = buf[i];
    }
    delete(buf);
    return read_bytes;
}

template<typename T>
size_t ClientSocket::Recv(T* a_dest)
{
    ssize_t read_bytes = recv(m_socket.descriptor(), m_buffer, sizeof(a_dest), 0);
    if (read_bytes == 0) {
        throw std::runtime_error("connection is closed");
    }
    if (read_bytes < 0) {
        throw std::runtime_error("recv failed");
    }
    
    memcpy(&a_dest, m_buffer, sizeof(a_dest));
    clearBuffer();
    return read_bytes;
}



inline Socket& ClientSocket::socket()
{
    return m_socket;
}


inline void ClientSocket::clearBuffer()
{
    memset(m_buffer, 0, protocol::MTU);
}


} //net


