#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class Error{
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


class Polynom
{

    private:
        int n_;
        double* data_;

    public:
        Polynom() = delete;
        Polynom(int n);
        Polynom(const Polynom &other);
        ~Polynom();

        void change(double x, int j);
        int degree();
        double value(double y);

        Polynom &operator+(const Polynom &p1, const Polynom &p2);
        Polynom &operator=(const Polynom &other);
        Polynom &operator+=(const Polynom &other);

};

Polynom::Polynom(int n)
{
    n_ = n + 1;

    if (n_ < 0)
    {
        throw Error(-1, "incorrect degree");
    }

    data_ = new double[n_];

    for(int i = 0; i < n_; i++)
    {
        data_[i] = 0;
    }
}

Polynom::Polynom(const Polynom &other)
{
    data_ = nullptr;

    *this = other;
}

Polynom::~Polynom()
{
    delete[] data_;
}

void Polynom::change(double x, int j)
{
    this->data_[j] = x;
}

int Polynom::degree()
{
    return n_;
}

double Polynom::value(double y)
{
    double s = 0;

    for(int i = n_; i > 0; i++)
    {
        s += this->data_[i];
        s *= y;
    }

    return s;
}

Polynom &Polynom::operator+(const Polynom &p1, const Polynom &p2)
{
    int c = 0;
    Polynom p(std::max(p1.n_, p2.n_));
    
    if (p1.n_ < p2.n_)
    {
        c = 22;
    }
    if (p1.n_ > p2.n_)
    {
        c = 11;
    }

    for (int i = 0; i < p.n; i++)
    {
        if (i < min(p1.n_, p2.n_))
        {
            p.data_[i] = p1.data_[i] + p2.data_[i];
        }
        else if (c == 11)
        {
            p.data_[i] = p1.data_[i];
        }
        else if (c == 22)
        {
            p.data_[i] = p2.data_[i];
        }
    }

    return p;
}

Polynom &Polynom::operator=(const Polynom &other)
{
    if (data_ == other.data_)
    {
        return *this;
    }

    n_ = other.n_;
    delete[] data_;
    this->data_ = new double[n_];

    for(int i = 0; i < n_; i++)
    {
        this->data_[i] = other.data_[i];
    }

    return *this;
}

Polynom& Polynom::operator+=(const Polynom &other)
{
    Polynom p(1);
    p = ((const Polynom)(*this) + other);

    return p;
}