#ifndef ISTORAGEDISPATCHER_H
#define ISTORAGEDISPATCHER_H

#include "storageManager.h"
#include "../server/ClientInfo.h"

class IStorageDispatcher {
    public: 
        virtual ~IStorageDispatcher(){};

        // Returns the storage manager instance for client to be used
        virtual storageManager* getStorageManager(ClientInfo clientInfo)=0;

};

#endif // ISTORAGEDISPATCHER_H