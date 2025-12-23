#include "storageManager.h"
#include <fstream>
#include <filesystem>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <mutex>

using namespace std;
namespace fs = std::filesystem;



//constructor
storageManager::storageManager(string path) {
    storagePath = path;
}


//returns the full path
string storageManager::getFullPath(string fileName) {
    return storagePath + "/" + fileName;
}

//checks if a file exists
bool storageManager::fileExists(string fileName) {
    std::lock_guard<std::mutex> lock(storageMutex);
    return fs::exists(getFullPath(fileName));
}

//create file and saves data to it
void storageManager::save(string fileName, string data) {

    std::lock_guard<std::mutex> lock(storageMutex);

    //if the file already exists then return an error
    if (fs::exists(getFullPath(fileName)))
        throw invalid_argument("File already exists");


    ofstream outFile(getFullPath(fileName));
    outFile << data;
    outFile.close();

}

//loads data from a file
string storageManager::load(string fileName){

    std::lock_guard<std::mutex> lock(storageMutex);

    //if the file already exists then return an error
    if (!fs::exists(getFullPath(fileName)))
        throw invalid_argument("File does not exist");
    
    string data;
    ifstream inFile(getFullPath(fileName));
    if (!inFile) {
        perror("Failed to open file");
        return "";
    }
    getline(inFile, data, '\0'); //reads the whole file
    return data;
}


//lists all files in the storage path
vector<string> storageManager::listFiles() {
    vector<string> files;

    std::lock_guard<std::mutex> lock(storageMutex);

    for (fs::directory_entry entry : fs::directory_iterator(storagePath)) {
        files.push_back(entry.path().filename().string());
    }
    std::sort(files.begin(), files.end());
    return files;
}



vector<pair<string, string>> storageManager:: listFilesWithContents(){
    vector<pair<string, string>> filesWithContents;

    std::lock_guard<std::mutex> lock(storageMutex);
    
    for (fs::directory_entry entry : fs::directory_iterator(storagePath)) {
        string name = entry.path().filename().string();
        ifstream inFile(getFullPath(name));
        if (!inFile) continue;
        string data;
        getline(inFile, data, '\0');
        filesWithContents.push_back({name, data});
    }

    std ::sort(filesWithContents.begin(), filesWithContents.end());
    return filesWithContents;
}

void storageManager:: deleteFile(string fileName){

    std::lock_guard<std::mutex> lock(storageMutex);

    if (fs::exists(getFullPath(fileName)) == false){
        throw invalid_argument("File does not exist");
    }

    fs::remove(getFullPath(fileName));
}
