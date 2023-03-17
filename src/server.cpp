#include "server.hpp"
#include "protocol.hpp"
#include <iostream>
#include <atomic>
#include <unistd.h> //sleep


void IntermediateServer::Run() 
{
    m_flag = true;
    m_selector.Track(m_serverSocket.descriptor());
    m_serverSocket.SetBlocking(false);
    while (m_flag) {
        m_selector.Select();
        if (m_selector.IsSet(m_serverSocket.descriptor())) {
            try{
                while (true) {
                    std::cout << " new client \n";
                    m_selector.Track(addNewClient());
                }
            }
            catch (net::Continued&) {
                std::cout << "Continued\n";
            }
        }
        for (auto it = m_clients.begin(); it!=m_clients.end(); it++) {
            if (m_selector.IsSet(it->first)) {
                try {
                    std::cout << " got message \n";
                    gotMessage(it->first);  
                }
                catch (...) {
                    std::cout << " catching \n";
                    removeClient(it->first);
                }      
            } 
        }
    }
    cleanData();
}


void::IntermediateServer::removeClient(int a_descriptor)
{
    m_clients.erase(a_descriptor);
    m_selector.Untrack(a_descriptor);
}

int::IntermediateServer::addNewClient()
{
    std::unique_ptr<net::ClientSocket> client = m_serverSocket.Accept();
    int descriptor = client->socket().descriptor();
    client->socket().SetBlocking(false);     // can remove?
    m_clients[descriptor] = std::move(client);
    
    return descriptor;
}


bool Server::gotMessage(int a_descriptor)
{
  
    int recvBytes = m_clients[a_descriptor]->Recv(m_buffer, protocol::MTU);
    int sentBytes = 1;

    char* bufferToSend = m_actions[m_buffer[0]]->Act(m_files[a_descriptor],m_buffer,
                                                        recvBytes, &sentBytes);

    m_clients[a_descriptor]->Send(bufferToSend, sentBytes);
 
    return true;
}

Server::Server(const char* a_ip, int a_port) 
{
    m_serverSocket.initalizeServer(a_ip, a_port);
    initalizeActivites();
}

void Server::cleanData() 
{
    m_actions.clear();
    m_clients.clear();
    m_files.clear();
}

void Server::initalizeActivites()
{
    using namespace actions;
    m_actions[protocol::TAG::OPEN] = std::make_unique<OpenAct>();
    m_actions[protocol::TAG::CLOSE] = std::make_unique <CloseAct>();
    m_actions[protocol::TAG::READ] = std::make_unique <ReadAct>();
    m_actions[protocol::TAG::WRITE] = std::make_unique <WriteAct>();
}


void addNewClient2(std::unique_ptr<IntermediateServer> a_server)
{
    std::unique_ptr<net::ClientSocket> client = (a_server->ServerSocket()).Accept();
    int descriptor = client->socket().descriptor();
    client->socket().SetBlocking(false);    
    a_server->Clients()[descriptor] = std::move(client);
    a_server->Selector().Track(descriptor);
}


void IntermediateServer::Kill() 
{
    m_flag = false;
}













