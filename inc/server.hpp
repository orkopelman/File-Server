#ifndef SERVER_HPP
#define SERVER_HPP

#include "tcp_server_socket.hpp"
#include "tcp_client_socket.hpp"
#include "net_tcp_selector.hpp"
#include "file_actions.hpp"

#include <unordered_map>
#include <fstream>
#include <memory>

class InterfaceServer{
public:
    virtual ~InterfaceServer() = default;

    virtual void Run() = 0;
    virtual void Kill() = 0;

protected:
    net::ServerSocket m_serverSocket;
};

class IntermediateServer : public InterfaceServer{
public:
    virtual ~IntermediateServer() = default;

    void Run() override;

    virtual void Kill() = 0;
    virtual bool gotMessage(int a_descriptor) = 0;

private:
    int addNewClient();
    void removeClient(std::unique_ptr<net::ClientSocket> a_client);

protected:
    std::unordered_map<int, std::unique_ptr<net::ClientSocket>> m_clients;

private:
    net::tcp::Selector m_selector;
};

class Server : public IntermediateServer {
public:
    Server(const char* a_ip, int a_port=4466);

    bool gotMessage(int a_descriptor) override;
    void Kill() override;

private:
    void initalizeActivites(char* a_buffer, int& a_recBytes, int* a_sentBytes);

private:
    std::unordered_map<int, std::fstream> m_files;
    std::unordered_map<int, std::unique_ptr<actions::AbstractAct>> m_actions;
    char m_buffer[protocol::bufSize];
};


#endif //SERVER_HPP