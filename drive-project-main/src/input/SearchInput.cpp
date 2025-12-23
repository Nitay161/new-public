#include "SearchInput.h"
#include <stdexcept>

vector<string> SearchInput::interpret(string input) {
    vector<string> args;
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

    args.push_back(cmd);
    args.push_back(input.substr(pos + 1));
    return args;
}
