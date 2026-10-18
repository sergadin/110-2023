#include <iostream>
#include "polynom.h"

int main(){
	polynom a(2), b(3);
	a.change(1,0);
	a.change(1,1);
	a.change(1,2);
	b.change(1,0);
	a = a + b;
	std::cout << a.coef_deg(0) << a.coef_deg(1) << a.coef_deg(2) << a.coef_deg(3) << "\n";
	return 0;
}
