#ifndef ADDINPUT_H
#define ADDINPUT_H

#include "ICInput.h"

class AddInput : public ICInput{
    public:
        vector<string> interpret(string input) override;
        virtual ~AddInput() {}
};

#endif