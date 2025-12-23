#include <gtest/gtest.h>
#include <sys/socket.h>
#include <string.h>
#include <vector>
#include <thread>
#include "../src/server/ClientHandler.h"
#include "../src/server/ClientInfo.h"
#include "../src/storage/storageManager.h"
#include <filesystem>
using namespace std;

class ClientHandlerTests : public ::testing::Test {
    protected:
        int sv[2]; // socket pair for testing. sv[0] for client, sv[1] for server
        ClientHandler* clientHandler;
        ClientInfo clientInfo;
        storageManager* sm;
        string testPath;



        void SetUp() override {
            // create a pair of connected sockets
            if (socketpair(AF_UNIX, SOCK_STREAM, 0, sv) == -1) {
                perror("socketpair");
            }

            // set up a temporary directory for storageManager
            testPath = "temp_test_storage";
            // clean old & create test directory
            if (filesystem::exists(testPath)) {
                filesystem::remove_all(testPath);
            }
            filesystem::create_directory(testPath);
            // setup storage manager
            sm = new storageManager(testPath);

            //client handler setup
            clientInfo = ClientInfo(); 
            clientInfo.socketFd = sv[1]; // server side socket

            clientHandler = new ClientHandler(clientInfo, sm);
        }

        void TearDown() override {
            //the client socket already closed in the client function
            close(sv[1]);
            delete clientHandler;
            delete sm;
            filesystem::remove_all(testPath);
        }
};

void loopedClientFunction(int fd, const vector<string>& messages, vector<string>& responses, int numLoops) {
    for (int i = 0; i < numLoops; i++) {

        send(fd, messages[i].c_str(), messages[i].size(), 0);

        char buffer[1024] = {0};
        int bytes = recv(fd, buffer, sizeof(buffer), 0);

        if (bytes <= 0) {
            responses[i] = "";  // assign something to avoid out-of-bounds
            break;
        }

        responses[i].assign(buffer, bytes);
    }

    // terminate connection so handler exits
    shutdown(fd, SHUT_RDWR);
    close(fd);
}

void runClientHandler(ClientHandler* handler) {
    handler->handle();
}


TEST_F(ClientHandlerTests, HandleCommandsCombined) {
    // prepare commands and expected responses
    vector<string> commands = {
        "post file1 Hello World\n",
        "get file1\n",
        "search World\n",
        "search nonexisting\n"
    };
    vector<string> expectedResponses = {
        "201 Created\n",
        "200 Ok\n\nHello World\n",
        "200 Ok\n\nfile1\n",
        "200 Ok\n\n"
    };

    int numLoops = commands.size();
    vector<string> responses(numLoops);

    // start client thread
    thread clientThread(loopedClientFunction, sv[0], commands, ref(responses), numLoops);

    // run client handler in main thread
    thread handlerThread(runClientHandler, clientHandler);

    // wait for client thread to finish
    clientThread.join();
    handlerThread.join();

    // verify responses
    for (int i = 0; i < numLoops; i++) {
        EXPECT_EQ(responses[i], expectedResponses[i]);
    }
}
