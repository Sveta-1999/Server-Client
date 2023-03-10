# Server-Client
A <b> server-client </b> architecture is a common pattern in network programming where a server program listens for incoming connections from client programs, and then establishes a connection with each client to exchange data.

<hr>

In this architecture, the server typically has a fixed IP address and listens on a specific port for incoming connections. The client program initiates a connection to the server by specifying the server's IP address and port number.
Once a connection is established, the client and server can exchange data.

![6230ef96eb40de02b0e3fbd0_61c9fc4838f10a5389c9cbca_Client-Server-Diagram](https://user-images.githubusercontent.com/79526438/224438648-4a7119af-4d28-4439-b174-7b9c4436a4b4.jpeg)


<b> To implement a client-server architecture in C++, we can use socket programming and threads . </b>
1. Create a socket using the socket() function.
2. Bind the socket to an address using the bind() function.
3. Listen for incoming connections using the listen() function.
4. Accept incoming connections using the accept() function.
5. Spawn a new thread to handle the connection.
6. In the new thread, use the send() and recv() functions to communicate with the client.
7. Once the client and server are connected, they can communicate with each other by sending messages back and forth. The protocol used for communication will depend on the specific application.
8. When a client connects to the server, a new thread is created to handle the client communication. The communication between the client and server takes place within this thread.



![socket-programming](https://user-images.githubusercontent.com/79526438/224439401-28e9f9e5-b746-4361-b805-9b2c3a2a5a96.png)
