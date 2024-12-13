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
#include <regex>

class Error : public std::runtime_error {
private:
    int code_;
public:
    Error(int code, const std::string& reason) : std::runtime_error(reason), code_(code) {}
    Error(int code, std::string&& reason) : std::runtime_error(std::move(reason)), code_(code) {}

    int getCode() const { return code_; }
};

#endif