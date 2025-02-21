#include "student.hpp"
#include <iostream>

int main(){
	char name[] = "ВасяВасяВасяВасяВасяВасяВасяВасяВасяВасяВасяВасяВасяВасяВасяВася";
	int group = 210;
	double rating = 4;
	char info[] = "Москва";
	student person(name, group, rating, info);
	person.print();
}
