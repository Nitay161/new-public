import sys
import socket

# This function sends the input through the socket.
def sendInput(socket, input):
    socket.send(bytes(input, 'utf-8'))

# This function recives and return the output from the server.
def reciveOutput(socket, size):
    return socket.recv(size)

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("Not enough argumets!")
        exit(1)

    # Creating soxket.
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # Getting command line arguments and connecting to the server.
    server_ip = sys.argv[1]
    server_port = int(sys.argv[2])
    s.connect((server_ip, server_port))

    # Reading input.
    msg = input()
    msg += "\n"  # Adding newline to mark end of command.
    while True:
        # Sending to server.
        sendInput(s, msg)
        # Reciving output.
        data = reciveOutput(s, 4096)
        # Printing.
        print(data.decode('utf-8'))
        # Reading next input.
        msg = input()
        msg += "\n"  # Adding newline to mark end of command.

    s.close()