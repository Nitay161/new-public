#ifndef THREADPERCLIENTDISPATCHER_H
#define THREADPERCLIENTDISPATCHER_H

#include "IClientDispatcher.h"
#include "ClientHandler.h"
#include <thread>

class ThreadPerClientDispatcher : public IClientDispatcher {
    public:
        //constructor
        ThreadPerClientDispatcher();

        void clientDispatch(ClientHandler* handler) override ; 
};

#endif  // THREADPERCLIENTDISPATCHER_H