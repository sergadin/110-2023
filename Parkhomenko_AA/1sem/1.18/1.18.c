#include <stdio.h>
#include <string.h>
#include <math.h>

int OSHIBKA = 0;
int NE_VOZR = 0;

int opred_sum_chet_elem (FILE *f);


int opred_sum_chet_elem (FILE *f)
{
    int tek, pred, sum = 0, schit_tek;
//tek используется для хранения текущего считанного числа из файла
//pred используется для хранения предыдущего считанного числа из файла
//sum используется для хранения суммы четных чисел в последовательности
 
    if (fscanf(f, "%d", &pred) != 1) {
        OSHIBKA = -1;
        return -1;
    }

    if (pred%2 == 0) sum += pred;

    while ((schit_tek = fscanf(f, "%d", &tek)) != EOF) {
        if (schit_tek != 1) {
            OSHIBKA = -1;
            return -1;
        }
        
        if (tek > pred) {
            NE_VOZR = 1;
            if (tek%2 == 0) { sum += tek; }
        }
        else {
            if(tek < pred) {
                if ((NE_VOZR != 1) && (pred%2 == 0)) { sum += pred; }
            NE_VOZR = 1;
            }
        }
        pred = tek;
    }
    return sum;
}

 
int main(void) {
    int sum_ravna;
    FILE *f = fopen("1.18.1.txt", "r");

    if (f == NULL) {                
        printf("error opening the file\n");
        return -1;
    }
    
    sum_ravna = opred_sum_chet_elem(f);
    
    if (OSHIBKA == -1) {
		printf("Некорректный файл\n"); //пустой или есть буквы  
    }
   // else if (NE_VOZR == 1) {
	//	printf("Последовательность не возрастает\n");
   // }
	else {
		printf("Сумма чётных элементов в возрастающих участках целой последовательности равна: %d\n", sum_ravna);
	}
	
    fclose(f);
    return 0;
}
