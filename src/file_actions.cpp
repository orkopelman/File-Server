#include "file_actions.hpp"
#include <string.h> //memcpy

namespace actions {

int open(std::fstream& a_file,const char *a_name, const int a_flags=0) 
{
    auto var = std::ios::in;
    
    switch (a_flags)
    {
        case (protocol::flags::READ_WRITE_APPEND):
            var = std::ios::in | std::ios::out | std::ios::app;
            break;
        case (protocol::flags::READ_WRITE):
            var = std::ios::in | std::ios::out;
            break;
        case (protocol::flags::WRITE):
            var = std::ios::out;
            break;
        case (protocol::flags::APPEND):
            var = std::ios::app;
            break;
        case (protocol::flags::BINARY):
             var = std::ios::binary;
            break;

        default:
            break;
    }

    a_file.open(a_name, var);

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

int read(std::fstream& a_file,char * a_buf, int a_size)  {

    if (!a_file.is_open()) {
        throw std::runtime_error("file is closed");
    }

    if (!a_file.good()) {
        if (a_file.eof()) {
            return 0;
        }
        throw std::runtime_error("file is corrupted");
    }
    
    a_file.read(a_buf,a_size);

    if (a_file.good()) {
        return a_size;
    }

    if (!a_file.eof()) {
        throw std::runtime_error("Reading Failed");
    }
    return a_file.gcount();
}

int write(std::fstream& a_file,const char * a_buf, int a_size)  {

    if (!a_file.is_open()) {
        return protocol::FAILED;
    }

    if (!a_file.good() && !a_file.eof()) {
        return protocol::FAILED;
    }

    a_file.write(a_buf + 1, a_size);

    if (a_file.bad() || a_file.fail()) {
        return protocol::FAILED;
    }

    return protocol::SUCCESS;
}


char* OpenAct::Act(std::fstream& a_file,char *a_buffer,  int a_recvBytes, int* a_sentBytes)
{
    a_buffer[0] = open(a_file ,a_buffer + 2, a_buffer[1]); 
    return a_buffer; 
}

char* CloseAct::Act(std::fstream& a_file,char *a_buffer,  int a_recvBytes, int* a_sentBytes)
{
    a_buffer[0] = close(a_file);
    return a_buffer; 
}

char* ReadAct::Act(std::fstream& a_file,char *a_buffer,  int a_recvBytes, int* a_sentBytes) 
{
    a_buffer[0] = protocol::DATA;
    *a_sentBytes = read(a_file, a_buffer, static_cast<uint8_t>(a_buffer[1])) + 1; 
    return a_buffer; 
}

char* WriteAct::Act(std::fstream& a_file,char *a_buffer,  int a_recvBytes, int* a_sentBytes)
{
    a_buffer[0] = write(a_file, a_buffer, a_recvBytes-1); 
    return a_buffer;
}


} //actionss