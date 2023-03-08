
/*
Project Goal:

Create file access over TCP/IP connection
Client opens file on server computer, using TCP/IP connection, reads data, closes file

Steps and requirements:
1. Implement client based on abstract "class nfs"
2. Implement server, abstract class and concrete implementions
3. Suggest basic protocol between client and server
4. Several files can be open at the same time
5. Several clients can use server at the same time

Assumption and directions
1. working code is not expected, pseudo-code in C++ syntax
2. TCP implmentation may be schematic, can skip details (flags, includes, and other stuff are not required)
3. Describe messages in both directions
4. Pay attention to interfaces (class methods)
*/

#include "tcp_client_socket.hpp"
#include <fstream>
#include <iostream>


class nfs //abstracet client interface
{
public:
    virtual ~nfs() = default;

    virtual int open(const char *name, const int flags=0) = 0;
    virtual int close() = 0;
    virtual int read(char * buf, int size) = 0;
    virtual int write(const char * buf, int size) = 0;
};


class mynfs : public nfs
{
public:
    mynfs();
   
    int open(const char *name, const int flags=0) override;
    int close() override;
    int read(char * buf, int size) override ;
    int write(const char * buf, int size) override ;

private:
    net::ClientSocket m_clientSocket;
};



// int main() {

//     char buffer[100];

//     nfs *f1 = new mynfs;
//     nfs *f2 = new mynfs;

//     f1->open("test1.txt");
//     f2->open("test2.txt");

//     auto bytes = f1->read(buffer,20);
//     std::cout << buffer << " " << bytes << std::endl;
//     return 0;
// }


