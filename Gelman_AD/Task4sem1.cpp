#include<stdio.h>
#include<<stdlib.h>>

//здесь вывести принтф считывания К
//считываем К
printf("Enter the value of shifting the mas\n");
fscanf(&K);

while 
//сюда запихнуть функцию сдвига массива

//(определяю длину массива, считывая первый элемент в файле)

void cyclic_Shift_Right(double* mas, int len);
//получает на вход массив (mas) и его длину (len)
//функция измененяет полученный на вход массив mas, циклически сдвигая каждый его элемент вправо


void cyclic_Shift_Right(double* mas, int len) {
	double posled_el;

	if (len == 0) {
		printf("net massiva, len = 0\n");
		return;
	}

	if (len == 1) {     //нечего сдвигать, т к только один элемент
		return;
	}

	posled_el = mas[len - 1];    //сохраняем последний элемент массива

	for (int i = len - 1; i > 0; i--) {		//сдвигаем элементы массива вправо
		mas[i] = mas[i - 1];
	}

	mas[0] = posled_el;
}


int main(void) {
	int len; //длина массива
	FILE* file_in = fopen("input.txt", "r");
	FILE* file_out = fopen("output.txt", "w");
	double* mas = NULL;

	if (file_in == NULL) {
		printf("error opening the file_in\n");
		return -1;
	}

	if (file_out == NULL) {
		printf("error opening the file_out\n");
		fclose(file_in);
		return -1;
	}

	if (fscanf(file_in, "%d", &len) != 1) {
		printf("error, v faile pusto / ne tot tip y dlinu\n");
		fclose(file_in);
		fclose(file_out);
		return -1;
	}

	mas = (double*)malloc((len) * sizeof(double));

	if (mas == NULL) {
		printf("Memory error\n");
		fclose(file_in);
		fclose(file_out);
		return -1;
	}

	for (int i = 0; i < len; i++) {
		if (fscanf(file_in, "%lf", &mas[i]) != 1) {
			printf("error, problema s tipom elementov massiva / dlina massiva < len\n");
			free(mas);
			fclose(file_in);
			fclose(file_out);
			return -1;
		}
	}

	cyclic_Shift_Right(mas, len);

	for (int i = 0; i < len; i++) {
		fprintf(file_out, "%lf ", mas[i]);
	}

	if (len != 0) {
		printf("rezultat napechatan\n");
	}

	free(mas);
	fclose(file_in);
	fclose(file_out);

	return 0;
}