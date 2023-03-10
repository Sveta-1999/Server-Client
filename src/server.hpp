Server::Server(int port) : m_port(port) {
    // Create the socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error creating socket" << std::endl;
        exit(1);
    }

    // Set socket options to reuse address
    int optval = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1) {
        perror("setsockopt");
        exit(1);
    }

    // Bind the socket to an address and port
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(m_port);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockaddr*) &server_address, sizeof(server_address)) < 0) {
        std::cerr << "Error binding socket" << std::endl;
        exit(1);
    }

    // Listen for connections
    if (listen(sockfd, 5) < 0) {
        std::cerr << "Error listening for connections" << std::endl;
        exit(1);
    }
}

void Server::accept_client() {
    //Accept and handle connections
    while (true) {
        struct sockaddr_in client_address;
        socklen_t client_address_len = sizeof(client_address);

        int clientfd = accept(sockfd, (struct sockaddr*) &client_address, &client_address_len);
        if (clientfd < 0) {
            perror("ERROR!!!");
            std::cerr << "Error accepting client connection" << std::endl;
            continue;
        }
        clients.push_back(clientfd);
        std::thread t(&Server::handle_client, this, clientfd, inet_ntoa(client_address.sin_addr));
        t.detach();

        std::cout << "New client connected" << std::endl;
    }
}

void Server::handle_client(int clientfd, const char* client_ip) {
    std::cout << client_ip << std::endl;
    std::cout << std::endl;

    while(true) {
        char buffer[1024] = {0};
        int num_bytes = recv(clientfd, buffer, sizeof(buffer), 0);
        if (num_bytes < 0) {
            std::cerr << "Error receiving data from client" << std::endl;
            return;
        }

        std::string message = buffer;
        std::cout << "Received message: " << message << std::endl;
        if(message == "disconnect") {
            for(std::vector<int>::size_type i = 0; i < clients.size(); ++i)
            {
                if(clientfd == clients[i])
                {
                    std::string output = "bye";
                    std::cout << "Client is disconnected" << std::endl;
                    send(clientfd, output.c_str(), output.length(), 0);
                    close(clientfd);
                }
            }
            break;
        }
        std::string output;
        FILE* pipe = popen(message.c_str(), "r");
        if (pipe != nullptr) {
            char buffer[1024] = {0};
            while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
                output += buffer;
            }
            pclose(pipe); 
            if(output == "") {
                std::string error{message + ": command not found"};
                if (send(clientfd, error.c_str(), error.length(), 0) < 0) {
                    std::cerr << "Error sending response to client" << std::endl;
                    return;
                }
            }else {
                if (send(clientfd, output.c_str(), output.length(), 0) < 0) {
                    std::cerr << "Error sending response to client" << std::endl;
                    return;
                }
            }
            
        }
    }
}

Server::~Server() {
    close(sockfd);
}