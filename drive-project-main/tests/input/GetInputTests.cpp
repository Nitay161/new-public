#include <gtest/gtest.h>
#include "../../src/input/GetInput.h"

// Sanity tests for GetInput interpret function.
TEST(GetInputTest, InterpretingGetInputCorrectly) {
    ICInput* get = new GetInput();
    vector<string> args1 = {"get", "file1"};
    EXPECT_EQ(get->interpret("get file1"), args1);

    vector<string> args2 = {"get", "file23_other"};
    EXPECT_EQ(get->interpret("GeT file23_other"), args2);
}

// Negative tests for GetInput interpret function. The text should be in get command format.
TEST(GetInputTest, InvalidInputFormat) {
    ICInput* get = new GetInput();
    // The file name cannot have spaces so this is illegal.
    EXPECT_THROW(get->interpret("get  file"), invalid_argument);
    // The input should not contain text after the file.
    EXPECT_THROW(get->interpret("get file with text"), invalid_argument);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}