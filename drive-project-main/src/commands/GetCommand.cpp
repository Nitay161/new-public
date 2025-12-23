#include "ICommand.h"
#include <vector>
#include <string>
#include <iostream>
#include "../storage/storageManager.h"
#include "GetCommand.h"
#include "../compression/Compressor.h"

using namespace std;

// constructor
GetCommand::GetCommand(storageManager* sm) {
    this->sm = sm;
}

// execute method - this function gets arguments for the command to execute and executes it.
string GetCommand::execute(int argc, vector<string> argv) {
    // if less then 2 arguments it is error.
    if (argc < 2) throw std::invalid_argument("400 Bad Request");

    string fileName = argv[1];
    try
    {
        string content = decompress(sm->load(fileName));
        return "200 Ok\n\n" + content;
    }
    catch(const std::invalid_argument& e)
    {
        throw std::invalid_argument("404 Not Found");
    }
}
