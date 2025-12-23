#include <gtest/gtest.h>
#include "../../src/input/AddInput.h"

// Sanity tests for AddInput interpret function.
TEST(AddInputTest, InterpretingAddInputCorrectly) {
    ICInput* add = new AddInput();
    vector<string> args1 = {"post", "file1", "some text for f1"};
    EXPECT_EQ(add->interpret("post file1 some text for f1"), args1);

    vector<string> args2 = {"post", "file2", " some   other  text"};
    EXPECT_EQ(add->interpret("PoSt file2  some   other  text"), args2);
}

// Negative tests for AddInput interpret function. The text should be in add command format.
TEST(AddInputTest, InvalidInputFormat) {
    ICInput* add = new AddInput();
    // The file name cannot have spaces so this is illegal.
    EXPECT_THROW(add->interpret("post  file some text"), invalid_argument);
    // The input should contain text after the file.
    EXPECT_THROW(add->interpret("post file"), invalid_argument);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}