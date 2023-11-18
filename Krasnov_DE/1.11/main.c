#include <stdio.h>
#include <stdlib.h>

int quantity(FILE*f1);

int quantity(FILE*f1){
    int staroe=0, pred=0, tek;
    int amount = 0;
    int flag = fscanf(f1, "%d", &tek);
    while(flag != -1){//öèêë ñ÷èòûâàþùèé âñå ÷èñëà èç ïîñëåäîâàòåëüíîñòè
        if(flag == 0){
            return -1;
            break;
        }
        else{

            if (tek == pred && tek == staroe){
                amount = amount + 1;
            }
            if(tek == pred && tek != staroe){
                amount = amount + 2;
            }
            staroe = pred;
            pred = tek;
        }
        flag = fscanf(f1, "%d", &tek);
    }
    return amount;

}


int main(){
    int s;
    FILE *f1;
    f1=fopen("input.txt","r");
    if(f1 == NULL){
        printf("file not open");
        return -1;
    }
    s=quantity(f1);
    fclose(f1);
    if(s == 0){
        printf("net takih uchastkov");
    }
    if(s > 0)
        printf("kol-vo elementov v post. uchastkah ranvo %d", s);
    if(s == -1)
       printf("oshibka");





}
