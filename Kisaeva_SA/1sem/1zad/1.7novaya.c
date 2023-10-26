//7. Определить все ли элементы последовательности равны между собой (для вещественных чисел - с точностью ε).

#include <stdio.h> 
#define OSHIBKA -1
#define NE_RAVNU 0
#define RAVNU 1

int opred_ravenstvo_chisel(FILE *file);
// определяет все ли числа в файле (input) равны
// если все числа равны, то результатом работы функции является переменная RAVNU 
// если не все числа равны, то результатом работы функции является переменная NE_RAVNU
// в случае ошибки считывания присвоит результату работы функции переменную ошибка (OSHIBKA)


int opred_ravenstvo_chisel(FILE *file)  
{ 
    double min_elem, max_elem, elem, perv_elem; 
    double eps = 0.1;
    int is_elem_chislo; 
	int ravenstvo = RAVNU;
    
	if( fscanf(file, "%lf", &perv_elem) != 1) {
		return OSHIBKA;
	}
        min_elem = perv_elem;
		max_elem = min_elem;
  
    while ((is_elem_chislo = fscanf(file, "%lf", &elem)) != EOF) { 
        if (is_elem_chislo != 1) { 
			return OSHIBKA;
		}       
        if (elem < min_elem) { 
			min_elem = elem;
        }
		if (elem > max_elem) { 
			max_elem = elem;
        }
    }
	
    if ((max_elem - min_elem) >= eps) { 
	    ravenstvo = NE_RAVNU;
    }
    
    return ravenstvo;     
}


int main(void) 
{
    int is_vse_chisla_ravnu;
    FILE *file = fopen("input.txt", "r");

    if (file == NULL) {
		printf("error opening the file\n"); 
		return -1;
	}
	
    is_vse_chisla_ravnu = opred_ravenstvo_chisel(file);
	
    if (is_vse_chisla_ravnu == OSHIBKA) {
		printf("error\n"); 
		return -1;
	}
    if (is_vse_chisla_ravnu == RAVNU) {
		printf("YES, all numbers in the file are equal\n");
	}
			
    if (is_vse_chisla_ravnu == NE_RAVNU) {
		printf("NO, not all numbers in the file are equal\n");
	}
	
    fclose(file); 
    
	return 0;
}

