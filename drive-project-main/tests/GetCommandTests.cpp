#include <gtest/gtest.h>
#include <filesystem>
#include <sstream>
#include <iostream>
#include <vector>
#include "../src/storage/storageManager.h"
#include "../src/commands/AddCommand.h"
#include "../src/commands/GetCommand.h"
#include "../src/compression/Compressor.h"



namespace fs = std::filesystem;

class GetCommandTest : public ::testing::Test {
    protected:
        std::string testPath;
        storageManager* sm;
        AddCommand* addCmd;
        GetCommand* getCmd;

        //set up a temporary directory in the tests folder for testing
        void SetUp() override {
            testPath = "temp_test_storage";

            // clean old & create test directory
            if (fs::exists(testPath)) {
                fs::remove_all(testPath);
            }
            fs::create_directory(testPath);
            // initialize storageManager for the tests
            sm = new storageManager(testPath);
            addCmd = new AddCommand(sm);
            getCmd = new GetCommand(sm);
        }

        // clean up the tests directory after tests
        void TearDown() override {
            delete sm;
            delete addCmd;
            delete getCmd;
            fs::remove_all(testPath); 
        }
};

//sanity test for GetCommand execute function
TEST_F(GetCommandTest, ExecuteGetCommand){
    //firstly add file using AddCommand
    std::vector<std::string> arr1 = {"add", "file1.txt", "texaaaat anbbbbd moccccre"};
    std::vector<std::string> arr2 = {"add", "file2.txt", "texaaaat   anbbbbd m  occccre"};
    addCmd->execute(arr1.size(), arr1);
    addCmd->execute(arr2.size(), arr2);

    //make argv
    std::vector<std::string> arr = {"get", "file1.txt"};
    std::vector<std::string> arrb = {"get", "file2.txt"};

    std::string o1 = getCmd->execute(arr.size(), arr);
    std::string o2 = getCmd->execute(arrb.size(), arrb);

    //verify returend output
    EXPECT_EQ(o1, "200 Ok\n\ntexaaaat anbbbbd moccccre");
    EXPECT_EQ(o2, "200 Ok\n\ntexaaaat   anbbbbd m  occccre");
    
}
    
//test getting a file which doesnt exist
TEST_F(GetCommandTest, ExecuteGetCommandInsufficientArgs){
    std::vector<std::string> arr1 = {"get", "file1.txt"};

    EXPECT_THROW(getCmd->execute(arr1.size(), arr1), std::invalid_argument);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}