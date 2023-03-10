#ifndef CLIENT_H
#define CLIENT_H

class Client {
public:
    Client(const std::string& ip, int port);
    void connectToServer();
    void sendMessageToServer();
    void receiveMessage();
    ~Client();

private:
    int sockfd;
    struct sockaddr_in server_address;
};

#include "client.hpp"

#endif //CLIENT_H