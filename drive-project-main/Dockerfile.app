FROM gcc:latest

COPY . /usr/src/projectapp
WORKDIR /usr/src/projectapp

#add environment variable
ENV DRIVE_STORAGE_PATH=/usr/src/projectapp/storage_data

#create storage directory for StorageManager to write files to
RUN mkdir -p /usr/src/projectapp/storage_data


RUN g++ -o projectapp \
    src/core/main.cpp \
    src/core/app.cpp \
    src/core/CLIMenu.cpp \
    src/commands/AddCommand.cpp  \
    src/commands/GetCommand.cpp  \
    src/commands/SearchCommand.cpp  \
    src/storage/storageManager.cpp \
    src/compression/Compressor.cpp \
    src/input/AddInput.cpp  \
    src/input/GetInput.cpp  \
    src/input/SearchInput.cpp  \
    src/input/DeleteInput.cpp  \
    src/input/InputManager.cpp

CMD ["./projectapp"]