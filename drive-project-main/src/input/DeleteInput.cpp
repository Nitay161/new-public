#include "DeleteInput.h"
#include <stdexcept>

vector<string> DeleteInput::interpret(string input) {
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
    input = input.substr(pos + 1);

    // Find the second space.
    pos = input.find(' ');
    // If there are spaces then the format is wrong.
    if (pos != string::npos) {
        throw invalid_argument("400 Bad Request");
    }
    args.push_back(input);
    return args;
}
