#include "SocketMenu.h"

SocketMenu::SocketMenu(int fd){
    this->socket_fd = fd;
}


string SocketMenu::nextCommand() {

    string msg = "";
    //get data from the client
    char buffer[4096];
    int expected_data_len = sizeof(buffer);
    //receive data from client to buffer

    while (true) {
        int read_bytes = recv(socket_fd, buffer, expected_data_len, 0);
        if (read_bytes < 0) {
            // error
            throw runtime_error("Error reading from socket");
        }
        else if (read_bytes == 0) { //no more data from client
            throw runtime_error("Client disconnected");
        }

        else if (buffer[read_bytes - 1] == '\n' && read_bytes < expected_data_len) { //last part of the message
            msg.append(buffer, read_bytes); //append received message
            break;
        }
        else { //message might be larger then buffer
            msg.append(buffer, read_bytes); //append received message
        }
    }
    if (msg.empty()) {
        return "";
    }
    if (msg[msg.length() - 1] == '\n')
        msg = msg.substr(0, msg.length() - 1); //trim the last \n 

    return msg;
}

void SocketMenu::displayOutput(string text) {
    if (text.empty() || text.back() != '\n') {
        text.push_back('\n');
    }
    //send data to the client
    int bytes_sent = send(socket_fd, text.c_str(), text.length(), 0);
    if (bytes_sent < 0) {
        perror("error sending to socket");
    }
}

void SocketMenu::displayError(string text){
    if (text.empty() || text.back() != '\n') {
        text.push_back('\n');
    }
    //send error message to the client
    int bytes_sent = send(socket_fd, text.c_str(), text.length(), 0);
    if (bytes_sent < 0) {
        perror("error sending to socket");
    }
}