//28. найти максимальную сумму подряд идущих элементов последовательности

#include <stdio.h> 
int OSHIBKA = 0;

double opred_max_sum(FILE *file);
// определяет максимальную сумму (max_sum) подряд идущих элементов последовательности
// в случае oшибки считывания присваивает глобальной переменной OSHIBKA значение -1 и работа функции прерывается


double opred_max_sum(FILE *file) {
	double next_elem, first_elem;
	int is_next_elem_chislo;
	int kol_vseh_elem = 0;
	int	kol_otricat = 0;
	double max_sum;
    double sum;
    double max_otricat_el;

    if (fscanf(file, "%lf", &first_elem) != 1) {
        OSHIBKA = -1;
        return -1;
    }

    kol_vseh_elem = 1;
    
    if (first_elem < 0) {
        max_otricat_el = first_elem;
        sum = 0;
        kol_otricat = 1;
    }
    else {
        sum = first_elem;
    }
    
    max_sum = sum;
	
	while ((is_next_elem_chislo = fscanf(file, "%lf", &next_elem)) != EOF) {    
		if (is_next_elem_chislo != 1) { 
			OSHIBKA = -1;
            return -1;
        }
        
        kol_vseh_elem += 1;
		sum += next_elem;
		
		if (sum > max_sum) {
			max_sum = sum;
		}
		if (sum < 0) {
            sum = 0;
		}
		
		if ((next_elem < 0) && (first_elem < 0)){
            kol_otricat += 1;
			if (max_otricat_el < next_elem){
				max_otricat_el = next_elem;
			}
		}
	} 
	
	if (kol_vseh_elem == kol_otricat) {
		max_sum = max_otricat_el;
	}
	
	return max_sum; 
}


int main(void) {
    double max_sum_ravna;
    FILE *file = fopen("input.txt", "r");

    if (file == NULL) {                
        printf("error opening the file\n");
        return -1;
    }
    
    max_sum_ravna = opred_max_sum(file);
    
    if (OSHIBKA == -1) {
		printf("error\n");
    }
	else {
		printf("max summa podryad iduchih chisel ravna: %lf\n", max_sum_ravna);
	}
	
    fclose(file);
	
    return 0;
}
