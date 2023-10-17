#include <stdio.h>
#include <math.h> 
#define LEN 100000000
int EqualityCheck(FILE *inp_f,  FILE *out_f, double eps, int mxlen);


int EqualityCheck(FILE *inp_f,  FILE *out_f, double eps, int mxlen){ //функция проверяет, что все числа в файле равны с собой с учетом погрешности
    
    double x, maxx, minx;
    char buf[LEN];
    
    maxx = -1*pow(10, 2*mxlen+1);  //вводим бесконечное малое значение, чтобы сравнить с ним
    minx = -1*pow(10, 2*mxlen+1);  //вводим бесконечное большое значение, чтобы сравнить с ним

    while (fgets(buf, LEN, inp_f)) { //идем по файлу пока мы можем считовать файл

        if (sscanf(buf, "%lf", &x) != 1) { //проверяем, что мы можем считать строчки
            
            printf("Error: Invalid data entry. Check the input file\n");
            return -2;
        }
        
        if (fabs(x) > 1*pow(10, mxlen)) {  //проверяем, что наши числа не слишком болшие
            
            printf("Error: The file input file contains too large values\n");
            return -1;
        }
        
        if (x > maxx) { //ищем наибольшое значение в файле
            maxx = x;
        }
        
        if (x < minx) { //ищем наименьшее значение в файле
            minx = x;
        }

    }

    if  ( (maxx < -1*pow(10, 2*mxlen) ) || (minx > 1*pow(10, 2*mxlen) ) ) {  //проверяем, что в файл не пуст
        
            printf("The input file is empty\n");
            return 0;
        }
    
    if ((maxx - minx) > eps) { //проверяем, что все наши зажатые числа лежат в предлах погрешности
        
            printf("The result is uploaded to the output file\n");
            fprintf(out_f, "Result: No, not all numbers are equal");
            return 1;
        }
        
        
    printf("The result is uploaded to the output file\n");    
    fprintf(out_f, "Result: Yes, all numbers are equal\n");
    return 2;

}


int main(void) {

    FILE *inp_f, *out_f;
    double eps;
    int mxlen;
    char fi[30], fo[30];
    
    printf("Enter the name of the input file:\n");
	scanf("%s" , fi);
    
	printf("Enter the name of the output file:\n");
	scanf("%s" , fo);
    

    inp_f = fopen(fi, "r");  //открыли файл для чтения
    out_f = fopen(fo , "w"); //открыли файл для записи
    
    
    if (inp_f == NULL) {                             //проверяем существование файла. если его нет, выводим ошибку
        printf("Error: The file '%s' does not exist\n", fi);
        return -3;
    }
    
    
    printf("Enter the error value:\n");
	scanf("%lf" , &eps);
    
	printf("Enter the maximum power of 10 to check the numbers\n");
	scanf("%d" , &mxlen);
  
    
    EqualityCheck(inp_f, out_f, eps, mxlen); //запускаем работу функции
    
    fclose(inp_f); //закрыли файл для чтения
	fclose(out_f); //закрыли файл для записи
    
	return 100;
        
}



