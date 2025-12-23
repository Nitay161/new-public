#include <gtest/gtest.h>
#include <iostream>
#include <thread>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include "../../src/client/CppClient.h"

// Functions for creating sockets to simulate server-client communication for tests.

// Creating server socket.
int create_server_socket(int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Error creating socket!");
    }

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(port);

    if (bind(sock, (sockaddr*)&sin, sizeof(sin)) < 0) {
        perror("Error binding socket!");
    }

    if (listen(sock, 5) < 0) {
        perror("Error listening to a socket!");
    }

    return sock;
}

// Creating client socket.
int create_client_socket(const char* ip, int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Error creating socket!");
    }

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip);
    sin.sin_port = htons(port);

    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("Error connecting to server!");
    }
    return sock;
}

// Sanity tests for sendInput function.
TEST(CppClientTest, SendingInputCorrectly) {
    const int PORT = 5555;

    // Create server socket
    int server_sock = create_server_socket(PORT);

    // Create client socket
    int client_sock = create_client_socket("127.0.0.1", PORT);

    // Accept connection
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int accepted_sock = accept(server_sock, (struct sockaddr*)&client_sin, &addr_len);

    if (accepted_sock < 0) {
        perror("Accept error!");
    }

    // Start client thread to simulate running on diiferent pc.
    const char* input = "Some input from user!!";
    int len = strlen(input);
    int sent_bytes;
    thread t(sendInput, client_sock, input, len, &sent_bytes);

    // Server reads data
    char buffer[1024] = {0};
    int bytes = recv(accepted_sock, buffer, sizeof(buffer), 0);

    EXPECT_STREQ(buffer, input);

    close(accepted_sock);
    close(server_sock);
    close(client_sock);

    t.join();
}

// Sanity tests for reciveInput function.
TEST(CppClientTest, ReciveInputCorrectly) {
    const int PORT = 6666;

    // Create server socket
    int server_sock = create_server_socket(PORT);

    // Create client socket
    int client_sock = create_client_socket("127.0.0.1", PORT);

    // Accept connection
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int accepted_sock = accept(server_sock, (struct sockaddr*)&client_sin, &addr_len);

    if (accepted_sock < 0) {
        perror("Accept error!");
    }

    // Server send some output.
    const char* output = "Some output from server!!";
    int len = strlen(output);
    int sent_bytes = send(accepted_sock, output, len, 0);

    // Start client thread to simulate running on diiferent pc.
    char buffer[1024] = {0};
    int recived_bytes;
    thread t(reciveOutput, client_sock, buffer, sizeof(buffer), &recived_bytes);

    t.join();
    EXPECT_STREQ(buffer, output);

    close(accepted_sock);
    close(server_sock);
    close(client_sock);

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}