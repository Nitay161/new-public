#include <gtest/gtest.h>
#include <filesystem>
#include "../src/storage/storageManager.h"
#include <thread>
#include <atomic>
#include <mutex>

namespace fs = std::filesystem;

class StorageManagerTest : public ::testing::Test {
    protected:
        std::string testPath;
        storageManager* sm;

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
        }


        // clean up the tests directory after tests
        void TearDown() override {
            delete sm;
            fs::remove_all(testPath); 
        }
};


//sanity tests for save, load and fileExists functions
TEST_F(StorageManagerTest, SaveLoadExistsFile){
    std::string fileName = "testfile.txt";
    std::string testData = "awecsu4940j1jd7dmdwi002jdm3";

    sm->save(fileName, testData);
    std::string loadedData = sm->load(fileName);

    EXPECT_EQ(testData, loadedData);
    EXPECT_EQ(sm->fileExists(fileName), true);
}

//sanity test for listFiles function
TEST_F(StorageManagerTest, ListFiles){
    std::vector<std::string> filesNames = {"file1.txt", "file2.txt", "file3.txt"};
    std::string testData = "sampledata12345";

    for(std::string name : filesNames){
        sm->save(name, testData);
    }
    std::vector<std::string> listedFiles = sm->listFiles();

    EXPECT_EQ(listedFiles.size(), filesNames.size());
    EXPECT_EQ(filesNames, listedFiles);
}

//negative test for load function when file does not exist
TEST_F(StorageManagerTest, LoadNonExistentFile){
    std::string nonExistentFile = "nofile.txt";
    EXPECT_THROW(sm->load(nonExistentFile), std::invalid_argument);
}

//negative test for fileExists function when file doesnt exist
TEST_F(StorageManagerTest, FileDoesntExist){
    std::string nonExistentFile = "nofile.txt";
    EXPECT_EQ(sm->fileExists(nonExistentFile), false);
}

//negative test for listFiles function when there are no files
TEST_F(StorageManagerTest, ListFilesWhenNoFiles){
    std::vector<std::string> listedFiles = sm->listFiles();
    EXPECT_EQ(listedFiles.empty(), true);
}

// sanity test for deleteFile function
TEST_F(StorageManagerTest, DeleteFile){
    std::string fileName = "file1.txt";
    std::string testData = "data to delete test";

    sm->save(fileName, testData);
    EXPECT_EQ(sm->fileExists(fileName), true); //checks if file really saved

    sm->deleteFile(fileName);
    EXPECT_EQ(sm->fileExists(fileName), false); // checkes if file really deleted

    sm->save(fileName, testData);
    EXPECT_EQ(sm->fileExists(fileName), true); //checks if file can be saved again after being deleted
}

// negative test for deleteFile function when file does not exist
TEST_F(StorageManagerTest, DeleteNonExistentFile){
    std::string nonExistentFile = "file1.txt";

    EXPECT_THROW(sm->deleteFile(nonExistentFile), std::invalid_argument);
}

//sanity tests for listFilesWithContents function
TEST_F(StorageManagerTest, ListFilesWithContents){
    std::vector<std::pair<std::string, std::string>> filesData = {
        {"file1", "data1"},
        {"file2", "data2"},
        {"file3", "data3"}
    };

    for(auto& fd : filesData){
        sm->save(fd.first, fd.second);
    }

    auto listedFilesData = sm->listFilesWithContents();

    EXPECT_EQ(listedFilesData.size(), filesData.size());
    EXPECT_EQ(filesData, listedFilesData);
}

//negative test for listFilesWithContents function when there are no files
TEST_F(StorageManagerTest, ListFilesWithContentsWhenNoFiles){
    std::vector<std::pair<std::string, std::string>> listedFilesData = sm->listFilesWithContents();
    EXPECT_EQ(listedFilesData.empty(), true);
}

//multiple threads trying to save the same file only one should succeed
TEST_F(StorageManagerTest, ConcurrentSaveSameFile) {
    const int numThreads = 20;
    std::vector<std::thread> threads;
    int successCount = 0;
    std::mutex successMutex;

    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back([this, &successCount, &successMutex]() {
            try {
                sm->save("shared.txt", "hello");
                {
                    std::lock_guard<std::mutex> lock(successMutex);
                    successCount++;
                }
            } catch (...) {
                // expected: save must throw if someone else wrote first
            }
        });
    }

    for (std::thread& t : threads) 
        t.join();


    EXPECT_EQ(successCount, 1);      // ONLY ONE CAN SUCCEED
    EXPECT_TRUE(sm->fileExists("shared.txt"));
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}