#include "AddInput.h"
#include <stdexcept>

vector<string> AddInput::interpret(string input) {
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
    // If no spaces then the format is wrong.
    if (pos == string::npos) {
        throw invalid_argument("400 Bad Request");
    }
    string word2 = input.substr(0, pos);
    // If the second word (after first space until second) is empty - it means the file name starts with ' ' which is illegal.
    if (word2 == "") {
        throw invalid_argument("400 Bad Request");
    }
    args.push_back(word2);
    args.push_back(input.substr(pos + 1));
    return args;
}
