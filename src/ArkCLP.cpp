//
//  ArkCLP.cpp
//  ArkLibrary
//
//  Created by Fangzhou Wang on 3/11/18.
//  Copyright © 2018 ArkLibrary. All rights reserved.
//

#include "ArkCLP.hpp"

ArkCLP::ArkCLP(int argc, char ** argv) :
ArkCLP(argc, (const char **) argv) {
}

ArkCLP::ArkCLP(int argc, const char ** argv) :
argc_(argc), argv_(argv) {
    ParseCommandLine();
}

std::string ArkCLP::GetOptionString(std::string key) {
    if (options_.find(key) != options_.end()) {
        return options_[key];
    }
    return "";
}

std::string ArkCLP::GetValueString(int idx) {
    if (idx < values_.size()) {
        return values_[idx];
    }
    return "";
}

std::string ArkCLP::operator[](int idx) {
    return GetValueString(idx);
}

std::string ArkCLP::operator[](std::string key) {
    return GetOptionString(key);
}

bool ArkCLP::GetOptionInt(std::string key, int & val) {
    if (options_.find(key) != options_.end()) {
        val = std::stoi(options_[key]);
        return true;
    }
    return false;
}

void ArkCLP::AddValue(const char * arg) {
    if (strnlen(arg, __ArkCLP_MAXSTRLEN) >= __ArkCLP_MAXSTRLEN) return;
    
    values_.push_back(std::string(arg));
}

void ArkCLP::AddOption(const char * arg) {
    if (strnlen(arg, __ArkCLP_MAXSTRLEN) >= __ArkCLP_MAXSTRLEN) return;
    
    while (*arg == '-') {
        if (*++arg == 0) return;
    }
    
    std::string str_arg(arg);
    if (str_arg.find('=')) {
        auto pos = str_arg.find('=');
        options_.insert({str_arg.substr(0, pos), str_arg.substr(pos+1)});
    } else {
        options_.insert({str_arg, str_arg});
    }
}

void ArkCLP::ParseCommandLine() {
    const char * arg = nullptr;
    for (auto i=0; i<argc_; ++i) {
        arg = argv_[i];
        if (*arg == '-') {
            AddOption(arg);
        } else {
            AddValue(arg);
        }
    }
}
