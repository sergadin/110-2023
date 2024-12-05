#include <iostream>
#include "rectangle.h"

int main(){
	point a(0, 0), b(100, 100);
	TreeNode rect(a, b);
	for (int i = 0; i < 100; i++){
		for (int j = 0; j < 100; j++){
		point p(i, j);
		std::cout << p[0] << " " << p[1] << "\n";
		rect.add_point(p);
		}
	}
	std::cout << rect.small_ << "\n";
	rect.delete_point(a);
	point c(55,55);
	point *test;
	std::cout << 11111 << "\n";
	std::cout << rect[0][0] << " ; " << rect[0][1] << "\n";
	test = rect.neighbours(c);
	int len = rect.get_len_neighbours(c);
	std::cout << len << "\n";
	for (int i = 0; i < len ; i++){
		std::cout << test[i][0] << " " << test[i][1] << "\n";
	}
}
