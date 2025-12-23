#ifndef GETINPUT_H
#define GETINPUT_H

#include "ICInput.h"

class GetInput : public ICInput{
    public:
        vector<string> interpret(string input) override;
        virtual ~GetInput() {}
};

#endif