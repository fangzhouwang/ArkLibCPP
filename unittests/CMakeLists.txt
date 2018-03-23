cmake_minimum_required(VERSION 3.9)

project(Test)

project(Example)

include(CTest)
enable_testing()

#add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)
add_subdirectory(./googletest EXCLUDE_FROM_ALL)

include_directories(../src)
set(test_SRCS
        ArkCLP_test.cpp)
add_executable(runUnitTests gtest.cpp ${test_SRCS})
target_link_libraries(runUnitTests gtest gmock core)
add_test(runUnitTests runUnitTests) #included in all tutorials but I don't know what it actually does.
