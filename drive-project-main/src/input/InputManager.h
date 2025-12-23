#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <string>
#include <map>
#include <vector>
#include "ICInput.h"

class InputManager {
    private:
        map<string, ICInput*> inputs;
    public:
        InputManager(map<string, ICInput*> inputs);
        vector<string> interpret(string input);
        virtual ~InputManager() {}
};

#endif