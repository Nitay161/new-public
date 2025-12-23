#include "tcp_server.h"

TCPServer::TCPServer(int port, IClientDispatcher* clientDispatcher, IStorageDispatcher* storageDispatcher){
    this->port = port;
    this->clientDispatcher = clientDispatcher;
    this->storageDispatcher = storageDispatcher;
}

void TCPServer::start() {
    //create TCP socket
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {//if creation of socket failed
        perror("error creating socket");
    }

    //bind the socket to the specified IP and port
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY; //bind to any address
    sin.sin_port = htons(port); //bind to the server port
    
    //bind socket to port
    if (bind(server_sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) { //if binding failed
        perror("error binding socket");
    }

    while (true) {
        //listen to incoming connections
        if (listen(server_sock, SOMAXCONN) < 0) { 
            //if listening failed
            perror("error listening to a socket");
        }

        //accept a comming connection
        struct sockaddr_in client_sin;
        unsigned int addr_len = sizeof(client_sin);
        //create new socket for the client
        int client_sock = accept(server_sock,  (struct sockaddr *) &client_sin,  &addr_len);

        if (client_sock < 0) { //if accepting client connection failed
            perror("error accepting client");
        }

        //setup client info
        ClientInfo clientInfo = ClientInfo();
        clientInfo.socketFd = client_sock;
        
        acceptClient(clientInfo);
    }
}

void TCPServer::acceptClient(ClientInfo clientInfo) {
    // This function is now integrated into start()
    storageManager* sm = storageDispatcher->getStorageManager(clientInfo);
    //create client handler
    ClientHandler* handler = new ClientHandler(clientInfo, sm);
    //dispatch the client handler
    clientDispatcher->clientDispatch(handler);
}

TCPServer::~TCPServer() {
    // Destructor implementation
}