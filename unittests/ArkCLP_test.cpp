//
//  ArkCLP_test.cpp
//  ArkLibrary
//
//  Created by Fangzhou Wang on 3/11/18.
//  Copyright © 2018 ArkLibrary. All rights reserved.
//

#include "ArkCLP_test.hpp"

TEST(ArkCLPTest, AddOptionSingleDash) {
    int argc = 2;
    const char **argv = new const char *[argc]();
    argv[0] = "program_name";
    argv[1] = "-num";
    ArkCLP clp = ArkCLP(argc, argv);
    EXPECT_TRUE(clp.GetOptionString("num") == "num");
}

TEST(ArkCLPTest, AddOptionMoreDashes) {
    int argc = 2;
    const char **argv = new const char *[argc]();
    argv[0] = "program_name";
    argv[1] = "-----num";
    ArkCLP clp = ArkCLP(argc, argv);
    EXPECT_TRUE(clp.GetOptionString("num") == "num");
}

TEST(ArkCLPTest, GetOptionWithBracket) {
    int argc = 2;
    const char **argv = new const char *[argc]();
    argv[0] = "program_name";
    argv[1] = "-num=5";
    ArkCLP clp = ArkCLP(argc, argv);
    EXPECT_TRUE(clp["num"] == "5");
}

TEST(ArkCLPTest, AddOptionWithValue) {
    int argc = 2;
    const char **argv = new const char *[argc]();
    argv[0] = "program_name";
    argv[1] = "-num=5";
    ArkCLP clp = ArkCLP(argc, argv);
    EXPECT_TRUE(clp.GetOptionString("num") == "5");
}

TEST(ArkCLPTest, AddOptionWithIntValue) {
    int argc = 2;
    const char **argv = new const char *[argc]();
    argv[0] = "program_name";
    argv[1] = "-num=5";
    ArkCLP clp = ArkCLP(argc, argv);
    int val = 0;
    clp.GetOptionInt("num", val);
    EXPECT_TRUE(val == 5);
}

TEST(ArkCLPTest, AddOptionWithIntValueException) {
    int argc = 2;
    const char **argv = new const char *[argc]();
    argv[0] = "program_name";
    argv[1] = "-num=x";
    ArkCLP clp = ArkCLP(argc, argv);
    int val = 0;
    EXPECT_THROW(clp.GetOptionInt("num", val), std::invalid_argument);
}

TEST(ArkCLPTest, AddValue) {
    int argc = 2;
    const char **argv = new const char *[argc]();
    argv[0] = "program_name";
    argv[1] = "num";
    ArkCLP clp = ArkCLP(argc, argv);
    EXPECT_TRUE(clp.GetValueString(1) == "num");
}
