Client::Client(const std::string& ip, int port) {
    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error creating socket" << std::endl;
        exit(1);
    }

    // Set server address
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);

}

void Client::connectToServer() {
    // Connect to server
    if (connect(sockfd, (sockaddr *) &server_address, sizeof(server_address)) < 0) {
        std::cerr << "Error connecting to server" << std::endl;
        exit(1);
    }
    std::cout << "  Connected to server" << std::endl;

    //Create threads for sending and receiving data
    std::thread sendThread(&Client::sendMessageToServer, this);
    sendThread.join();

}

void Client::sendMessageToServer() {
    std::string message;
    std::cout << "Enter a message to send to the server (or 'disconnect' to quit):" << std::endl;
    while (true) {
        std::getline(std::cin, message);
        if (send(sockfd, message.c_str(), message.length(), 0) < 0) {
            std::cerr << "Error sending message: " << std::endl;
            break;
        }
        receiveMessage();
    }
}

void Client::receiveMessage() {
    char buffer[1024] = {0};
    int bytesReceived = recv(sockfd, buffer, sizeof(buffer), 0);
    std::string message(buffer);
    if(message == "bye")
    {
        close(sockfd);
        std::cout << "disconnected" << std::endl;
        exit(1);
    }

    std::cout << "Message received: " << std::endl << message << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << "Enter a message to send to the server (or 'disconnect' to quit):" << std::endl;
    
}

Client::~Client() {
    close(sockfd);
    std::cout << "Disconnected from server" << std::endl;
}