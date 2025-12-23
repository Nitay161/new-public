#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include "ClientInfo.h"
#include "../core/app.cpp"
#include "../core/IMenu.h"
#include "../storage/storageManager.h"
#include "../input/ICInput.h"
#include "../input/InputManager.h"
#include "../input/AddInput.h"
#include "../input/GetInput.h"
#include "../input/SearchInput.h"
#include "../input/DeleteInput.h"
#include <string>
#include <map>
#include <limits>
#include <cstdlib>
#include "../commands/ICommand.h"
#include "../commands/AddCommand.h"
#include "../commands/GetCommand.h"
#include "../commands/SearchCommand.h"
#include "../core/SocketMenu.h"
#include "../commands/DeleteCommand.h"



class ClientHandler {
    private:
        ClientInfo clientInfo;
        storageManager* storageMgr;
    
    public:
        // constructor
        ClientHandler(ClientInfo cInfo, storageManager* storageMgr);
        virtual ~ClientHandler() = default;
        // function to handle client requests
        virtual void handle();
};

#endif // CLIENTHANDLER_H