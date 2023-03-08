#ifndef TCPCLIENTSOCKET_HPP
#define TCPCLIENTSOCKET_HPP

#include "tcp_socket.hpp"
#include <netinet/in.h> //struct sockaddr_int, socklent_t */
#include <vector>

constexpr int MTU  = 1500;

namespace net {

class ClientSocket {
public:
    ClientSocket();
    ClientSocket(const char* a_ip);
    ClientSocket(int a_desciptr);
    ClientSocket(const ClientSocket& a_other) = delete;
    ClientSocket &operator=(const ClientSocket& a_other) = delete;
    ~ClientSocket() = default;

    void Connect(const char* a_ip, int a_port=4466);

    template<typename T>
    size_t Send(const T&  a_message);

    template<typename T>
    size_t Send(const std::vector<T>& a_vec);

    template<typename T>
    size_t Send(const T* a_buf, size_t a_bytesNum);

    template<typename T>
    size_t Recv(T& a_dest);

    template<typename T>
    size_t Recv(std::vector<T>& a_vec);

    size_t Recv(std::string& a_dest);
    
    size_t Send(std::string& a_dest);

    size_t Recv(char* a_buffer, size_t a_size);

    template<typename T>
    size_t Recv(T* a_buf);

    Socket& socket();

    void clearBuffer();
 
private:  
    /* void clearBuffer(); */
    Socket m_socket;
    char m_buffer[MTU];
};


} // net 

#include "inl/tcp_client_scoket.hxx"

#endif // TCPCLIENTSOCKET_HPP