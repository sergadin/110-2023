#include <stdio.h>
#include <stdlib.h>
float tochka(char c[20],float x){
FILE *f1;
f1=fopen(c,"r");
float chislo;
int k=0;
float s=0;
while(fscanf(f1,"%f",&chislo)!=EOF){ //цикл считывающий все числа из последовательности
        s=s+chislo*powf(x,k);
        k=k+1;
}
fclose(f1);
return s;
}

float proizvodnaya(char c[20],float y){
FILE *f1;
f1=fopen(c,"r");
float chislo;
int k=0;
float p=0;
while(fscanf(f1,"%f",&chislo)!=EOF){ //цикл считывающий все числа из последовательности
        if(k>=1){
            p=p+chislo*powf(y,k-1);
        }
        k=k+1;
}
fclose(f1);
return p;
}


int main(){

float a,b,c;
char m[20];
printf("vvedi nazvanie file\n");
scanf("%s",m);
FILE *f1;
f1=fopen(m,"r");
if(f1==NULL){
    printf("file not open");
    return -1;
}
scanf("%f",&c);
a=tochka(m,c);
b=proizvodnaya(m,c);
fclose(f1);
printf("znajenie v tochke x ravno %f\n",a);
printf("znajenie proizvod v tochke x ravno %f",b);

    return 0;
}
