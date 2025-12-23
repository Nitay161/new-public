#include <gtest/gtest.h>
#include <filesystem>
#include <vector>
#include "../src/storage/storageManager.h"
#include "../src/commands/DeleteCommand.h"

namespace fs = std::filesystem;

class DeleteCommandTest : public ::testing::Test {
    protected:
        std::string testPath;
        storageManager* sm;
        DeleteCommand* deleteCmd;

        void SetUp() override {
            testPath = "temp_test_storage_delete";
            if (fs::exists(testPath)) {
                fs::remove_all(testPath);
            }
            fs::create_directory(testPath);
            sm = new storageManager(testPath);
            deleteCmd = new DeleteCommand(sm);
        }

        void TearDown() override {
            delete sm;
            delete deleteCmd;
            fs::remove_all(testPath); 
        }
};

// Test valid file deletion
TEST_F(DeleteCommandTest, ExecuteDeleteValidFile){
    std::string fileName = "file1.txt";
    sm->save(fileName, "some data"); // Pre-create file
    
    std::vector<std::string> args = {"delete", fileName};
    std::string output = deleteCmd->execute(args.size(), args);

    EXPECT_EQ(output, "204 No Content");
    EXPECT_FALSE(sm->fileExists(fileName));
}

// Test deleting a file that does not exist (Should return 404)
TEST_F(DeleteCommandTest, ExecuteDeleteNonExistentFile){
    std::vector<std::string> args = {"delete", "ghost_file.txt"};

    // Based on your architecture, commands throw exceptions for errors
    try {
        deleteCmd->execute(args.size(), args);
        FAIL() << "Expected std::invalid_argument";
    } catch(const std::invalid_argument& e) {
        EXPECT_STREQ(e.what(), "404 Not Found");
    }
}

// Test invalid arguments (Should return 400)
TEST_F(DeleteCommandTest, ExecuteDeleteInsufficientArgs){
    std::vector<std::string> args = {"delete"}; // Missing filename

    try {
        deleteCmd->execute(args.size(), args);
        FAIL() << "Expected std::invalid_argument";
    } catch(const std::invalid_argument& e) {
        EXPECT_STREQ(e.what(), "400 Bad Request");
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}