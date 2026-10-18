#include <iostream>
#include <stdio.h>
#include "vector.h"

using namespace std;

Vector::Vector (int N, int Nsize)
{
    if ((N <= 0) || (Nsize < 0) || (N <= Nsize))
    {
        throw Error (-1, string ("неправильный размер"));
    }

    N_ = N;
    Nsize_ = Nsize;
    vect_ = new int[N];
    for (int i = 0; i < N; i++)
    {
        vect_[i] = 0;
    }
}

Vector::Vector(const Vector &v)
{
    N_ = v.N_;
    Nsize_ = v.Nsize_;
    for (int i = 0; i < N_; i++)
    {
        vect_[i] = v.vect_[i];
    }
}

    void Vector::writeLoc()
    {
        vect_[Nsize_]++;
    }

    void Vector::writeInc (const Vector &v)
    {
        vect_[Nsize_]++;
        if (N_!=v.N_)
        {
            throw Error (-2, std::string ("неправильный процесс' число"));
        }

        for (int i = 0; i < N_; i++)
        {
            if (vect_[i] < v.vect_[i])
            {
                vect_[i] = v.vect_[i];
            }
        }   
    }

    Vector& Vector::operator = (const Vector &v)
    {
        if (vect_ == v.vect_)
        {
            return *this;
        }

        N_ = v.N_;
        Nsize_ = v.Nsize_;
        delete []vect_;
        vect_ = new int[N_];
        for (int i = 0; i < N_; i++)
        {
            vect_[i] = v.vect_[i];
        }
        return *this;
    }

    bool Vector::operator<(const Vector &v)
    {
        if (N_!=v.N_)
        {
            throw Error (-2, std::string ("неправильный процесс' число"));
        }

        for (int i = 0; i < N_; i++)
        {
            if (vect_[i] > v.vect_[i])
            {
                return 0;
            }
        }

        return 1;
    }

    void Vector::printVect()
    {
        for (int i = 0; i < N_; i++)
        {
            cout << vect_[i] << " ";
        }

        cout << "\n";
    }
