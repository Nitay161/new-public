#include <gtest/gtest.h>
#include "../../src/input/SearchInput.h"

// Sanity tests for SearchInput interpret function.
TEST(SearchInputTest, InterpretingSearchInputCorrectly) {
    ICInput* search = new SearchInput();
    vector<string> args1 = {"search", "some text"};
    EXPECT_EQ(search->interpret("search some text"), args1);

    vector<string> args2 = {"search", "  other   text"};
    EXPECT_EQ(search->interpret("SeaRch   other   text"), args2);
}

// Negative tests for SearchInput interpret function. The text should be in search command format.
TEST(SearchInputTest, InvalidInputFormat) {
    ICInput* search = new SearchInput();
    // The input should have some text after command name.
    EXPECT_THROW(search->interpret("search"), invalid_argument);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}