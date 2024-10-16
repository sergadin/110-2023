#include <stdio.h>
#include <string>
#include <iostream>

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

class Lamport
{

private:
    int n_;
    int *vector_;


public:

    Lamport() = delete;
    Lamport(int n);
    Lamport(const Lamport &other);
    ~Lamport();

    string event(int k);
    string get(string s,)

    Lamport &operator=(const Lamport &other);

};

Lamport::Lamport(int n)
{
    n_ = n;

    vector_ = new int[n_];

    for(int i = 0; i < n_; i++)
    {
        other.vector_[i] = 0;
    }
}


Lamport::Lamport(const Lamport &other)
{
    vector_ = nullptr;

    *this = other;
}


Lamport::~Lamport()
{
    delete[] vector_;
}

string Lamport::event(int k)
{
    vector_[k] += 1;
    string s = "done";

    return s;
}


string Lamport::get(string so, const Lamport &other)
{
    if (s0 == '')
    {
        return "not get"
    }



    s = "get"
    return s;
}

Lamport &Lamport::operator=(const Lamport &other)
{
    if (vector_ == other.vector_)
    {
        return *this;
    }

    n_ = other.n_;

    delete[] vector_;
    this->vector_ = new int[n_];

    for(int i = 0; i < n_; i++)
    {
        this->vector_[i] = other.vector_[i];
    }

    return *this;
}















