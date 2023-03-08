#include "client.hpp"
#include "string.h" //strlen
#include "protocol.hpp"
#include <memory>

mynfs::mynfs()
: m_clientSocket("127.0.0.1")
{}

int mynfs::open(const char *name, const int flags) 
{
    
    size_t size = strlen(name) + 3;
    char* buffer = new char[size];          //unique_ptr

    //std::unique_ptr<char> buffer = std::make_unique<char>();
    int i=0;

    buffer[i++] = protocol::OPEN;
    buffer[i++] = flags;

    memcpy(buffer+i,name,size-2);

    m_clientSocket.Send(buffer, size); 

    char response;
    m_clientSocket.Recv(&response,1);

    delete[] buffer;    
    return response;
}

int mynfs::close() 
{
    size_t size = 1;
    char* buffer = new char[size];             
    
    buffer[0] = protocol::CLOSE;
    m_clientSocket.Send(buffer, size);   

    char response;
    m_clientSocket.Recv(response);
    delete[] buffer; 
    return response;
}

int mynfs::read(char * buf, int size)
{
    size_t sizeBuf = 2;
    char* buffer = new char[sizeBuf]; 

    buffer[0] = protocol::READ;
    buffer[1] = static_cast<uint8_t>(size);

    m_clientSocket.Send(buffer, sizeBuf); 

    size_t read_bytes = m_clientSocket.Recv(buf,size);
    delete[] buffer; 
    return read_bytes;
}

int mynfs::write(const char * buf, int size)
{
    size_t sizeBuf = strlen(buf) + 1;
    char* buffer = new char[sizeBuf]; 

    buffer[0] = protocol::WRITE;
    memcpy(buffer+1,buf,sizeBuf-1);

    m_clientSocket.Send(buffer, sizeBuf); 

    char response;
    m_clientSocket.Recv(response);
    delete[] buffer; 
    return response;
}