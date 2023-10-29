#include <stdio.h>
#include <stdlib.h>


float tochka (char name[20], float x){
FILE *f1 ;
f1 = fopen (name, " r ") ;
float chislo, znajenie_v_tochke = 0, stepen_x = 1;
int flag = 0 ;
while(fscanf (f1, " %f ", &chislo) != EOF){ //цикл считывающий все числа из последовательности
        znajenie_v_tochke = znajenie_v_tochke + chislo * stepen_x ;
        flag = flag + 1;
        stepen_x = stepen_x * x;
}
fclose(f1);
return znajenie_v_tochke;
}


float proizvodnaya (char name[20], float y){
FILE *f1;
f1 = fopen(name,"r");
float chislo, proizvodnay_v_tochke = 0, stepen_y = 1;
int flag = 0;
while(fscanf(f1, " %f ", &chislo) != EOF){ //цикл считывающий все числа из последовательности
        if(flag >= 1){
            proizvodnay_v_tochke = proizvodnay_v_tochke + chislo * stepen_y * flag;
            stepen_y = stepen_y * y;
        }
        flag = flag + 1;

}
fclose(f1);
return proizvodnay_v_tochke;
}


int main(){

float c, z;
char file_name[20];
printf("vvedi nazvanie file\n");
scanf("%s", file_name);
FILE *f1;
f1 = fopen(file_name, "r");
if(f1 == NULL){
    printf("file not open");
    return -1;
}
if(fscanf (f1, "%f", &z) == EOF){
    printf("file pust");
    return -1;
}
printf("vvedi tochku X\n");
scanf("%f", &c);
printf("znajenie v tochke x ravno %f\n", tochka(file_name, c));
printf("znajenie proizvod v tochke x ravno %f", proizvodnaya(file_name, c));
fclose(f1);

    return 0;
}
