#include <stdio.h>
FILE* data;
int det_number(FILE* data);
//Функция определяет порядковый номер первого максимального числа


int det_number(FILE* data)
{
	int current = 0;
	int index = 0;
	int max_val;
	int cnt = 0;
	      if (fscanf(data, "%d", &max_val) !=1){//Проверка считалось ли число
                 printf("mistake");
		 return 0;
       } 
       cnt = 1;
	while (fscanf(data, "%d", &current) ==1){
		cnt++;
		if (max_val<current){
			max_val = current;
			index = cnt;
		}
	
	}
	return index;
}

 int main(void){
	FILE *answer;
	int r;
	answer = fopen("output.txt", "w");
	data = fopen("input.txt", "r");

 
       if (!answer){// Проверка есть ли ansver
		printf("What?");
 		return -1;
       }

       if (!data)//Есть ли data
       
	    return -1;
	 r = det_number(data);

 
       if (!feof(data))//Проверка достижения конца файла
      {
         fclose(data);
	 printf("NoNoNO!!!");
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
