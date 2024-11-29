#include <stdio.h>
#include <string>
#include <iostream>
#include <math.h>

#pragma once
#include "Error.h"
#include "Vector.h"

#define epsilon 1e-10

using namespace std;


Vector::Vector(double vx, double vy)
{
    vx_ = vx;
    vy_ = vy;
}

Vector::~Vector()
{
}

double Vector:: get_vx() const
{
    return vx_;
}

double Vector:: get_vy() const
{
    return vy_;
}