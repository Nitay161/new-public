#ifndef ADDCOMMAND_H
#define ADDCOMMAND_H

#include <vector>
#include <string>
#include "../storage/storageManager.h"
#include "ICommand.h"

class AddCommand : public ICommand{
    private :
        storageManager* sm;

    public:
        //constructor
        AddCommand(storageManager* sm);

        string execute(int argc, std::vector<std::string> argv) override;

        virtual ~AddCommand() {}
};

#endif