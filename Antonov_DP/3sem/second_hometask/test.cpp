#include <iostream>
#include "rectangle.h"

int main(){
	point a(0, 0), b(100, 100);
	TreeNode rect(a, b);
	for (int i = 0; i < 100; i++){
		for (int j = 0; j < 100; j++){
		double first = ((double)i) / 10, second = ((double)j) / 10;
		point p(first, second);
		rect.add_point(p);
		}
	}
	rect.delete_point(a);
	point c(9.9, 9.9);
	point *test;
	std::cout << rect.len() << "\n";
	std::cout << "[" << rect[0][0] << " ; " << rect[0][1] << "]" << "\n";
	test = rect.neighbours(c);
	int len = rect.get_len_neighbours(c);
	std::cout << "len of neighbours =" << len << "\n" << "neighbours: ";
	for (int i = 0; i < len ; i++){
		std::cout << test[i][0] << " " << test[i][1] << "\n";
	}
	delete[] test;
}
