#include <iostream>
#include <cstring>
#include <unistd.h>        //read(), close()
#include <sys/types.h>
#include <sys/socket.h>    //socket(), bind(),
#include <netinet/in.h>    //struct sockaddr_in server_addr

#include <thread>
#include <vector>

#include "client.h"


int main() {
    std::string str;
    std::cout << "Please enter. connect " << std::endl;
    std::getline(std::cin, str);
    //std::string c{"connect"};
    if(str == "connect") {
        Client client("127.0.0.1", 8080);
        client.connectToServer();
        client.sendMessageToServer();
    }
    else {
        std::cout << "Wrong <IP_ADDRESS> or <PORT>" << std::endl << "Please tray again" << std::endl;
    }
    
}