//2.3 Циклически сдвинуть элементы массива на одну позицию вправо

//(определяю длину массива, считывая первый элемент в файле)

#include <stdio.h>
#include <stdlib.h>

void cyclic_Shift_Right(double* mas, int len);
//получает на вход массив (mas) и его длину (len)
//функция измененяет полученный на вход массив mas, циклически сдвигая каждый его элемент вправо


void cyclic_Shift_Right(double* mas, int len) {
    double posled_el;
    
	if (len == 1) {     //нечего сдвигать, т к массив состоит из одного элемента
		return;
	}
	
	posled_el = mas[len - 1];    //сохраняем последний элемент массива
	
	for (int i = len - 1; i > 0; i--) {		//сдвигаем элементы массива вправо
		mas[i] = mas[i - 1];
	}
	
	mas[0] = posled_el;    //помещаем сохраненное значение в начало массива
}


int main(void) {
	int len; //длина массива
	FILE *file_in = fopen("input.txt", "r");
	FILE *file_out = fopen("output.txt", "w");
    double *mas;
	int is_elem_len; //будем считывать элемент в массиве на месте len
    
	if (file_in == NULL) {
		printf("error opening the file_in\n");
		return -1;
	}
	
	if (fscanf(file_in, "%d", &len) != 1) {
		printf("error, v faile pusto / ne tot tip y dlinu\n");
		return -1;
	}
	
	if (len == 0) {
		printf("error, net massiva\n");
		return -1;
	}
	
	if (len < 0) {
		printf("error, otrizat dlina massiva\n");
		return -1;
	}
	
	mas = (double*) malloc((len)*sizeof(double));
	
	for (int i = 0; i < len; i ++) {
		if (fscanf(file_in, "%lf", &mas[i]) != 1) {
			printf("error, problema s tipom elementov massiva / dlina massiva < len\n");
			return -1;
		}
	}
	
	is_elem_len = fscanf(file_in, "%lf", &mas[len]);
    
    if (is_elem_len != EOF) {
        printf("error, dlina massiva > len\n");
        return -1;
    }
	
	fclose(file_in);
	
	cyclic_Shift_Right(mas, len);
	
	for (int i = 0; i < len; i++) {
		fprintf(file_out, "%lf ", mas[i]);
	}
	
	printf("rezultat napechatan\n");
	
	free(mas);
	fclose(file_out);
	
	return 0;
}