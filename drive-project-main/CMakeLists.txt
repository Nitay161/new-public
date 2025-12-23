cmake_minimum_required(VERSION 3.10)

project(DriveProject)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(runTestsClient
    tests/client/CppClientTests.cpp
    src/client/CppClient.cpp
)
add_executable(runTestsAdd
    tests/AddCommandTests.cpp
    src/storage/storageManager.cpp
    src/commands/AddCommand.cpp
    src/compression/Compressor.cpp
)
add_executable(runTestsGet
    tests/GetCommandTests.cpp
    src/storage/storageManager.cpp
    src/commands/AddCommand.cpp
    src/commands/GetCommand.cpp
    src/compression/Compressor.cpp
)
add_executable(runTestsCompressor
    tests/CompressorTests.cpp
    src/compression/Compressor.cpp
)
add_executable(runTestsStorage
    tests/StorageManagerTests.cpp
    src/storage/storageManager.cpp
)
add_executable(runTestsSearch
    tests/SearchCommandTests.cpp
    src/storage/storageManager.cpp
    src/commands/AddCommand.cpp
    src/commands/SearchCommand.cpp
    src/compression/Compressor.cpp
)
add_executable(runTestsDeleteCommand
    tests/DeleteCommandTests.cpp
    src/storage/storageManager.cpp
    src/commands/DeleteCommand.cpp
)
add_executable(runTestsAddInput
    tests/input/AddInputTests.cpp
    src/input/AddInput.cpp
)
add_executable(runTestsGetInput
    tests/input/GetInputTests.cpp
    src/input/GetInput.cpp
)
add_executable(runTestsSearchInput
    tests/input/SearchInputTests.cpp
    src/input/SearchInput.cpp
)
add_executable(runTestsDeleteInput
    tests/input/DeleteInputTests.cpp
    src/input/DeleteInput.cpp
)
add_executable(runTestsInputManager
    tests/input/InputManagerTests.cpp
    src/input/InputManager.cpp
    src/input/DeleteInput.cpp
    src/input/SearchInput.cpp
    src/input/GetInput.cpp
    src/input/AddInput.cpp
)
add_executable(runTestsConstStorageDispatcher
    tests/ConstSmDispatcherTests.cpp
    src/storage/storageManager.cpp
    src/storage/ConstStorageDispatcher.cpp
)
add_executable(runTestsThreadPerClientDispatcher
    tests/ThreadPerClientTests.cpp
    src/server/ThreadPerClientDispatcher.cpp
    src/server/ClientHandler.cpp
    src/storage/storageManager.cpp
    src/input/InputManager.cpp
    src/core/SocketMenu.cpp
    src/commands/AddCommand.cpp
    src/commands/GetCommand.cpp
    src/commands/SearchCommand.cpp
    src/commands/DeleteCommand.cpp
    src/input/AddInput.cpp
    src/input/GetInput.cpp
    src/input/SearchInput.cpp
    src/input/DeleteInput.cpp
    src/compression/Compressor.cpp
)
add_executable(runTestsSocketMenu
    tests/SocketMenuTests.cpp
    src/core/SocketMenu.cpp
)
add_executable(runTestsClientHandler
    tests/ClientHandlerTests.cpp
    src/server/ClientHandler.cpp
    src/storage/storageManager.cpp
    src/input/InputManager.cpp
    src/core/SocketMenu.cpp
    src/commands/AddCommand.cpp
    src/commands/GetCommand.cpp
    src/commands/SearchCommand.cpp
    src/commands/DeleteCommand.cpp
    src/input/AddInput.cpp
    src/input/GetInput.cpp
    src/input/SearchInput.cpp
    src/input/DeleteInput.cpp
    src/compression/Compressor.cpp
)

target_link_libraries(runTestsClient gtest_main)
target_link_libraries(runTestsAdd gtest_main)
target_link_libraries(runTestsGet gtest_main)
target_link_libraries(runTestsCompressor gtest_main)
target_link_libraries(runTestsStorage gtest_main)
target_link_libraries(runTestsSearch gtest_main)
target_link_libraries(runTestsDeleteCommand gtest_main)
target_link_libraries(runTestsAddInput gtest_main)
target_link_libraries(runTestsGetInput gtest_main)
target_link_libraries(runTestsSearchInput gtest_main)
target_link_libraries(runTestsDeleteInput gtest_main)
target_link_libraries(runTestsInputManager gtest_main)
target_link_libraries(runTestsConstStorageDispatcher gtest_main)
target_link_libraries(runTestsThreadPerClientDispatcher gtest_main)
target_link_libraries(runTestsSocketMenu gtest_main)
target_link_libraries(runTestsClientHandler gtest_main)
