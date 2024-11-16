#include <stdio.h>
#include <string>
#include <iostream>
#include <math.h>

#pragma once
#include "Error.h"
#include "Dot.h"

#define eps 1e-10

using namespace std;

Dot::Dot(double x, double y)
{
    x_ = x;
    y_ = y;
}


Dot::~Dot()
{
}

double Dot:: get_x() const
{
    return x_;
}

double Dot:: get_y() const
{
    return y_;
}

Dot &Dot::operator=(const Dot &other)
{
    double x = other.x_;
    double y = other.y_;

    Dot T(x, y);
    *this = T;

    return *this;
}