#include "IMenu.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class CLIMenu : public IMenu {
    public:
        CLIMenu() {}
        // This function gets the command from the user returns it.
        string nextCommand() {
            // Get input from user.
            string input;
            getline(cin, input);
            return input;
        }
        // This function displays the output. For the CLI menu it just prints to CLI.
        void displayOutput(string text) {
            cout << text << endl;
        }
        // This function displays an error. For the CLI menu it just ignores the error.
        void displayError(string text) {
            return;
        }
};
