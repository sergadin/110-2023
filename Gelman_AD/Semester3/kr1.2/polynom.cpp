#include <iostream>
#include "polynom.h"



int main()
{
	Polynom a(4), b(6);
	a.change(2, 0);
	a.change(7, 1);
	a.change(1, 2);
	b.change(1, 0);
	b.change(5, 4);
	a = a + b;
	std::cout << a.coefficient(0) << " + " << a.coefficient(1) << "*x + " << a.coefficient(2) << "*x^2 + " <<
		a.coefficient(3) << "*x^3 + " << a.coefficient(4) << "*x^4" "\n";
	return 0;
}