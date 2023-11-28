// 4.15  Разложить натуральное число на простые множители.

#include <stdio.h>
#include <math.h>

void razl(FILE *file_out, int N);
// функция разложения натурального числа на простые множители


void razl(FILE *file_out, int N) {
	int izmen_N = N;
	int st; // степень простого множителя
	
	fprintf(file_out, "%d = 1", N);
	
	for (int i = 2; i < pow(N, 0.5) + 1; i++) {
		if ((izmen_N % i) == 0) {	
			fprintf(file_out, " * ");
			fprintf (file_out, "%d^", i);   // простой множитель
			for (st = 0; (izmen_N % i) == 0; st++) {
				izmen_N = izmen_N / i;
			}
			fprintf(file_out, "%d", st);   // степень простого множителя
		}
	}
	
	if (izmen_N > 1) {
		fprintf(file_out, " * %d", izmen_N);
	}
}


int main(void) {
	int N; // натуральное число, считываемое с клавиатуры
	FILE *file_out = fopen("output.txt", "w");
	
	if (file_out == NULL) {
		printf("error opening the file_out");
		return -1;
	}
	
	printf("vvedite natur chislo N = ");
	
	if ((scanf("%d", &N) != 1) || (N < 1)) {
		printf("not korr N (not natur)\n");
		fclose(file_out);
		return -1;
	}
	
	razl(file_out, N);	
	
	printf("rezultat napechatan\n");
	
	fclose(file_out);
	return 0;
}