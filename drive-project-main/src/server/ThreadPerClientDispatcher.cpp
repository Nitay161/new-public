#include "ThreadPerClientDispatcher.h"

ThreadPerClientDispatcher::ThreadPerClientDispatcher() {}

void ThreadPerClientDispatcher::clientDispatch(ClientHandler* handler) {
    std::thread clientThread;

    clientThread = std::thread([handler](){
        handler->handle();
        delete handler;
    });
    clientThread.detach();
}