#ifndef ICOMMAND_H
#define ICOMMAND_H

#include <string>
#include <map>
#include <vector>

using namespace std;

class ICommand {
    public:
        // This function gets arguments for the command to execute and executes it.
        virtual string execute(int argc, vector<string> argv) = 0;
        virtual ~ICommand() {}
};

#endif