#include <stdio.h>  
#define LEN 100000

int main(void) {

    FILE* f;
    int x, i, minx, mini;
    char buf[LEN];

    fopen_s(&f, "input.txt", "r");  //открыли файл для чтения

    if (f == NULL) {                      //проверяем существование файла. если его нет, выводим ошибку
        printf("Error: File does not exist\n");
        return -2;
    }

    minx = 1000000;
    mini = 0;
    i = 0;

    while (fgets(buf, LEN, f)) {

        if (sscanf_s(buf, "%ld", &x) != 1) {
            printf("Error: Invalid data entry\n");
            return -1;
        }

        if (x <= minx) {
            minx = x;
            mini = i;
        }

        ++i;
    }

    if (minx != 1000000) {
        printf("Result: The number of the last minimum number is equal to <%ld>\n", mini);
        return 1;
    }

    else {
        printf("The file 'input.txt' is empty\n");
        return 0;
    }
}
