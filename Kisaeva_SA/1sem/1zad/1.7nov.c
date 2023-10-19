#include <stdio.h>  // библиотека для printf, fscanf, fclose, fopen
#include <math.h>  // это библиотека для математических операций, нам нужна для того, чтобы пользоваться модулем(fabs)

int is_equal(FILE *file) ;

int is_equal(FILE *file)  // функция для определения равности между собой чисел в файле
{ 
    double x, next_x;
	double eps = 0.1; // задали определённую точность для вещественных чисел
	int next;
    
    if ((fscanf(file, "%lf", &x) != 1)) {   //прочитали первое число и вывели ошибку при пустом файле или если это не число
		return -1;
	}

    while ((next = fscanf(file, "%lf", &next_x)) != EOF) { //пока мы можем считать следующее число, проверяем их равенство (пока не конец файла)
         if (next != 1) { 
            return -1;                   // ошибка, если в файле встретились не числа
        }
        if (fabs(next_x - x) > eps) { 
            return 0;                     // ложный результат работы функции, если числа не равны
        }
        x = next_x;
    }
    return 1;        // фунция выдаёт правду, если все числа равны 
}

int main(void) {

    int f;
    FILE *file = fopen("input.txt", "r");

    
    if (file == NULL) {                      //проверяем существование файла. если его нет, выводим ошибку
        printf("error opening the file\n");
        return -1;
    }
    
    f = is_equal(file);
        

    if (f == 1) // если функция выдаёт правду и файл не пустой, т е 1, то выводим, что все числа равны
	{
        printf("YES, all numbers in the file are equal\n");  
    } 
	else if (f == 0)  // иначе если файл не пустой печатаем, что числа не равны
	{
        printf("NO, not all numbers in the file are equal\n");
    }
    else if (f == -1)       // иначе печатаем ошибку, если файл пустой или там не числа
    {
        printf("error\n");
    }
	
    fclose(file); 

    return 0;
}
