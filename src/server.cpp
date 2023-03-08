#include "server.hpp"
#include "protocol.hpp"
#include <iostream>
#include <atomic>
#include <unistd.h> //sleep

void IntermediateServer::Run() 
{
    std::atomic<bool> flag{true};
    m_selector.Track(m_serverSocket.descriptor());
    m_serverSocket.SetBlocking(false);
    while (flag) {
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
                    flag = false;
                    break;
                }      
            } 
        }
    }
}


void::IntermediateServer::removeClient(std::unique_ptr<net::ClientSocket> a_client)
{
    int descriptor = a_client->socket().descriptor();
    m_clients.erase(descriptor);
}

int::IntermediateServer::addNewClient()
{
    std::unique_ptr<net::ClientSocket> client = m_serverSocket.Accept();
    int descriptor = client->socket().descriptor();
    client->socket().SetBlocking(false);    
    m_clients[descriptor] = std::move(client);
    
    return descriptor;
}

void Server::Kill() 
{
    m_files.clear();
    m_actions.clear();
    m_clients.clear();
}


Server::Server(const char* a_ip, int a_port) 
{
    m_serverSocket.initalizeServer(a_ip, a_port);
}


void Server::initalizeActivites(char* a_buffer, int& a_recBytes, int* a_sentBytes)
{
    using namespace actions;
    m_actions[protocol::TAG::OPEN] = std::make_unique<OpenAct>(a_buffer,a_sentBytes);
    m_actions[protocol::TAG::CLOSE] = std::make_unique <CloseAct>(a_buffer,a_sentBytes);
    m_actions[protocol::TAG::READ] = std::make_unique <ReadAct>(a_buffer, a_sentBytes );
    m_actions[protocol::TAG::WRITE] = std::make_unique <WriteAct>(a_buffer,a_recBytes,a_sentBytes);
}


bool Server::gotMessage(int a_descriptor)
{
  
    int recvBytes = m_clients[a_descriptor]->Recv(m_buffer, protocol::MTU);
    int sentBytes;

    initalizeActivites(m_buffer, recvBytes, &sentBytes);
    char* bufferToSend = m_actions[m_buffer[0]]->Act(m_files[a_descriptor]);

    m_clients[a_descriptor]->Send(bufferToSend, sentBytes);
    return true;
}
