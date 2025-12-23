#ifndef STORAGEMANAGER_H
#define STORAGEMANAGER_H


#include <string>
#include <vector>
#include <mutex>
using namespace std;

class storageManager {
    private:
        string storagePath;
        mutex storageMutex;

        
    public:
        // constructor
        storageManager(string path);        
        // this function create a file named fileName and write the received data in it
        void save(string fileName, string data);
        // this function load the content of the file named fileName and return it as a string
        string load(string fileName);
        // this function list all files in the storage path and return them as a vector of strings
        vector<string> listFiles();
        // this function checks if a file named fileName exists in the storage path
        bool fileExists(string fileName);
        // this function returns the full path of a file named fileName in the storage path
        string getFullPath(string fileName);
        // this function lists all files and their contents (snapshot)
        vector<pair<string, string>> listFilesWithContents();
        // this function deletes the file named fileName from the storage path
        void deleteFile(string fileName);
};

#endif