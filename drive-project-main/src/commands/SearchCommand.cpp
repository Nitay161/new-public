#include "SearchCommand.h"
#include <iostream>
#include <vector>
#include <string>
#include "../compression/Compressor.h"

using namespace std;

// Constructor
SearchCommand::SearchCommand(storageManager* sm) {
    this->sm = sm;
}

string SearchCommand::execute(int argc, vector<string> argv) {
    if (argc < 2) throw std::invalid_argument("400 Bad Request");

    string searchContent = argv[1];
    vector<pair<string, string>> files = sm->listFilesWithContents();
    string output = ""; 

    for (const auto& file : files) {
        string fileName = file.first;
        bool match = false;

        if (fileName.find(searchContent) != string::npos) {
            match = true;
        }
        
        else {
            try {
                string originalContent = decompress(file.second);
                if (originalContent.find(searchContent) != string::npos) {
                    match = true;
                }
            } catch (...) {
                continue; 
            }
        }

        if (match) {
            output += fileName + " ";
        }
    }

    if (!output.empty()) {
        output.pop_back(); 
    }
    
    return "200 Ok\n\n" + output;
}