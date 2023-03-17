#ifndef SERVER_HPP
#define SERVER_HPP

#include "tcp_server_socket.hpp"
#include "tcp_client_socket.hpp"
#include "net_tcp_selector.hpp"
#include "file_actions.hpp"
#include "threads_pool.hpp"
#include "thread_pool_actions.hpp"

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

    void Kill() override;

    net::ServerSocket& ServerSocket() {return m_serverSocket;}
    std::unordered_map<int, std::unique_ptr<net::ClientSocket>>& Clients() {return m_clients;}
    net::tcp::Selector& Selector() {return m_selector;}

private:
    virtual void cleanData() = 0;
    virtual bool gotMessage(int a_descriptor) = 0;

private:
    void removeClient(int a_descriptor);
    int addNewClient();

protected:
    std::unordered_map<int, std::unique_ptr<net::ClientSocket>> m_clients;

private:
    net::tcp::Selector m_selector;
    std::atomic<bool> m_flag;
    std::atomic<unsigned int> m_numOfClients;
};

class Server : public IntermediateServer {
public:
    Server(const char* a_ip, int a_port=4466);

    bool gotMessage(int a_descriptor) override;
    
    virtual void cleanData() override;

private:
    void initalizeActivites();

private:
    std::unordered_map<int, std::fstream> m_files;
    std::unordered_map<int, std::unique_ptr<actions::AbstractAct>> m_actions;
    char m_buffer[protocol::bufSize];
};


void addNewClient2(std::unique_ptr<IntermediateServer> a_server);


#endif //SERVER_HPP