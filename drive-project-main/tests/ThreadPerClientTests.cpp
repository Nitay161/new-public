#include <gtest/gtest.h>
#include "../src/server/ThreadPerClientDispatcher.h"
#include "../src/server/ClientHandler.h"
#include <vector>

// fake handler for testing ThreadPerClientDispatcher
class FakeHandler : public ClientHandler {
    public:
        FakeHandler(bool* ran, bool* destroyed)
            : ClientHandler(ClientInfo("127.0.0.1", 0), nullptr), ranFlag(ran), destroyedFlag(destroyed) {}

        void handle() override {
            // Called inside the new thread
            *ranFlag = true;
        }

        ~FakeHandler() override {
            *destroyedFlag = true;
        }

    private:
        bool* ranFlag;
        bool* destroyedFlag;
};

TEST(ThreadPerClientDispatcherTest, HandlerRunsAndIsDeleted) {
    ThreadPerClientDispatcher dispatcher;

    int clientNum = 5;

    //vector to store results for each client
    std::vector<std::pair<bool, bool>> results = {};
    for (int i = 0; i < clientNum; i++)
        results.push_back({false, false});

    //create fake handlers for each client
    std::vector<ClientHandler*> handlers = {};
    for (int i = 0; i < clientNum; i++) {
        handlers.push_back(new FakeHandler(&results[i].first, &results[i].second));
    }

    //dispatch each handler
    for (int i = 0; i < clientNum; i++) {
        dispatcher.clientDispatch(handlers[i]);
    }
    
    //wait for threads to run
    std::this_thread::sleep_for(std::chrono::milliseconds(80));

    bool run = true, destroyed = true;
    // The handler should have run
    for (int i = 0; i < clientNum; i++) {
        run &= results[i].first;
        destroyed &= results[i].second;
    }
    EXPECT_TRUE(run);
    EXPECT_TRUE(destroyed);
}
