#include "ConstStorageDispatcher.h"

ConstStorageDispatcher::ConstStorageDispatcher(storageManager* sm){
    this->global = sm;
}

// Returns the  same storage manager instance for all clients to be used
storageManager* ConstStorageDispatcher::getStorageManager(ClientInfo clientInfo) {
    return global;
}