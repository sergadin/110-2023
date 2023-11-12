#include <stdio.h>
#include <string.h>
#include <math.h>

int OSHIBKA = 0;

int opred_sum_chet_elem (FILE *f)
{
    int tek, pred, sum = 0, elem = 0, vozr_posl = 1, nevozr_posl = 1, col_chet = 0;
    //tek используется для хранения текущего считанного числа из файла
//pred используется для хранения предыдущего считанного числа из файла
//sum используется для хранения суммы четных чисел в последовательности
//elem используется для подсчета количества считанных чисел из файла
//vozr_posl и nevozr_posl используются для определения направления движения по последовательности (по возрастанию или убыванию)
//col_chet используется для подсчета количества четных чисел в последовательности
 
 if (fscanf(f, "%d", &tek) != 1) {
        OSHIBKA == -1;
        return 0;
    }

    while (fscanf(f, "%d", &tek) == 1) {
        if (elem == 0) {
            if (tek%2 == 0) sum += tek;
        }
        else {
            if (tek >= pred) {vozr_posl = 1;}
            else {vozr_posl = -1;} 
            if (tek%2 == 0 && vozr_posl == 1 && nevozr_posl == 1) { sum += tek; col_chet++; } 
            if (vozr_posl == 1 && nevozr_posl == -1) {
                if (pred%2 == 0) { sum += pred; col_chet++; }
                if (tek%2 == 0) { sum += tek; col_chet++; }
            } 
            nevozr_posl = vozr_posl;
            pred = tek;
        }
        elem++;
    }
 
    if (col_chet == 0) {sum = 0;}
    if (elem == 0) {sum = 1;}
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
		printf("Некорректный файл\n");
    }
	else {
		printf("Сумма чётных элементов в возрастающей последовательности равна: %d\n", sum_ravna);
	}
	
    fclose(f);
    return 0;
}