#include <stdio.h>
#include <string>
#include <iostream>
#include "Polynom.hpp"

using namespace std;

int main(void)
{
    char ctemp[50];
     
    Polynom a(3);

    for(int i = 0; i < a.degree(); i++)
    {
        a.change((double)(i), i);
    }

    cout << sprintf(ctemp," a(0.5) = %lf\n", a.value(0.5));
    cout << sprintf(ctemp," a(1.0) = %lf\n", a.value(1.0));

    Polynom b(a);

    cout << sprintf(ctemp," b(0.5) = %lf\n", b.value(0.5));
    cout << sprintf(ctemp," b(1.0) = %lf\n", b.value(1.0));

    Polynom c(b);

    for(int i = 0; i < c.degree(); i++)
    {
        c.change((double)(c.degree() - i), i);
    }

    cout << sprintf(ctemp," a(0.5) = %lf\n", c.value(0.5));
    cout << sprintf(ctemp," a(1.0) = %lf\n", c.value(1.0));

    Polynom d(10);

    d += a;

    cout << sprintf(ctemp," d.n_ = %d\n", d.degree());

    d += c;
    cout << sprintf(ctemp," a(1.0) = %lf\n", d.value(1.0));

    try
    {
        Polynom er1(-2);
    }
    catch(const Error &err)
    {
        cout << "Error: " << err.get_mess() << endl;
    }
    catch(...)
    {
        cout << "Something wrong" << endl;
    }

    return 0;
}