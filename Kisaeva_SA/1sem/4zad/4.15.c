// 4.15  Разложить натуральное число на простые множители.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int razl(int *mas, int N);
// функция разложения натурального числа на простые множители


int razl(int *mas, int N) { // вернуть массив
	int izmen_N = N;
    int kol = 0;
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
		mas[kol] = izmen_N;
        mas[kol+1] = 1;
	}
    kol = kol + 2;
	return kol;
}


int main(void) {
	int N; // натуральное число, считываемое с клавиатуры
	FILE *file_out = fopen("output.txt", "w");
    int* mas = NULL;
    int kol_del;
	
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
	
	kol_del = razl(mas, N);	
        
    for (int i = 0; i < kol_del; i += 2){
        if(i > 0)
            fprintf(file_out, " * ");
        fprintf(file_out, "%d^", mas[i]);   // простой множитель
        fprintf(file_out, "%d", mas[i+1]);   // степень простого множителя
    }
    fprintf(file_out, "\n");

	fclose(file_out);
	return 0;
}