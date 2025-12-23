#ifndef GETCOMMAND_H
#define GETCOMMAND_H

#include <vector>
#include <string>
#include "../storage/storageManager.h"
#include "ICommand.h"

class GetCommand : public ICommand{
    private :
        storageManager* sm;

    public:
        //constructor
        GetCommand(storageManager* sm);

        string execute(int argc, std::vector<std::string> argv) override;

        virtual ~GetCommand() {}
};

#endif
