#include <gtest/gtest.h>
#include <filesystem>
#include "../src/storage/storageManager.h"
#include "../src/storage/ConstStorageDispatcher.h"
#include "../src/server/ClientInfo.h"
#include <thread>
#include <atomic>
#include <mutex>

namespace fs = std::filesystem;

class ConstStorageDispatcherTest : public ::testing::Test {
    protected:
        std::string testPath;
        storageManager* sm;
        ConstStorageDispatcher* dispatcher;

        //set up a temporary dierectory in the tests folder for testing
        void SetUp() override {
            testPath = "temp_test_storage";

            // clean old & create test directory
            if (fs::exists(testPath)) {
                fs::remove_all(testPath);
            }
            fs::create_directory(testPath);
            // initialize storageManager for the tests
            sm = new storageManager(testPath);
            // create dispatcher
            dispatcher = new ConstStorageDispatcher(sm);
        }


        // clean up the tests directory after tests
        void TearDown() override {
            delete dispatcher;
            delete sm;
            fs::remove_all(testPath); 
        }
};

//sanity test for getStorageManager function
TEST_F(ConstStorageDispatcherTest, GetStorageManager){
    
    ClientInfo clientInfo; // create a ClientInfo object as required by the function
    storageManager* retrievedSm = dispatcher->getStorageManager(clientInfo);
    // compares the pointers. succeeds only if dispatcher returns the original storageManager*
    EXPECT_EQ(retrievedSm, sm);
}