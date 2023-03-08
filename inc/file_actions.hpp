#ifndef FILE_ACTIONS_HPP
#define FILE_ACTIONS_HPP

#include <fstream>
#include <iostream>
#include <string.h>
#include "protocol.hpp"

namespace actions{

class AbstractAct {
public:
    virtual ~AbstractAct() = default;

    virtual char* Act(std::fstream& a_file) = 0;

protected:
    AbstractAct() = default;
    AbstractAct(AbstractAct const& a_other) =  default;
    AbstractAct& operator=(AbstractAct const& a_other) =  default;
};


class OpenAct : public AbstractAct {
public:
    OpenAct(char *a_buffer, int* a_sentBytes);

    char* Act(std::fstream& a_file) override;

private:
    char m_buffer[protocol::bufSize];
};

class CloseAct : public AbstractAct {
public:
    CloseAct(char *a_buffer, int* a_sentBytes);

    char* Act(std::fstream& a_file) override;

private:
    char m_buffer[protocol::bufSize];
};

class ReadAct : public AbstractAct {
public:
    ReadAct(char * a_buffer, int* a_sentBytes);

    char* Act(std::fstream& a_file) override;

private:
    char m_buffer[protocol::bufSize];
    int* m_sentBytes;
};

class WriteAct : public AbstractAct {
public:
    WriteAct(char * a_buffer, int a_recvBytes, int* a_sentBytes);

    char* Act(std::fstream& a_file) override;
  
private:
    char m_buffer[protocol::bufSize];
    int m_recBytes;
};

}

#endif //FILE_ACTIONS_HPP