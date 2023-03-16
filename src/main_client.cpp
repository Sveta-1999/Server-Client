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
    std::cout << "Please enter. connect <IP_ADDRESS> and <PORT>" << std::endl;
    std::getline(std::cin, str);
    std::string str1;
    std::vector<std::string>  vec;
    for(int i = 0; i < str.size(); ++i)
    {
        if(str[i] == '<' or str[i] == '>')
        {
            continue;
        }
        if(str[i] != ' ')
        {
            str1 += str[i];
        }
        else {
            vec.push_back(str1);
            str1 = "";
        }
    }
    vec.push_back(str1);
    std::cout << vec[vec.size() - 2] << "     " << stoi(vec[vec.size() - 1]);
    if(vec[0] == "connect") {
        Client client(vec[vec.size() - 2], stoi(vec[vec.size() - 1]));
        client.connectToServer();
        client.sendMessageToServer();
    }
    else {
        std::cout << "Wrong <IP_ADDRESS> or <PORT>" << std::endl << "Please tray again" << std::endl;
    }
    
}