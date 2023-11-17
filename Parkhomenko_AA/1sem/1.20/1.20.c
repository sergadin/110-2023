//20. Найти количество элементов в наибольшем постоянном участке целой последовательности.

#include <stdio.h>   
#define ERROR -1

int opred_kol_el(FILE *file); 


int opred_kol_el(FILE *file) 
{ 
 int kol_el = 0;
 int max_kol, el1, el2, korrectnost_elem;
 
 if (fscanf(file, "%d", &el1) != 1) {  
        return ERROR;               
    }
 
 kol_el = 1;
 max_kol = kol_el;

    while ((korrectnost_elem = fscanf(file, "%d", &el2)) != EOF) { 
        if (korrectnost_elem != 1) { 
            return ERROR;               
        }
        if (el1 == el2) {
            kol_el++;
        }
  if (kol_el > max_kol) {
   max_kol = kol_el;
  }
   if (el1 != el2) {
            kol_el = 1;
        }
  el1 = el2;
    }
 
    return max_kol;  
}


int main(void) 
{
    int max_kol_el;
    FILE *file = fopen("1.20.1.txt", "r");

    if (file == NULL) {                      
        printf("error opening the file\n");
        return -1;
    }
    
    max_kol_el = opred_kol_el(file);

    if (max_kol_el == ERROR) {
        printf("error\n");
    }
    else {
        printf("%d\n", max_kol_el);  
    } 
 
    fclose(file); 
    return 0;
}