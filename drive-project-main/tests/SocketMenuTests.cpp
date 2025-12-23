#include "../src/core/SocketMenu.h"
#include <gtest/gtest.h>
#include <sys/socket.h>
#include <string.h>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

class SocketMenuTests : public ::testing::Test {
    protected:
        int sv[2]; // socket pair for testing
        SocketMenu* socketMenu;

        void SetUp() override {
            // create a pair of connected sockets
            if (socketpair(AF_UNIX, SOCK_STREAM, 0, sv) == -1) {
                perror("socketpair");
            }
            socketMenu = new SocketMenu(sv[1]); // use one end for SocketMenu
        }

        void TearDown() override {
            close(sv[0]);
            close(sv[1]);
            delete socketMenu;
        }
};


void receiverFunction(SocketMenu* menu, string* outCmd) {
    *outCmd = menu->nextCommand();
}
// sends two partial pieces to socket
void senderFunction(int fd, const string& part1, const string& part2) {
    send(fd, part1.c_str(), part1.size(), 0);
    this_thread::sleep_for(chrono::milliseconds(50));
    send(fd, part2.c_str(), part2.size(), 0);
}
void senderFunctionSingle(int fd, const string& msg) {
    send(fd, msg.c_str(), msg.size(), 0);
}
// reads exactly one message from fd
void receiveData(int fd, string* out) {
    char buffer[1024] = {0};
    int bytes = recv(fd, buffer, sizeof(buffer), 0);
    if (bytes > 0) {
        out->assign(buffer, bytes);
    }
}
// sender for displayOutput
void senderOutput(SocketMenu* menu, const string& msg) {
    this_thread::sleep_for(chrono::milliseconds(30));
    menu->displayOutput(msg);
}
// sender for displayError
void senderError(SocketMenu* menu, const string& msg) {
    this_thread::sleep_for(chrono::milliseconds(30));
    menu->displayError(msg);
}


// test nextCommand with regular data reception 
TEST_F(SocketMenuTests, NextCommandRegular) {

    string message = "First Command\n";
    string expected = "First Command";


    string received;

    // receiver thread
    thread receiver(receiverFunction, socketMenu, &received);

    // allow receiver to block on recv()
    this_thread::sleep_for(chrono::milliseconds(50));

    // sender thread
    thread sender(senderFunctionSingle, sv[0], message);

    sender.join();
    receiver.join();

    EXPECT_EQ(received, expected);
}



//test nextCommand with mixed reads
TEST_F(SocketMenuTests, NextCommandMixed) {

    string part1 = "First Com";
    string part2 = "mand\n"; 
    string expected = "First Command";

    string received;

    // receiver thread
    thread receiver(receiverFunction, socketMenu, &received);

    // allow receiver to block on recv()
    this_thread::sleep_for(chrono::milliseconds(50));

    // sender thread
    thread sender(senderFunction, sv[0], part1, part2);

    sender.join();
    receiver.join();

    EXPECT_EQ(received, expected);
}



// test displayOutput sends data correctly
TEST_F(SocketMenuTests, DisplayOutputSendsDataCorrectly) {
    string outputMessage = "Output from SocketMenu\n\n";
    string received;

    //receiver
    thread receiver(receiveData, sv[0], &received);

    //sender
    thread sender(senderOutput, socketMenu, outputMessage);

    sender.join();
    receiver.join();

    EXPECT_EQ(received, outputMessage);
}


//test displayError sends data correctly
TEST_F(SocketMenuTests, DisplayErrorSendsDataCorrectly) {
    string errorMessage = "Error from SocketMenu\n\n";
    string received;

    //receiver
    thread receiver(receiveData, sv[0], &received);

    //sender
    thread sender(senderError, socketMenu, errorMessage);

    sender.join();
    receiver.join();

    EXPECT_EQ(received, errorMessage);
}


