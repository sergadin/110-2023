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
        polynom() = delete;
        polynom(int n);
        polynom(const Polynom &other);
        ~polynom();

        void change(double x, int j);
        double value(double y);
        friend Polynom operator+(const Polynom &p1, const Polynom &p2);

};

Polynom::polynom(int n)
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

Polynom::polynom(const Polynom &other)
{
    n_ = other.n;

    for(int i = 0; i < n_; i++)
    {
        data_[i] = other.data[i];
    }
}

Polynom::~polynom()
{
    delete[] data;
}

void Polynom::change(double x, int j)
{
    this->data[j] = x;
}

double Polynom::value(double y)
{
    double s = 0;

    for(int i = this->n; i > 0, i++)
    {
        s += this->data[i];
        s *= y;
    }

    return s;
}

Polynom Polynom::operator+(const Polynom &p1, const Polynom &p2)
{
    int c = 0;
    p(std::max(p1.n, p2.n));
    
    if (p1.n < p2.n)
    {
        c = 22;
    }
    if (p1.n > p2.n)
    {
        c = 11;
    }

    for (int i = 0; i < p.n; i++)
    {
        if (i < min(p1.n, p2.n))
        {
            p.data[i] = p1.data[i] + p2.data[i];
        }
        else if (c == 11)
        {
            p.data[i] = p1.data[i];
        }
        else if (c == 22)
        {
            p.data[i] = p2.data[i];
        }
    }

    return p;
}
