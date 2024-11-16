#include <stdio.h>
#include <string>
#include <iostream>

#pragma once

using namespace std;

class Error
{
private:
    int code_;
    string message_;

public:
    Error(int code, string message)
    {
        code_ = code;
        message_ = message;
    }
    
    const string get_mess() const
    {
        return message_;
    }
};