#include <stdio.h>


int counter(FILE*);
//Функция считает общее количество элементов в постоянных участках последовательности


int main(void){

	FILE *fin, *fout;
	int Result;	

	fin = fopen("input.txt", "r");
	if (fin == NULL){
		printf("Не удалось открыть файл 'input.txt'\n");
		return -3;
	}	

	Result = counter(fin);

	fout = fopen ("output.txt", "w");
	if (fout == NULL){
		printf("Не удалось открыть файл 'output.txt'\n");
		return -3;
	}

	fprintf (fout, "%d\n", Result);

	fclose(fin);
	fclose(fout);

	return 0;
}

	
int counter(FILE *fin){
	int counter = 0;	//искомое количество
	double first_num;
	double medium_num;
	double last_num;

	if (fscanf(fin, "%lf", &medium_num) != 1){
               printf ("Файл пуст\n");
               return -2;
        }

        last_num = medium_num + 1; 

        while ( fscanf(fin, "%lf", &first_num)  == 1) {
                if (medium_num == first_num || medium_num == last_num){
                        counter += 1;
                }
                last_num = medium_num;
                medium_num = first_num;
        }

        if (feof (fin) == 0){
                printf("Файл не прочитался до конца\n");
                return -1;
        }

        if (medium_num == last_num){
                counter += 1;
        }

	return counter;
}

