#include <stdio.h>
#include <stdlib.h>
int quantity(char c[20]){
FILE *f1;
f1=fopen(c,"r");
int staroe=0,pred=0,tek;
int k=0;
while(fscanf(f1,"%d",&tek)!=EOF){ //цикл считывающий все числа из последовательности
        if (tek==pred && tek==staroe){
            k=k+1;
        }
        if(tek==pred && tek!=staroe){
            k=k+2;
        }
        staroe=pred;
        pred=tek;
}
fclose(f1);
return k;
}

int main()
{
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
s=quantity(m);
fclose(f1);
if(s==0){
    printf("net takih uchastkov");
}
else
    printf("kol-vo elementov v post. uchastkah ranvo %d",s);

    return 0;
}
