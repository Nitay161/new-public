#include "DeleteCommand.h"
#include <stdexcept>

// constructor
DeleteCommand::DeleteCommand(storageManager* sm) {
    this->sm = sm;
}

// execute method
string DeleteCommand::execute(int argc, std::vector<std::string> argv) {
    // Check if arguments are sufficient (cmd + filename)
    if (argc < 2) {
        throw std::invalid_argument("400 Bad Request");
    }

    std::string fileName = argv[1];

    try {
        sm->deleteFile(fileName);
        return "204 No Content";
    } catch (const std::exception& e) {
        // If storageManager throws (file not found), we map it to 404
        throw std::invalid_argument("404 Not Found");
    }
}