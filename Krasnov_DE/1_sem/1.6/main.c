#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int poryadok(FILE *f1,float x);

int main(void){

    int s,a;
    float x;
    FILE *f1;
    char m[20];
    printf("vvedi nazvanie file\n");
    scanf("%s", m);
    f1 = fopen(m, "r");
    if(f1 == NULL){
        printf("file not open");
        return -1;
    }

    printf("vvedi X\n");
    a = scanf("%f",&x);
    if(a != 1){
        printf("vvedeno ne chislo");
        return -1;
    }

    s = poryadok(f1,x);
    fclose(f1);
    if(s == -2)
        printf("net chisla");

    if(s == -1)
        printf("file pust or est chars");

    if(s > 0)
        printf("chislo stoint na %d meste",s);

        return 0;
}


int poryadok(FILE *f1, float x){
    float chislo;
    int nomer = -2, k = 0;
    float eps = 0.000001;
    int a;
    while((a = fscanf(f1, "%f", &chislo)) != EOF){//цикл считывающий все числа из последовательности
        if(a != 1){
            return -1;
        }
        k = k + 1;
        if (fabs(chislo-x) <= eps){
            nomer = k;
        }
    }
    if(k == 0){
        nomer = -1;
    }
    return nomer;
}



