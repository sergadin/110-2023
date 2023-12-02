#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define NOT_OK -1
#define Error -2
FILE* data;
 
 
 
int dense(int *array, int N);
 
 
int dense(int *array, int N){
       int a;
       int b;
       int cnt=0;
 
       printf("введите число a");
       scanf("%d", &a);
       printf("введите число b");
       scanf("%d", &b);
       
       if (a>b || a>N || b>N){
       		return Error;
       }
 
       for(int i=0; i < N; i++){
               if ((array[i] >= a) && (array[i] <=b)){
                       cnt++;
                       for(int j=i+1; j<N; j++){
                               if(array[j]==array[i]){

                               		array[j]=b+10;
                               }
                       }
               }
       }
 
       if (cnt == b - a + 1)
               return OK;
       else
               return NOT_OK;
}
int main(void){
        int itog;
        int n;
        FILE *answer;
        int *array = NULL;
    answer = fopen("output.txt", "w");
 
        if (!answer) {     //Проверка существует ли answer
        printf("What?");
        return -1;
        }
 
    data = fopen("np.txt", "r");
 
        if (!data) {     //Проверка есть ли data
        printf("ERR");
        return -1;
        }
 
 
 
        if (fscanf(data, "%d", &n)!=1){//Проверяем, считалось ли число
                printf("no values\n");
                return -1;
        }
 	printf("len - %d\n", n);
        array = (int *)malloc(n*sizeof(int));
        for (int i = 0; i < n; i++){
                if(fscanf(data, "%d", &array[i]) != 1) {
                        printf("FGH");
                        return -1;
                }// считался ли элемент
        }
 
        for (int i = 0; i < n;i++){
                printf("%d\n", array[i]);
        }
 
        fclose(data);
        itog = dense(array, n);
 
        if (itog == OK) {
                printf("плотный");
        }
        if (itog == NOT_OK){
                printf("не плотный");
 
        }
        if (itog == Error){
        	printf("Ввели некорректные границы\n");
        }
 
        fclose(answer);
    return 0;
}

