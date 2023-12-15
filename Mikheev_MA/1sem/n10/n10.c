#include<stdio.h>
#define SUCCESS 0
#define ER_READ -1
#define ER_OPEN -2

int square(int b){ // вспомогательная функция создана, что возводить число в квадрат
    return b = b*b;
}

int degree(int a, int res, int n){ // функция на входе получает число а и степень n,в результате возвращает число a^n
    int i, j; // счетчики
  if(n & 1){
      n = n >> 1;
      res = a;
  }
  else{
      n = n >> 1;
  }
  
    for(i = 1; i < (sizeof(int) * 8); i++){
        if (n & 1){
            int b = a;
            for(j = 0; j < i; j++){
                b = square(b);
            }
            res = res * b;
        }
        n = n >> 1;
    }
    return res;
}

int main(void)
{
  int  res = 1; // переменна, которая выдает результат возведения в степень
  int n; // степень, в которую возводят число
  int a; // число, которое возводят в степень n
  
  FILE* input;
  input = fopen("input.txt", "r");
  if(input == NULL){
      printf("Ошибка открытия файла\n");
      return ER_OPEN;
  }
  
  if((fscanf(input, "%d", &a)) != 1){
      printf("Ошибка чтения файла\n");
      fclose(input);
      return ER_READ;
  }
  
    if((fscanf(input, "%d", &n)) != 1){
      printf("Ошибка чтения файла\n");
      fclose(input);
      return ER_READ;
  }

  res = degree(a, res, n);
  
  printf("Результат - %d\n", res);
  
  return SUCCESS;
}
