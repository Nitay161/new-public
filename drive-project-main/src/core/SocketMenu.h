#ifndef SOCKETMENU_H
#define SOCKETMENU_H

#include "IMenu.h"
#include <iostream>
#include <string.h>
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdexcept>


using namespace std;

class SocketMenu : public IMenu {
    private:
        int socket_fd; // File descriptor for the socket connection
        

    public:
        //constructor
        SocketMenu(int fd);
    
        string nextCommand() override;

        void displayOutput(string text) override;

        void displayError(string text) override;
};
#endif