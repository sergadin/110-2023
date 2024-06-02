#include "pointer_7.h"

// f: R->R; g: R*R->Z; x - аргумент;
// limit - кол-во операций до вынужденного завершения программы 

void find_the_null(R_Rfun f, RR_Zfun g, double x, int limit) {
	
	double f1, f2; // Последние 2 значения функции f
	f1 = (*f)(x);
	f2 = (*f)(f1);
	
	
	while (((*g)(f1, f2) != 0) && (limit > 0)) {
		f1 = f2;
		f2 = (*f)(f1);
		//printf("%lf\n", f1);
		--limit;
	}
	printf("%lf\n%lf\n", f1, f2);
	
	if ((*g)(f1, f2) != 0) {
		printf("Ноль не найден\n");
	}
	else {
		printf("Последовательность завершена\n");
	} //проверка, что мы завершили не из-за лимита
	
	return;
}
