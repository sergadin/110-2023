#include "Hash.hpp"
#include <iostream>


int main(){
	char name[] = "Антонов";
	int group = 210;
	double rating = 4;
	char info[] = "Москва";
	std::cout << "1" << "\n";
	student person(name, group, rating, info);
	std::cout << "1" << "\n";
	person.print();
	Hash hash;
	std::cout << "1" << "\n";
	hash.Add_group(group);
	std::cout << "1" << "\n";
	hash.Delete_group(group);
	std::cout << "1" << "\n";
}
