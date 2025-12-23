#ifndef CONSTSTORAGEDISPATCHER_H
#define CONSTSTORAGEDISPATCHER_H

#include "storageManager.h"
#include "IStorageDispatcher.h"

class ConstStorageDispatcher : public IStorageDispatcher {
    private:
        storageManager* global;
    
    public:
        // constructor
        ConstStorageDispatcher(storageManager* sm);

        storageManager* getStorageManager(ClientInfo clientInfo) override;
};

#endif // CONSTSTORAGEDISPATCHER_H