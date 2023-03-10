#include <iostream>
#include <cstring>
#include <unistd.h>        //read(), close()
#include <sys/types.h>
#include <sys/socket.h>    //socket(), bind(),
#include <netinet/in.h>    //struct sockaddr_in server_addr
#include <arpa/inet.h> 

#include <sstream>
#include <thread>
#include <vector>

#include "server.h"

int main() {
    int port = 8080;
    Server server(port);
    server.accept_client();
}