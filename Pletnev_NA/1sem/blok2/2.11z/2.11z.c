#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define Error_File_NOT_Exist -666
#define Error_Invalid_Data -555
#define Error_Unallocated_Memory -444
#define Error_Array_Empty -333
#define Result_Answer 222

int ShiftTheArrayByPositionK(int* arr,int len, int k);


//функция, которая сдвигает элементы на k позиций вправо
int ShiftTheArrayByPositionK(int* arr, int len, int k) {

	if (arr == NULL) {
		printf("Error:The array is empty\n");
		return Error_Array_Empty;
	}

	k %= len;

    int i;
    int j;
    int cnt = 0;
    int c;
    
    //перебор всех вохможных цепоцек
    for (int i0 = 0; cnt < len; i0++) {
        
        i = i0;
        c = a[i];
        
        for (j = ((i + k)%len); j != i0; j = ((j + k)%len)) {
            a[i] = a[j];
            cnt++;
            i = j;
        }
        
        a[i] = c;
        cnt++;
    
    }
    
}


int main(void) {

	FILE* inp_f;		// -файл наших значений для обработки
	FILE* out_f;		// -файл для вывода ответа
	char fi[30];		// -вспомогательная перемнная для ввода имени файла наших значений
	char fo[30];		// -вспомогательная перемнная для для ввода имени файла ответ
	int code = 0;		// -резултат фнукции
	int* arr = NULL;	// -наш массив для работы
	int len;			// -длина нашего массива
	int k;				// -число на которое нужно сдвинуть элементы массива

	printf("Enter the name of the input file:\n");
	scanf("%s", fi);

	//открыли файл для чтения
	inp_f = fopen(fi, "r");

	//проверяем существование файла. если его нет, выводим ошибку
	if (inp_f == NULL) {
		printf("Error: The file '%s' does not exist\n", fi);
		code = Error_File_NOT_Exist;
	}

	if (fscanf(inp_f, "%d", &len) != 1) {
		return Error_Invalid_Data;
	}

	arr = (int*)malloc((len + 1) * sizeof(int));

	if (arr == NULL) {
		printf("Error: RAM is not allocated\n");
		code = Error_Unallocated_Memory;
	}

	for (int i = 0; i < len; i++) {

		if (fscanf(inp_f, "%d", &arr[i]) != 1) {
			printf("Error: Invalid data entry. Check the file '%s'\n", fi);
			code = Error_Invalid_Data;
		}

	}

	//закрыли файл для чтения
	fclose(inp_f);

	if (code != 0) {
		return code;
	}

	printf("Enter the number by which you want to shift all array elements:\n");
	scanf("%d", &k);

	for (int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}

	code = ShiftTheArrayByPositionK(arr, len, k);

	if (code != Result_Answer) {
		return code;
	}
	

	for (int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}

	printf("Enter the name of the output file:\n");
	scanf("%s", fo);

	//открыли файл для записи
	out_f = fopen(fo, "w");

	printf("The result is uploaded to the file '%s'\n", fo);

	for (int i = 0; i < len; i++) {
		fprintf(out_f, "%d ", arr[i]);
	}

	//закрыли файл для записи
	fclose(out_f);
	free(arr);

	return code;
}
