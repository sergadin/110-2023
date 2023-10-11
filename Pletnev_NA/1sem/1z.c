#include <stdio.h>  
#include <math.h> 
 
int main(void) {

    double x, nx; 
    double maxx = -1000.0 ; 
    double minx = 1000.0;
	double eps = 0.000001;  // задали определённую точность для вещественных чисел
    double del = 0.0000005;
    FILE *f ;

    fopen_s(&f, "input.txt", "r");  //открыли файл для чтения

    
    if (f == NULL) {                      //проверяем существование файла. если его нет, выводим ошибку
        printf("Error: File does not exist\n");
        return -1;
    }
    
    if (fscanf_s(f, "%lf", &x) != 1) {  //прочитали первое число и вывели ошибку при пустом файле
        printf("Error: List is empty\n");
		return -1;
	}

    while (!feof(f)) {
        if (x - maxx >= del) {
            maxx = x ;
        }
        if (x - minx < del) {
            minx = x ;
        }

        if (fscanf_s(f, "%lf", &nx) == 1) {
            x = nx;
        }
        else {
            printf("Error: Invalid data entry\n");
            return -1;
        }
    }

    if ((maxx - minx) > eps) {
        printf("Result: No, not all numbers are equal with an error of <");
        printf("%lf", eps);
        printf(">\n");
        return 1; 
    }
    else {
        printf("Result: Yes, all numbers are equal with an error of <");
        printf("%lf", eps);
        printf(">\n");
        return 1;     
    }
            
}