#include <stdio.h>
#include <string.h>
#include <math.h>
 
int fun(FILE *f);
 
int fun(FILE *f)
{
    int x, k, s = 0, i = 0, g = 1, gg = 1, u = 0;
    //x используется для хранения текущего считанного числа из файла
//k используется для хранения предыдущего считанного числа из файла
//s используется для хранения суммы четных чисел в последовательности
//i используется для подсчета количества считанных чисел из файла
//g и gg используются для определения направления движения по последовательности (по возрастанию или убыванию)
//u используется для подсчета количества четных чисел в последовательности
 
    while (fscanf(f, "%d", &x) == 1) {
        if (i == 0) {
            k = x;
            if (x%2 == 0) s += k;
        }
        else {
            if (x >= k) {g = 1};
            else {g = -1};
 
            if (x%2 == 0 && g == 1 && gg == 1) { s += x; u++; }
 
            if (g == 1 && gg == -1) {
                if (k%2 == 0) { s += k; u++; }
                if (x%2 == 0) { s += x; u++; }
            }
 
            gg = g;
            k = x;
        }
        i++;
    }
 
    if (u == 0) {s = 0};
    if (i == 0) {s = 1};
    return s;
}
 
int main(void)
{
    FILE *f;
    char name[100] = {0};
 
    int s;
 
    printf("File: ");
    fgets(name, sizeof(name)-1, stdin);
    name[strlen(name)-1] = 0;
    f = fopen(name, "r");
    if (f == NULL) {
        printf("Can't open file \n");
        return -1;
    }
 
    s = fun(f);
 
    if (s%2 == 0) printf("%d \n", s);
    if (s == 1) printf ("Пустая или еденичная последовательность");
    return 0;
}