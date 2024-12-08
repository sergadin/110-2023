#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <stdexcept>
#include <memory>
#include <variant>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>
#include <map>
#include <optional>
#include <limits>

class Error 
{
private:
    int code_ = 0;
    std::string reason_ = "";
public:
    Error(int code, std::string reason) : code_(code), reason_(std::move(reason)) {}

    std::string getReason() const 
    { 
        return reason_;
    }
    int getCode() const 
    { 
        return code_;
    }
};

#endif