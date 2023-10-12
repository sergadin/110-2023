#include <stdio.h>  
#define LEN 100000

int main(void) {

    FILE* f;
    double x, maxx, minx;
    double eps = 0.001;  // задали определённую точность для вещественных чисел
    char buf[LEN];
    

    fopen_s(&f, "input.txt", "a+");  //открыли файл для чтения

    if (f == NULL) {                      //проверяем существование файла. если его нет, выводим ошибку
        printf("Error: File does not exist\n");
        return -2;
    }
    
    maxx = -1e100;
    minx = 1e100;

    while (fgets(buf, LEN, f)) {

        if (sscanf_s(buf, "%lf", &x) != 1) {
            printf("Error: Invalid data entry\n");
            return -1;
        }
        
        if (x > maxx) {
            maxx = x;
        }
        if (x < minx) {
            minx = x;
        }

    }

    if ((maxx - minx) > eps) {
        printf("Result: No, not all numbers are equal with an error of <%lf>\n", eps);
        return 1;
    }
    else {
        printf("Result: Yes, all numbers are equal with an error of <%lf>\n", eps);
        return 2;
    }
}
