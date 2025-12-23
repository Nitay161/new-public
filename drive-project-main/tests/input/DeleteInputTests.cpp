#include <gtest/gtest.h>
#include "../../src/input/DeleteInput.h"

// Sanity tests for DeleteInput interpret function.
TEST(DeleteInputTest, InterpretingDeleteInputCorrectly) {
    ICInput* deleteI = new DeleteInput();
    vector<string> args1 = {"delete", "file1"};
    EXPECT_EQ(deleteI->interpret("delete file1"), args1);

    vector<string> args2 = {"delete", "file23_other"};
    EXPECT_EQ(deleteI->interpret("DelEte file23_other"), args2);
}

// Negative tests for DeleteInput interpret function. The text should be in delete command format.
TEST(DeleteInputTest, InvalidInputFormat) {
    ICInput* deleteI = new DeleteInput();
    // The file name cannot have spaces so this is illegal.
    EXPECT_THROW(deleteI->interpret("delete  file"), invalid_argument);
    // The input should not contain text after the file.
    EXPECT_THROW(deleteI->interpret("delete file with text"), invalid_argument);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}