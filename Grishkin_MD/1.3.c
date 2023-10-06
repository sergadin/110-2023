#include <stdio.h>

int main () {
FILE *file;

float number;
float sum = 0;
int count = 0;

file = fopen ("numbers.txt", "r");
if (file = NULL) {
printf("Не удалось открыть файл\n");
return -1;
}
while (fscanf(file,"%f", &number) ==1) {
sum +=1/number;
count ++;
}
fclose(file);
if (count > 0) {
float average = count/sum;
printf("Среднее гармоническое из последовательности:%f\n", average);
}
return 0;
}