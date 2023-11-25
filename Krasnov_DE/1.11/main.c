#include <stdio.h>
#include <stdlib.h>

int quantity(FILE*f1);



int main(void){
    int s;
    FILE *f1;
    f1=fopen("input.txt", "r");
    if(f1 == NULL){
        printf("file not open");
        return -1;
    }
    s = quantity(f1);
    fclose(f1);
    if(s == 0)
        printf("net takih uchastkov");

    if(s > 0)
        printf("kol-vo elementov v post. uchastkah ranvo %d", s);

    if(s == -1)
       printf("est char or float chisla");

    if(s == -2)
       printf("file pust");

    return 0;

}



int quantity(FILE*f1){
    float staroe=0.5, pred=0.5, tek;
    int amount = 0;
    int flag ;
    int k=0;
    while((flag=fscanf(f1, "%d", &tek))!=EOF ){//öèêë ñ÷èòûâàþùèé âñå ÷èñëà èç ïîñëåäîâàòåëüíîñòè
        if(flag != 1){
            return -1;
        }

        if (tek == pred && tek == staroe){
            amount = amount + 1;
        }

        if(tek == pred && tek != staroe){
            amount = amount + 2;
        }

        staroe = pred;
        pred = tek;
        k++;
    }

    if(k==0){
        return -2;
    }

    return amount;

}
