#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define NOT_OK -1
FILE* data;
 
void swap(int *x, int *y);  
 
int dense(int *array, int N);
 
void swap(int *x, int *y) {//bubble sort
	int t = *x;
	*x = *y;
	*y = t;
}
int dense(int *array, int N){
      int f;
        f = 1;

      
       for(int i =0; i < N; i++){
              for (int j = 0; j < N - i - 1; j++) {
              		if (array[j + 1] < array[j]) {
              			swap(&array[j], &array[j + 1]);
              		}
              }
       }
 	
 	for (int i = 1; i < N; i++) {
 		if (array[i - 1] - array[i] < -1) f = 0;//Флаг сработает, если разность по модулю больше 1, т.е не найдётся элемент
 	}
       if (f)
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
  
        fclose(data);
        itog = dense(array, n);
        
        if (itog == OK) {
                printf("плотный");
        }
        if (itog == NOT_OK){
                printf("не плотный");
 
        }
 
        fclose(answer);
    return 0;
}
