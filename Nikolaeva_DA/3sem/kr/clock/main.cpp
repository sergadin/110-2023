#include "clock.h"
#include <iostream>

using namespace std;

int main(void) {
	try {
		Vector v1(4, 1), v2(4, 2), v3(4, 0);


		v2.updateLocation();
		v3.updateLocation();
		v3.updateLocation();
		v3.updateLocation();

		cout << "Vector 2: ";
		v2.printVector();
		cout << "Vector 3: ";
		v3.printVector();

		v1 = v2; 
		v2.updateIncrement(v3);

		cout << "New Vector 2: ";
		v2.printVector();

		cout << "v2 < v3: " << (v2 < v3) << endl;
		cout << "v3 < v2: " << (v3 < v2) << endl;

	} catch (Error& err) { 
		cout << "EXEPTION: " << err.get_mes() << "\n";
	} catch (...) { 
		cout << "Something wrong. We don't know, what is it?" << "\n";
	}
	return 0;
}
