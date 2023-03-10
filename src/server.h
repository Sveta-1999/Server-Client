#ifndef SERVER_H
#define SERVER_H

class Server {
public:
    Server(int port);
    void accept_client();
    void handle_client(int clientfd, const char* client_ip);
    ~Server();

private:
    int m_port;
    int sockfd;
    struct sockaddr_in server_address;
    std::vector<int> clients;   
};

#include "server.hpp"

#endif //SERVER_H