#include "InputManager.h"
#include <stdexcept>

InputManager::InputManager(map<string, ICInput*> inputs) : inputs(inputs) {}

vector<string> InputManager::interpret(string input) {
    // Find the first space.
    int pos = input.find(' ');
    // If no spaces then the format is wrong.
    if (pos == string::npos) {
        throw invalid_argument("400 Bad Request");
    }
    string cmd = input.substr(0, pos);

    // Changing the cmd to lowercase.
    for (char &c : cmd) {
        c = tolower((unsigned char)c);
    }

    // Checking if the command name exists.
    bool isExist = false;
    for (const auto& pair : inputs) {
        if (pair.first == cmd) {
            isExist = true;
            break;
        }
    }
    if (!isExist) throw invalid_argument("400 Bad Request");

    return inputs[cmd]->interpret(input);
}
