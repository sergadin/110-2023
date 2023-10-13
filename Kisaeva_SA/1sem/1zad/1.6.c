//6. Определить номер последнего числа, равного X (для вещественных чисел — с точностью ε).  

#include <stdio.h>  
#include <math.h> 

int nomer(FILE *file) ;

int nomer(FILE *file) 
{ 
    double x, a;
	int chislo;
	int k = -2;
	double eps = 0.1; 
	int n = -1;
    
    if ((fscanf(file, "%lf", &x) != 1)) {   
		return -1;
	}

    while ((chislo = fscanf(file, "%lf", &a)) != EOF) { 
		n ++;
        if (chislo != 1) { 
            return -1;                
        }
        if (fabs(a - x) < eps) { 
            k = n;                     
        }
    }
    if (n == -1){
		k = -1;
	}
		return k;		
}

int main(void) {

    int f;
    FILE *file = fopen("input.txt", "r");

    
    if (file == NULL) {                      
        printf("error opening the file\n");
        return -1;
    }
    
    f = nomer(file);
        

    if ((f != -2) && (f != -1)) // если нашли число, равное Х
	{
        printf("%d\n", f);  
    } 
	else if (f == -2)  // если в файле нет числа, равного Х
	{
        printf("net chisla, kotoroe ravno X\n");
    }
    else if (f == -1)       // если файл пустой/там попались не числа/после Х ничего нету 
    {
        printf("error\n");
    }
	
    fclose(file); 

    return 0;
}
