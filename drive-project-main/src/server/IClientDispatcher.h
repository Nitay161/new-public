#ifndef ICLIENTDISPATCHER_H
#define ICLIENTDISPATCHER_H

#include "../storage/storageManager.h"
#include "ClientHandler.h"

class IClientDispatcher {
    public:
        virtual void clientDispatch(ClientHandler* handler) = 0;

        virtual ~IClientDispatcher() {}
};

#endif  // ICLIENTDISPATCHER_H