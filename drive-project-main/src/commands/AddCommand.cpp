#include "ICommand.h"
#include <vector>
#include <string>
#include <iostream>
#include "../storage/storageManager.h"
#include "AddCommand.h"
#include "../compression/Compressor.h"

// constructor
AddCommand::AddCommand(storageManager* sm) {
    this->sm = sm;
}

// execute method - this function gets arguments for the command to execute and executes it.
string AddCommand::execute(int argc, std::vector<std::string> argv) {
    // if less then 3 arguments it is error.
    if (argc < 3) throw std::invalid_argument("400 Bad Request");

    // the file name is the second argument.
    std::string name = argv[1];
    // the text is the third argument.
    std::string text = argv[2];

    sm->save(name, compress(text));
    return "201 Created";
}