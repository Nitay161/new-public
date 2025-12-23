#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include "ClientInfo.h"
#include "ClientHandler.h"
#include "IClientDispatcher.h"
#include "../storage/storageManager.h"
#include "../storage/IStorageDispatcher.h"
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

class TCPServer {
    private:
        int port;
        IClientDispatcher* clientDispatcher;
        IStorageDispatcher* storageDispatcher;

        void acceptClient(ClientInfo clientInfo);

    public:
        // constructor
        TCPServer(int port, IClientDispatcher* clientDispatcher, IStorageDispatcher* storageDispatcher);

        // start the server
        void start();

        // destructor
        ~TCPServer();
};

#endif