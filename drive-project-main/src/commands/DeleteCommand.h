#ifndef DELETECOMMAND_H
#define DELETECOMMAND_H

#include <vector>
#include <string>
#include "../storage/storageManager.h"
#include "ICommand.h"

class DeleteCommand : public ICommand {
    private:
        storageManager* sm;

    public:
        // constructor
        DeleteCommand(storageManager* sm);

        string execute(int argc, std::vector<std::string> argv) override;

        virtual ~DeleteCommand() {}
};

#endif