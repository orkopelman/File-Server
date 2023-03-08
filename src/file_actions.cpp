#include "file_actions.hpp"
#include <string.h> //memcpy

namespace actions {

int open(std::fstream& a_file,const char *name, const int flags=0) 
{
    
    switch (flags)
    {
        case (protocol::flags::READ):
            a_file.open(name,std::ios::in);
            break;
        case (protocol::flags::WRITE):
            a_file.open(name,std::ios::out);
            break;
        case (protocol::flags::APPEND):
            a_file.open(name,std::ios::app);
            break;
        case (protocol::flags::BINARY):
            a_file.open(name,std::ios::binary);
            break;

        default:
            break;
    }

    if (a_file.good() || a_file.eof()) {
        return protocol::SUCCESS;
    }
    return protocol::FAILED;
}

int close(std::fstream& a_file) 
{
    if (a_file.is_open()) {
        a_file.close();
        return a_file.fail() ? protocol::FAILED : protocol::SUCCESS;
    }
    return protocol::FAILED;
}

int read(std::fstream& a_file,char * buf, int size)  {

    if (!a_file.is_open()) {
        throw std::runtime_error("file is closed");
    }

    if (!a_file.good()) {
        if (a_file.eof()) {
            return 0;
        }
        throw std::runtime_error("file is corrupted");
    }
    
    a_file.read(buf,size);

    if (a_file.good()) {
        return size;
    }

    if (!a_file.eof()) {
        throw std::runtime_error("Reading Failed");
    }
    return a_file.gcount();
}

int write(std::fstream& a_file,const char * buf, int size)  {

    if (!a_file.is_open()) {
        return protocol::FAILED;
    }

    if (!a_file.good() && !a_file.eof()) {
        return protocol::FAILED;
    }

    a_file.write(buf + 1, size);

    if (a_file.bad() || a_file.fail()) {
        return protocol::FAILED;
    }

    return protocol::SUCCESS;
}


OpenAct::OpenAct(char *a_buffer, int* a_sentBytes)
{
    memcpy(m_buffer, a_buffer, protocol::bufSize);
    *a_sentBytes = 1;
}

CloseAct::CloseAct(char *a_buffer, int* a_sentBytes)
{
    memcpy(m_buffer, a_buffer, protocol::bufSize);
    *a_sentBytes = 1;
}

ReadAct::ReadAct(char * a_buffer, int* a_sentBytes)
: m_sentBytes(a_sentBytes)
{{memcpy(m_buffer, a_buffer, protocol::bufSize);}}

WriteAct::WriteAct(char * a_buffer, int a_recvBytes, int* a_sentBytes)
: m_recBytes(a_recvBytes)
{
    memcpy(m_buffer, a_buffer, protocol::bufSize);
    *a_sentBytes = 1;
}


char* OpenAct::Act(std::fstream& a_file)  
{
    m_buffer[0] = open(a_file ,m_buffer + 2, m_buffer[1]); 
    return m_buffer; 
}

char* CloseAct::Act(std::fstream& a_file)  
{
    m_buffer[0] = close(a_file);
    return m_buffer; 
}

char* ReadAct::Act(std::fstream& a_file)  
{
    m_buffer[0] = protocol::DATA;
    *m_sentBytes = read(a_file, m_buffer, static_cast<uint8_t>(m_buffer[1])) + 1; 
    return m_buffer; 
}

char* WriteAct::Act(std::fstream& a_file)  
{
    m_buffer[0] = write(a_file, m_buffer, m_recBytes-1); 
    return m_buffer;
}

} //actionss