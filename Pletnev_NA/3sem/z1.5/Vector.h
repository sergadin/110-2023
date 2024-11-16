#include <stdio.h>
#include <string>
#include <iostream>
#include <math.h>

#pragma once
#include "Error.h"

#define epsilon 1e-10

using namespace std;

class Vector
{
private:
    double vx_;
    double vy_;

public:
    Vector() = delete;
    Vector(double vx, double vy);   //Конструктор
    ~Vector();  //Деструктор

    double get_vx() const;   //Возращает х координату вектора
    double get_vy() const;   //Возращает у координату вектора
};

