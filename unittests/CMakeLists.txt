cmake_minimum_required(VERSION 3.9)

project(Test)

project(Example)

include(CTest)
enable_testing()

set(FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR /usr/local/mysql/)
include_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/include)
link_directories(${FULL_PATH_TO_MYSQL_CONNECTOR_CPP_DIR}/lib)

#add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)
add_subdirectory(./googletest EXCLUDE_FROM_ALL)

include_directories(../src)
set(test_SRCS
        ArkCLP_test.cpp ArkDBMySQL_test.cpp ArkDBMySQL_test.hpp)
add_executable(runUnitTests gtest.cpp ${test_SRCS} ArkDBMySQL_test.cpp ArkDBMySQL_test.hpp)
target_link_libraries(runUnitTests gtest gmock core)
add_test(runUnitTests runUnitTests) #included in all tutorials but I don't know what it actually does.
