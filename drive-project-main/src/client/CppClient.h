#ifndef CPPCLIENT_H
#define CPPCLIENT_H

#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

// This function sends the input through the socket.
void sendInput(int socket, const char* input, int len, int* bytes);

// This function recives the output through the socket.
void reciveOutput(int socket, char buffer[], int expected_len, int* bytes);

#endif