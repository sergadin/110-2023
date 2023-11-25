#include <stdio.h>
#include <stdlib.h>

int ERROR = 0 ;


float tochka (FILE *f1, float x);
float proizvodnaya (FILE *f2, float y);


int main(void){

    float c, a, b;
    FILE *f1;
    FILE *f2;
    f1 = fopen("input.txt", "r");
    f2 = fopen("input.txt", "r");
    if(f1 == NULL){
        printf("file not open");
        return -1;
    }
    printf("vvedi tochku X\n");
    scanf("%f", &c);
    a = tochka(f1, c);
    b = proizvodnaya(f2, c);
    if(ERROR == -1){
        printf("ERROR");
        return -1;
    }
    printf("znajenie v tochke x ravno %f\n", a);
    printf("znajenie proizvod v tochke x ravno %f", b);
    fclose(f1);
    fclose(f2);
    return 0;
}

float tochka (FILE *f1, float x){
    float chislo, znajenie_v_tochke = 0, stepen_x = 1;
    int flag = 0 ;
    int a;
    while((a = fscanf (f1, "%f", &chislo)) != EOF){//цикл считывающий все числа из последовательности
        if(a!=1){
            ERROR = -1;
            return -1;
        }
        znajenie_v_tochke = znajenie_v_tochke + chislo * stepen_x ;
        flag = flag + 1;
        stepen_x = stepen_x * x;
    }
    return znajenie_v_tochke;
}

float proizvodnaya (FILE *f2, float y){
    float chislo, proizvodnay_v_tochke = 0, stepen_y = 1;
    int flag = 0;
    int a;
    while((a=fscanf(f2, "%f", &chislo)) != EOF){ //цикл считывающий все числа из последовательности
        if(a != 1){
            ERROR=-1;
            return -1;
        }
        if(flag >= 1){
            proizvodnay_v_tochke = proizvodnay_v_tochke + chislo * stepen_y * flag;
            stepen_y = stepen_y * y;
        }
        flag = flag + 1;

    }
    return proizvodnay_v_tochke;
}




