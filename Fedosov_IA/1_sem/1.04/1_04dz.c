#include <stdio.h>


int Schet(FILE*);
//Функция считает кол-во чисел, больших предыдущего


int main(void){
	FILE *fout, *fin;
	int Result;

	fin = fopen("input.txt", "r");
	if (fin == NULL){
		printf("Не удалось открыть файл 'input.txt'\n");
		return -3;
	}
	
	Result = Schet(fin);

	fout = fopen ("output.txt", "w");
	if (fout == NULL){
		printf("Не удалось открыть файл 'output.txt'\n");
		return -3;
	}

	fprintf (fout, "%d", Result);
	
	fclose(fin);
	fclose(fout);

	return 0;
}
	

int Schet(FILE *fin){
	int count = 0; 	//Кол-во чисел
	double current;					
	double previous;	

	if (fscanf(fin, "%lf", &previous) != 1){
		printf("В файле содержится не число\n");
		return -2; //Чтение первого значения из файла и проверка, что это число
	}

	while (fscanf(fin, "%lf", &current) == 1){
		if (current > previous){
			count ++;
		}
		previous = current;
	}

	if (feof (fin) == 0){
		printf("Файл не прочитался до конца\n");
		return -1;
	}

	return count;
}

					
