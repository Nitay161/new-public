#ifndef DELETEINPUT_H
#define DELETEINPUT_H

#include "ICInput.h"

class DeleteInput : public ICInput{
    public:
        vector<string> interpret(string input) override;
        virtual ~DeleteInput() {}
};

#endif