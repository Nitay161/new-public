#include <gtest/gtest.h>
#include <filesystem>
#include <sstream>
#include <iostream>
#include <vector>
#include "../src/storage/storageManager.h"
#include "../src/commands/AddCommand.h"
#include "../src/commands/SearchCommand.h" 
#include "../src/compression/Compressor.h"

namespace fs = std::filesystem;

class SearchCommandTest : public ::testing::Test {
    protected:
        std::string testPath;
        storageManager* sm;
        AddCommand* addCmd;
        SearchCommand* searchCmd;

        void SetUp() override {
            testPath = "temp_test_storage_search";

            // Clean old run and create test directory
            if (fs::exists(testPath)) {
                fs::remove_all(testPath);
            }
            fs::create_directory(testPath);

            sm = new storageManager(testPath);
            addCmd = new AddCommand(sm);
            searchCmd = new SearchCommand(sm);
        }

        void TearDown() override {
            delete sm;
            delete addCmd;
            delete searchCmd;
            fs::remove_all(testPath); 
        }
};

// Test finding a simple string in one file
TEST_F(SearchCommandTest, ExecuteSearchSingleMatch){
    std::vector<std::string> file1 = {"add", "file1.txt", "hello world"};
    std::vector<std::string> file2 = {"add", "file2.txt", "goodbye moonman"};
    
    addCmd->execute(file1.size(), file1);
    addCmd->execute(file2.size(), file2);

    std::vector<std::string> searchArgs = {"search", "world"};

    std::string o = searchCmd->execute(searchArgs.size(), searchArgs);

    EXPECT_EQ(o, "200 Ok\n\nfile1.txt");
}

// Test that no output is printed when text is not found
TEST_F(SearchCommandTest, ExecuteSearchNotFound){
    std::vector<std::string> file1 = {"add", "file1.txt", "some content"};
    addCmd->execute(file1.size(), file1);

    std::vector<std::string> searchArgs = {"search", "missing"};

    std::string o = searchCmd->execute(searchArgs.size(), searchArgs);

    EXPECT_EQ(o, "200 Ok\n\n");
}

// Test finding matches in multiple files
TEST_F(SearchCommandTest, ExecuteSearchMultipleMatches){
    std::vector<std::string> f1 = {"add", "a.txt", "two once"};
    std::vector<std::string> f2 = {"add", "b.txt", "one once"}; 
    std::vector<std::string> f3 = {"add", "c.txt", "two twice"};

    addCmd->execute(f1.size(), f1);
    addCmd->execute(f2.size(), f2);
    addCmd->execute(f3.size(), f3);

    std::vector<std::string> searchArgs = {"search", "two"};

    std::string o = searchCmd->execute(searchArgs.size(), searchArgs);

    // Verify both files are in the output (order may vary by OS)
    EXPECT_TRUE(o.find("a.txt") != std::string::npos);
    EXPECT_TRUE(o.find("c.txt") != std::string::npos);
    EXPECT_TRUE(o.find("b.txt") == std::string::npos);
}

// Test finding match in file name (Requirement update)
TEST_F(SearchCommandTest, ExecuteSearchMatchInFileName){
    std::vector<std::string> file1 = {"add", "find_me.txt", "hidden content"};
    addCmd->execute(file1.size(), file1);

    std::vector<std::string> searchArgs = {"search", "find_me"};

    std::string o = searchCmd->execute(searchArgs.size(), searchArgs);

    EXPECT_EQ(o, "200 Ok\n\nfind_me.txt");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}