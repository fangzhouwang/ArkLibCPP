//
//  ArkCLP_test.hpp
//  ArkLibrary
//
//  Created by Fangzhou Wang on 3/11/18.
//  Copyright © 2018 ArkLibrary. All rights reserved.
//

#ifndef ArkCLP_test_hpp
#define ArkCLP_test_hpp

#include <gtest/gtest.h>
#include "ArkCLP.hpp"

class ArkCLPTest : public ::testing::Test {
protected:
    
    ArkCLPTest() {
        // You can do set-up work for each test here.
    }
    
    virtual ~ArkCLPTest() {
        // You can do clean-up work that doesn't throw exceptions here.
    }
    
    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:
    
    virtual void SetUp() {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }
    
    virtual void TearDown() {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }
    
    // Objects declared here can be used by all tests in the test case for Foo.
};

#endif /* ArkCLP_test_hpp */
