#ifndef IMENU_H
#define IMENU_H

#include <string>

using namespace std;

class IMenu {
    public:
        // This function gets the command from the user and return the arguments in array of strings.
        virtual string nextCommand() = 0;
        // This function displays athe output.
        virtual void displayOutput(string text) = 0;
        // This function displays an error.
        virtual void displayError(string text) = 0;
        virtual ~IMenu() {}
};

#endif