#ifndef SEARCHINPUT_H
#define SEARCHINPUT_H

#include "ICInput.h"

class SearchInput : public ICInput{
    public:
        vector<string> interpret(string input) override;
        virtual ~SearchInput() {}
};

#endif