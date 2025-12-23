#include "../commands/ICommand.h"
#include "../input/InputManager.h"
#include "IMenu.h"
#include <string>
#include <map>
#include <vector>
#include <iostream>

using namespace std;

class App {
    private:
        IMenu* menu;
        map<string, ICommand*> commands;
        InputManager* manager;
    public:
        App(IMenu* menu, map<string, ICommand*> commands, InputManager* manager) : menu(menu), commands(commands), manager(manager) {}

        void run() {
            while (true) {
                string input = menu->nextCommand();
                try {
                    vector<string> argv = manager->interpret(input);
                    string output = commands[argv[0]]->execute(argv.size(), argv);
                    menu->displayOutput(output);
                }
                catch (invalid_argument& e) {
                    menu->displayError(e.what());
                }
            }
        }
};
