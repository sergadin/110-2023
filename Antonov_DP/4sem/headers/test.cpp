#include "database.hpp"
#include <iostream>


int main(){
	char name[] = "Antonov";
	int group = 210;
	double rating = 4;
	char info[] = "Moscow";
	student st(name, group, rating, info);
	char name1[] = "Storogeva";
	group = 210;
	rating = 5;
	student st1(name1, group, rating, info);
	char name2[] = "Chepkalenko";
	group = 210;
        rating = 3;
        student st2(name2, group, rating, info);
	char name3[] = "Simonyan";
	group = 208;
        rating = 3.5;
        student st3(name3, group, rating, info);
	char name4[] = "Baderko";
	group = 111;
        rating = 4,5;
        student st4(name4, group, rating, info);
	Hash hash;
	std::cout << 1 << "\n";
	hash.Add_student(st);
	std::cout << 1 << "\n";
	hash.Add_student(st1);
	std::cout << 1 << "\n";
	hash.Add_student(st2);
	std::cout << 1 << "\n";
	hash.Add_student(st3);
	hash.Add_student(st4);
}
