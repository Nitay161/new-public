#include "ClientHandler.h"

ClientHandler::ClientHandler(ClientInfo cInfo, storageManager* storageMgr){
    this->clientInfo = cInfo;
    this->storageMgr = storageMgr;
}

void ClientHandler::handle(){

    //Map of all the commands that can be executed.

    map<string, ICommand*> commands;

    // Add instances of the implemented commands here to the map.
    // The key for the commands should be their exact names.
    ICommand* addCommand = new AddCommand(storageMgr);
    commands["post"] = addCommand;
    ICommand* getCommand = new GetCommand(storageMgr);
    commands["get"] = getCommand;
    ICommand* searchCommand = new SearchCommand(storageMgr);
    commands["search"] = searchCommand;
    ICommand* deleteCommand = new DeleteCommand(storageMgr);
    commands["delete"] = deleteCommand;


    // The menu that will get input from the socket and display output to the socket.
    IMenu* menu = new SocketMenu(clientInfo.socketFd);

    // Map of all the inputs that can be for commands.
    map<string, ICInput*> inputs;
    ICInput* addInput = new AddInput();
    inputs["post"] = addInput;
    ICInput* getInput = new GetInput();
    inputs["get"] = getInput;
    ICInput* searchInput = new SearchInput();
    inputs["search"] = searchInput;
    ICInput* deleteInput = new DeleteInput();
    inputs["delete"] = deleteInput;

    InputManager* manager = new InputManager(inputs);

    // Creating App instance and running the app.
    App app1(menu, commands, manager);
    try {
        app1.run();
    } catch (runtime_error& e) {
        // Handle client disconnection or other runtime errors gracefully
        // For now, we just exit the handle function
    }

    // Delete all the instances of commands, inputs, menu, and manager here to free the memory.
    delete addCommand;
    delete getCommand;
    delete searchCommand;
    delete deleteCommand;
    delete menu;
    delete addInput;
    delete getInput;
    delete searchInput;
    delete deleteInput;
    delete manager;
}