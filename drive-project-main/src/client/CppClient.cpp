#include "CppClient.h"

using namespace std;

void sendInput(int socket, const char* input, int len, int* bytes) {
    *bytes = send(socket, input, len, 0);
}

void reciveOutput(int socket, char buffer[], int expected_len, int* bytes) {
    *bytes = recv(socket, buffer, expected_len, 0);
}