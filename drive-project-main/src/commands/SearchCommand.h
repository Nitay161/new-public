#ifndef SEARCHCOMMAND_H
#define SEARCHCOMMAND_H

#include <vector>
#include <string>
#include "../storage/storageManager.h"
#include "ICommand.h"

class SearchCommand : public ICommand {
    private:
        storageManager* sm;

    public:
        // constructor
        SearchCommand(storageManager* sm);

        string execute(int argc, std::vector<std::string> argv) override;

        virtual ~SearchCommand() {}
};

#endif