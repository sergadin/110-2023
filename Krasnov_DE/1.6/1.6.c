#include <stdio.h>
#include <stdlib.h>
int poryadok(char c[20]){
FILE *f1;
f1=fopen(c,"r");
float chislo,x;
int nomer,k=0;
float e=0.000001;
printf("vvedi X\n");
scanf("%f",&x);
while(fscanf(f1,"%f",&chislo)!=EOF){ //цикл считывающий все числа из последовательности
        k=k+1;
        if (fabs(chislo-x)<e){
            nomer=k;
        }
}
fclose(f1);
return nomer;
}

int main(){

int s;
char m[20];
printf("vvedi nazvanie file\n");
scanf("%s",m);
FILE *f1;
f1=fopen(m,"r");
if(f1==NULL){
    printf("file not open");
    return -1;
}
s=poryadok(m);
fclose(f1);
if(s==0){
    printf("net chisla");
}
else
    printf("chislo stoint na %d meste",s);

    return 0;
}
