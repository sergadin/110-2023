#include <stdio.h>
#include <stdlib.h>
#define ER_READ -1
#define ER_MEMORY -2
#define NOT_SUCCESS -3
#define SUCCESS 0
#define SUCCESS_1 -4
#define SUCCESS_2 -5

int compare(int *mas_a, int *mas_b, int length_a, int length_b);

int compare(int *mas_a, int *mas_b, int length_a, int length_b){

int i = 0;
int j = 0;
int good = 0; // счетчик для сравнения массивов

if(length_a > length_b){
return NOT_SUCCESS;
}

if(length_a < length_b){
for(i = 0; i < length_a; i++){
for(j = 0; j < length_b; j++){
if(mas_a[i] == mas_b[j]){
good++;
break;
}
}
}
if(length_a == good){
return SUCCESS_1;
}
else{
return NOT_SUCCESS;
}
}


if(length_a == length_b){
for(i = 0; i < length_a; i++){
for(j = 0; j < length_b; j++){
if(mas_a[i] == mas_b[j]){
good++;
break;
}
}
}
if(length_a == good){
return SUCCESS_2;
}
else{
return NOT_SUCCESS;
}
}
return NOT_SUCCESS;
}


int main(void)
{
FILE* input_a;
FILE* input_b;
int *mas_a = NULL; // массив А
int *mas_b = NULL; // массив В
int length_a; // длина массива A
int length_b; // длина массива B
int i=0; // счетчик
int res; // результат работы функции

input_a = fopen("inputA.txt", "r");
if(input_a == NULL){
printf("Ошибка чтения файла\n");
return ER_READ;
}

input_b = fopen("inputB.txt", "r");
if(input_b == NULL){
printf("Ошибка чтения файла\n");
return ER_READ;
}


if((fscanf(input_a, "%d", &length_a)) != 1){
printf("Ошибка введенного массива А\n");
return ER_READ;
}

if((fscanf(input_b, "%d", &length_b)) != 1){
printf("Ошибка введенного массива В\n");
return ER_READ;
}

mas_a = (int*) malloc((length_a) * sizeof(int));
mas_b = (int*) malloc((length_b) * sizeof(int));

if(mas_a == NULL){
printf("Ошибка памяти\n");
free(mas_a);
free(mas_b);
return ER_MEMORY;
}

if(mas_b == NULL){
printf("Ошибка памяти\n");
free(mas_a);
free(mas_b);
return ER_MEMORY;
}

for(i = 0; i < length_a; i++){
if((fscanf(input_a, "%d", &mas_a[i])) != 1){
printf("Ошибка чтения файла\n");
free(mas_a);
free(mas_b);
return ER_READ;
}
}

for(i = 0; i < length_b; i++){
if((fscanf(input_b, "%d", &mas_b[i])) != 1){
printf("Ошибка чтения файла\n");
free(mas_a);
free(mas_b);
return ER_READ;
}
}

res = compare(mas_a, mas_b, length_a, length_b);

if(res == NOT_SUCCESS){
printf("В массивах встречаются неравные элементы или размер А > В\n");
free(mas_a);
free(mas_b);
return NOT_SUCCESS;
}

if(res == SUCCESS_1){
printf("A ⊂ B\n");
free(mas_a);
free(mas_b);
return SUCCESS;
}
if(res == SUCCESS_2){
printf("A = B\n");
free(mas_a);
free(mas_b);
return SUCCESS;
}
}
