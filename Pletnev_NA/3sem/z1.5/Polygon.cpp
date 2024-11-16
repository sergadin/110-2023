#include <stdio.h>
#include <string>
#include <iostream>
#include <math.h>
#include <vector>

#pragma once
#include "Error.h"
#include "Dot.h"
#include "Polygon.h"

Polygon::Polygon(int n) : n_(n)
{
    if (n_ <= 0)
    {
        throw Error(-10, string("There is no such polygon\n"));
    }

    data_.resize(n_);
}

Polygon::Polygon(const Polygon &other) : n_(other.n_), data_(other.data_)
{
}

Polygon::~Polygon()
{
}

int Polygon::get_n() const
{
    return n_;
}

void Polygon::add_dot(const Dot &A, int i)
{
    if ((i < 0) || (i >= n_))
    {
        throw Error(-11, string("Index out of bounds\n"));
    }

    data_[i] = A;
}

Polygon &Polygon::operator=(const Polygon &other)
{
    if (this == &other)
    {
        return *this;
    }

    n_ = other.n_;
    data_ = other.data_; // Assign the vector directly
    return *this; 
}

Dot Polygon::get_dot(int i) const
{
    if ((i < 0) || (i >= n_))
    {
        throw Error(-11, string("Index out of bounds\n"));
    }

    return data_[i];
}