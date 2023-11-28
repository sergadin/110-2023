// 4.15  Разложить натуральное число на простые множители.

#include <stdio.h>
#include <math.h>

int main(void) {
	int N; // натуральное число, считываемое с клавиатуры
	int izmen_N;
	int st; // степень простого множителя
	
	printf("vvedite chislo N = ");
	
	if ((scanf("%d", &N) != 1) || (N < 1)) {
		printf("not korr N (not natur)\n");
		return -1;
	}
	
	printf("%d = 1", N);
	
	izmen_N = N;
	
	for (int i = 2; i < pow(N, 0.5) + 1; i++) {
		if ((izmen_N % i) == 0) {	
			printf(" * ");
			printf ("%d^", i);   // простой множитель
			for (st = 0; (izmen_N % i) == 0; st++) {
				izmen_N = izmen_N / i;
			}
			printf("%d", st);   // степень простого множителя
		}
	}
	
	if (izmen_N > 1) {
		printf(" * %d", izmen_N);
	}	
	
	printf("\n");
	return 0;
}