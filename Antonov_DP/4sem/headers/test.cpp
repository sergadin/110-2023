#include "database.hpp"


int main(){
	char name[] = "Антонов";
	int group = 210;
	double rating = 4;
	char info[] = "Москва";
	student person(name, group, rating, info);
	person.print();
}
