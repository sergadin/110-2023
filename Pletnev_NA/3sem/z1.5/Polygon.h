#include <stdio.h>
#include <string>
#include <iostream>
#include <math.h>
#include <vector>

#pragma once
#include "Error.h"
#include "Dot.h"
#include "Vector.h"

#define epsilon 1e-10

using namespace std;

class Polygon
{
private:
    int n_;
    vector<Dot> data_;
public:
    Polygon() = delete;
    Polygon(int n);
    Polygon(const Polygon &other);
    ~Polygon();

    int get_n() const;
    void add_dot(const Dot &A, int i);
    Dot get_dot(int i) const;

    Polygon &operator=(const Polygon &other);
};

