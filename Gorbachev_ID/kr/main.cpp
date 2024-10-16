#include <iostream>
#include "Head.h"

int main()
{
	Polynom Ilya(2), Gorbachev(5);
	Ilya.change(68,0);
	Ilya.change(228,1);
	Ilya.change(666,2);
	Gorbachev.change(1,0);
	Gorbachev.change(404, 4);
	Ilya = Ilya + Gorbachev;
	std::cout << Ilya.coefficient(0) << " + " << Ilya.coefficient(1) << "*x + " << Ilya.coefficient(2) << "*x^2 + " <<
	       	Ilya.coefficient(3) << "*x^3 + " << Ilya.coefficient(4) << "*x^4" "\n";
	return 0;
}
