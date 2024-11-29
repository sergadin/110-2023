#include <stdio.h>
#include <string>
#include <iostream>
#include <math.h>

#pragma once
#include "Error.h"

#define eps 1e-10

using namespace std;

class Dot
{
private:
    double x_;
    double y_;
public:
    Dot() : x_(0.0), y_(0.0) {};
    Dot(double x, double y);    //конструктор
    ~Dot();     //деструктор

    double get_x() const;   //Возращает х координату точки
    double get_y() const;   //Возращает у координату точки

    Dot &operator=(const Dot &other);
    
};
