#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <set>
#include <map>

class Error
{ 
private:
    int code_ = 0;
    std::string reason_ = "";
public:
    Error(int code, std::string reason)
    { 
      code_ = code;
      reason_ = reason;
    }
    std::string getReason()
    {
      return reason_;
    }
    int getCode()
    { 
      return code_;
    }
};

#endif