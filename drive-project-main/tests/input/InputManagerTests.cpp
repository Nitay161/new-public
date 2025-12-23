#include <gtest/gtest.h>
#include "../../src/input/InputManager.h"
#include "../../src/input/AddInput.h"
#include "../../src/input/GetInput.h"
#include "../../src/input/SearchInput.h"
#include "../../src/input/DeleteInput.h"

// Sanity tests for InputManagerInput interpret function.
TEST(InputManagerTest, InputManagerInterpretsCorrectly) {
    // Map of all the inputs that can be for commands.
    map<string, ICInput*> inputs;
    ICInput* addInput = new AddInput();
    inputs["post"] = addInput;
    ICInput* getInput = new GetInput();
    inputs["get"] = getInput;
    ICInput* searchInput = new SearchInput();
    inputs["search"] = searchInput;
    ICInput* deleteInput = new DeleteInput();
    inputs["delete"] = deleteInput;

    InputManager* manager = new InputManager(inputs);
    vector<string> args1 = {"post", "file1", "some text"};
    EXPECT_EQ(manager->interpret("PosT file1 some text"), args1);
    vector<string> args2 = {"get", "file1"};
    EXPECT_EQ(manager->interpret("gEt file1"), args2);
    vector<string> args3 = {"search", "some text"};
    EXPECT_EQ(manager->interpret("sEarch some text"), args3);
    vector<string> args4 = {"delete", "file1"};
    EXPECT_EQ(manager->interpret("dEleTe file1"), args4);

    delete addInput;
    delete getInput;
    delete searchInput;
    delete deleteInput;
}

// Negative tests for InputManagerInput interpret function. The text should be a legal command.
TEST(InputManagerTest, InvalidInputFormat) {
    // Map of all the inputs that can be for commands.
    map<string, ICInput*> inputs;
    ICInput* addInput = new AddInput();
    inputs["post"] = addInput;
    ICInput* getInput = new GetInput();
    inputs["get"] = getInput;
    ICInput* searchInput = new SearchInput();
    inputs["search"] = searchInput;
    ICInput* deleteInput = new DeleteInput();
    inputs["delete"] = deleteInput;

    InputManager* manager = new InputManager(inputs);
    // Command that does not exist.
    EXPECT_THROW(manager->interpret("nonexist"), invalid_argument);
    EXPECT_THROW(manager->interpret("nonexist other input"), invalid_argument);
    // Wrong format for existing commands.
    EXPECT_THROW(manager->interpret("post file1"), invalid_argument);
    EXPECT_THROW(manager->interpret("add  file1 text"), invalid_argument);
    EXPECT_THROW(manager->interpret("get  file1"), invalid_argument);
    EXPECT_THROW(manager->interpret("get"), invalid_argument);
    EXPECT_THROW(manager->interpret("search"), invalid_argument);
    EXPECT_THROW(manager->interpret("delete  file1"), invalid_argument);
    EXPECT_THROW(manager->interpret("delete"), invalid_argument);

    delete addInput;
    delete getInput;
    delete searchInput;
    delete deleteInput;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}