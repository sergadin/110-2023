// 4.15  Разложить натуральное число на простые множители.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PROST_V_KONZE 1
#define NET_PROST_V_KONZE -1
int kol = 0; //длина массива

int razl(int *mas, int N);
// функция разложения натурального числа на простые множители


int razl(int *mas, int N) { // вернуть массив
	int izmen_N = N;
	int st; // степень простого множителя
    
    for (int i = 2; i < pow(N, 0.5) + 1; i++) {
        if ((izmen_N % i) == 0) {
            mas[kol] = i;
            for (st = 0; (izmen_N % i) == 0; st++) {
                izmen_N = izmen_N / i;
            }
            mas[kol + 1] = st;
            kol = kol + 2;
        }
    }
	
	if (izmen_N > 1) {
        kol++;
        mas[kol] = izmen_N;
        return PROST_V_KONZE;
	}
	return NET_PROST_V_KONZE;
}


int main(void) {
	int N; // натуральное число, считываемое с клавиатуры
	FILE *file_out = fopen("output.txt", "w");
    int* mas = NULL;
    int razl_na_mnoz;
	
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
	
	mas = (int*) malloc((N)*sizeof(int));
    
    if (mas == NULL) {
		printf("Memory error\n");
		fclose(file_out);
		return -1;
	}
	
	razl_na_mnoz = razl(mas, N);	
    
    fprintf(file_out, "%d = 1", N);
    
    if (razl_na_mnoz == NET_PROST_V_KONZE) {
        for (int i = 0; i < kol; i++){
            fprintf(file_out, " * ");
            fprintf(file_out, "%d^", mas[i]);   // простой множитель
            fprintf(file_out, "%d", mas[i+1]);   // степень простого множителя
            i++;
        }
    }
    else {
        for (int i = 0; i < kol-1; i++){
            fprintf(file_out, " * ");
            fprintf(file_out, "%d^", mas[i]);   // простой множитель
            fprintf(file_out, "%d", mas[i+1]);   // степень простого множителя
            i++;
        }
        fprintf(file_out, " * ");
        fprintf(file_out, "%d", mas[kol]);   // простой множитель
    }

	fclose(file_out);
	return 0;
}
