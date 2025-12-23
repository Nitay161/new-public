#ifndef CLIENTINFO_H
#define CLIENTINFO_H
#include <string>

class ClientInfo {
    public:
        std::string address;
        int socketFd;

        ClientInfo() : address(""), socketFd(-1) {}

        ClientInfo(std::string addr, int fd){
            address = addr;
            socketFd = fd;
        }
};

#endif // CLIENTINFO_H