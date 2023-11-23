//2.8 Удалить из целочисленного массива одинаковые значения, т.е. если какое-то значение встречается несколько раз 
//    (в разных местах массива), то оставить только первый такой элемент, а остальные удалить из массива. 
//    Оставшиеся элементы сдвинуть к началу массива, и указать их количество.
#include <stdio.h>
#include <stdlib.h>

int sdvig_i_schet_itog_len(int *mas, int len);
//преобразует массив mas: если какое-то значение встречается несколько раз, 
//то оставляет только первый такой элемент, а от остальных избавляется, 
//сдвигая оставшиеся элементы массива влево
//также считает итоговую длину (itog_len) изменённого массива mas


int sdvig_i_schet_itog_len(int *mas, int len)
{
	int itog_len = len;

	if (len == 0) {
        printf("net massiva, len = 0\n");
        return itog_len;
    }
	
	if (len == 1) {
        return itog_len;
    }
	
	for (int i = 0; i < len; i++) {
		for (int j = (i + 1); j < len; j++) {
			if (mas[i] == mas [j]) {
				for (int k = j; k < (len - 1); k++) {
					mas[k] = mas[k + 1];
				}
				len--;
				j = j - 1; //"шаг назад"  
				//чтобы смогли рассмотреть новое число на позиции, с которой только что "убрали" неподходящее нам число
				//(без этого будем "перескакивать" через число на той позиции, на которую только что сдвинули числа)
			}
		}
	}
	
	itog_len = len;
	
	return itog_len;
}


int main(void) {
	int len, itog_len_ravna;
	int* mas = NULL;
	FILE *file_in = fopen("input.txt", "r");
	FILE *file_out = fopen("output.txt", "w");
    
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
	
	mas = (int*) malloc((len)*sizeof(int));
	
	if (mas == NULL) {
		printf("Memory error\n");
		fclose(file_in);
		fclose(file_out);
		return -1;
	}
	
	for (int i = 0; i < len; i ++) {
		if (fscanf(file_in, "%d", &mas[i]) != 1) {
			printf("error, problema s tipom elementov massiva / dlina massiva < len\n");
			free(mas);
			fclose(file_in);
			fclose(file_out);
			return -1;
		}
	}
	
	itog_len_ravna = sdvig_i_schet_itog_len(mas, len);
	
	fprintf(file_out, "itog_len = %d\n", itog_len_ravna);
	for (int h = 0; h < itog_len_ravna; h++) {
		fprintf(file_out, "%d ", mas[h]);
	}
	
	if (len != 0) {
		printf("rezultat napechatan \n");	
	}
	
	free(mas);
	fclose(file_in);
	fclose(file_out);
	return 0;
}