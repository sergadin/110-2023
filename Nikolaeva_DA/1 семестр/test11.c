#include <stdio.h>

int count(const char* name, double x, double e);
// Функция считывает колличество вождений X в файл с точность до эпсилон//
double fabs_(double a);

double fabs_(double a) {
 if (a < 0)
    return -a;
 else 
    return a;
}


int count(const char* name, double x, double e){
  double A;
  int cnt = 0;
  FILE* data;
  
  data = fopen(name, "r");
  if (!data)
    return -1;
  if(fscanf(data, "%lf", &A) != 1) 
  {
      printf("??");
      
  }
  while (fscanf(data, "%lf", &x)==1){
       if(fabs_(x - A) <= e) 
	       cnt++;
  }
  if(!feof(data))
  {
       fclose(data);
       return -2;
  }
  fclose(data);
  return cnt;
}
int main(void)	
{
  FILE *answer = fopen("output.txt", "w");
  double x, e;
  printf("Значение переменной X: \n");
  scanf("%lf", &x);
  printf("Значение переменной e: \n");
  scanf("%lf", &e);

  if (!answer) {
      printf("What?");
      return -1;
  }
  if (fprintf(answer, "%d", count("input.txt",x, e)) == 0) {
      printf("NO SUCCESS!!");
      return -2; }
  fclose(answer);
  return 0;
}

