#include <stdio.h>
FILE* data;
int count( double A, double e);
//Функция считывает количество вхождений A в файл с точностью до e
double fabs_(double a);


double fabs_(double a) {
 if (a < 0)
    return -a;
 else 
    return a;
}


int count( double A, double e){
  double el;
  int cnt = 0;
  while (fscanf(data, "%lf", &el)==1){ //Проверка, считалось ли число
       if (fabs_(el - A) <= e)
        cnt++;
     
  }
  return cnt;
}


int main(void) {
  FILE *answer = fopen("output.txt", "w");
  double x, e;
  int r;
        printf("Ввод x и e\n");
  if (scanf("%lf%lf", &x, &e) != 2) {// Проверка, считалось ли 2 числа
  	printf("mistake");
  	return 0;
  }
  if (!answer) {
      printf("What?");
      return -1;
  }
  data = fopen("input.txt", "r");
  if (!data)// Отклылась ли успешно data
    return -1;
   r = count( x, e);
  if (!feof(data))// Достигло ли конца файла
  {
  	printf("nums only!");
       fclose(data);
       return -2;
  }
  fclose(data);
  if (fprintf(answer, "%d", r) == 0) {
      printf("NO SUCCESS!!");
      return -2;
  }
  fclose(answer);
  
  return 0;
}
