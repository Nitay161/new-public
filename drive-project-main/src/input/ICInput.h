#ifndef ICINPUT_H
#define ICINPUT_H

#include <string>
#include <map>
#include <vector>

using namespace std;

class ICInput {
    public:
        // This function input strings and return it as arguments to command.
        virtual vector<string> interpret(string input) = 0;
        virtual ~ICInput() {}
};

#endif