//6. Определить номер последнего числа, равного X (для вещественных чисел — с точностью ε).  

#include <stdio.h>  
#include <math.h> 
#define OSHIBKA -1
#define NET_TAKOGO_CHISLA -2

int opred_nomer_X(FILE *file, double X); 
// функция определяет номер (itog_nom) последнего вхождения числа X
// в случае несуществования числа X в файле функция присвоит искомому номеру (itog_nom) значение NET_TAKOGO_CHISLA
// в случае другой ошибки (ошибки считывания) присвоит искомому номеру (itog_nom) переменную ошибка (OSHIBKA)


int opred_nomer_X(FILE *file, double X) 
{ 
    double elem;
	int is_chislo;
	int itog_nom = NET_TAKOGO_CHISLA;
	double eps = 0.1; 
	int nom_elem = -1;

    while ((is_chislo = fscanf(file, "%lf", &elem)) != EOF) { 
		nom_elem ++;
        if (is_chislo != 1) { 
            return OSHIBKA;               
        }
        if (fabs(X - elem) <= eps) {
            itog_nom = nom_elem; 
        }
    }
    if (nom_elem == -1){
		itog_nom = OSHIBKA;
	}
    return itog_nom;		
}


int main(void) 
{
    int is_X_chislo, opred_nomer;
    double X;
    FILE *file = fopen("input.txt", "r");

    if (file == NULL) {                      
        printf("error opening the file\n");
        return -1;
    }
    
	printf("vvedite chislo: ");
    is_X_chislo = scanf("%lf", &X);
    
    if (is_X_chislo != 1) {  
        opred_nomer = OSHIBKA; 
	}
    else {
        opred_nomer = opred_nomer_X(file, X);
    }

	if (opred_nomer == NET_TAKOGO_CHISLA)  // если в файле нет числа, равного Х
	{
        printf("net chisla, kotoroe ravno X\n");
    }
    else if (opred_nomer == OSHIBKA)       // если файл пустой / попались не числа 
    {
        printf("error\n");
    }
    else if ((opred_nomer != NET_TAKOGO_CHISLA) && (opred_nomer != OSHIBKA)) // если нашли число, равное Х
	{
        printf("%d\n", opred_nomer);  
    } 
	
    fclose(file); 

    return 0;
}
