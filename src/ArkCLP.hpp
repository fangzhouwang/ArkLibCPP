//
//  ArkCLP.hpp
//  ArkLibrary
//
//  Created by Fangzhou Wang on 3/11/18.
//  Copyright © 2018 ArkLibrary. All rights reserved.
//

#ifndef ArkCLP_hpp
#define ArkCLP_hpp

#include <map>
#include <string>
#include <vector>

#define __ArkCLP_VERSION "1.0.0"
#define __ArkCLP_MAXSTRLEN  12800

class ArkCLP {
    const int argc_;
    const char **argv_;
    std::map<std::string, std::string> options_;
    std::vector<std::string> values_;

    ArkCLP();   // calling default constructor is not allowed
    void ParseCommandLine();
    void AddOption(const char *arg);
    void AddValue(const char *arg);

public:
    ArkCLP(int argc_, char **argv);
    ArkCLP(int argc_, const char **argv);
    std::string GetOptionString(std::string key);
    std::string GetValueString(int idx);
    bool GetOptionInt(std::string key, int &val);
    std::string operator[](std::string key);
    std::string operator[](int idx);
};

#endif /* ArkCLP_hpp */
