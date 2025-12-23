#include <string>
#include <map>
#include <limits>
#include <cstdlib>
#include "../commands/ICommand.h"
#include "../commands/AddCommand.h"
#include "../commands/GetCommand.h"
#include "../commands/SearchCommand.h"
#include "IMenu.h"
#include "app.cpp"
#include "CLIMenu.cpp"
#include "../storage/storageManager.h"
#include "../input/ICInput.h"
#include "../input/InputManager.h"
#include "../input/AddInput.h"
#include "../input/GetInput.h"
#include "../input/SearchInput.h"
#include "../input/DeleteInput.h"

using namespace std;

int main() {    

    //read environment variable
    const char* envPath = getenv("DRIVE_STORAGE_PATH");
    if (!envPath) {
        cerr << "Error: Environment variable DRIVE_STORAGE_PATH not set." << endl;
        return 1;
    }

    //create storage manager instance with the retrieved path
    storageManager* sm = new storageManager(string(envPath));

    // Map of all the commands that can be executed.
    map<string, ICommand*> commands;

    // Add instances of the implemented commands here to the map.
    // The key for the commands should be their exact names.
    ICommand* addCommand = new AddCommand(sm);
    commands["add"] = addCommand;
    ICommand* getCommand = new GetCommand(sm);
    commands["get"] = getCommand;
    ICommand* searchCommand = new SearchCommand(sm);
    commands["search"] = searchCommand;


    // The menu that will get input from the CLI.
    IMenu* menu = new CLIMenu();

    // Map of all the inputs that can be for commands.
    map<string, ICInput*> inputs;
    ICInput* addInput = new AddInput();
    inputs["add"] = addInput;
    ICInput* getInput = new GetInput();
    inputs["get"] = getInput;
    ICInput* searchInput = new SearchInput();
    inputs["search"] = searchInput;
    ICInput* deleteInput = new DeleteInput();
    inputs["delete"] = deleteInput;

    InputManager* manager = new InputManager(inputs);

    // Creating App instance and running the app.
    App app1(menu, commands, manager);
    app1.run();

    // Delete all the instances of commands here to free the memory.
    delete addCommand;
    delete getCommand;
    delete searchCommand;

    delete menu;

    delete addInput;
    delete getInput;
    delete searchInput;
    delete deleteInput;

    return 0;
}