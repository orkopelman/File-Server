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

    virtual char* Act(std::fstream& a_file,char *a_buffer,  int a_recvBytes, int* a_sentBytes) = 0;

protected:
    AbstractAct() = default;
    AbstractAct(AbstractAct const& a_other) =  default;
    AbstractAct& operator=(AbstractAct const& a_other) =  default;
};


class OpenAct : public AbstractAct {
public:
    char* Act(std::fstream& a_file,char *a_buffer,  int a_recvBytes, int* a_sentBytes) override;
};

class CloseAct : public AbstractAct {
public:
    char* Act(std::fstream& a_file,char *a_buffer,  int a_recvBytes, int* a_sentBytes) override;
};

class ReadAct : public AbstractAct {
public:
    char* Act(std::fstream& a_file,char *a_buffer,  int a_recvBytes, int* a_sentBytes) override;
};

class WriteAct : public AbstractAct {
public:
    char* Act(std::fstream& a_file,char *a_buffer,  int a_recvBytes, int* a_sentBytes) override;
};

}

#endif //FILE_ACTIONS_HPP