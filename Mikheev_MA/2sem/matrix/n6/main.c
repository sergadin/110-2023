#include "MethZeyd.h"



typedef struct{  //структура теста
    const char* inp;  //название файла
    double *res;   // ожидаемый результат
    Er error;  // код ошибки
}Testcase;


int main(void){
    FILE* input;
    int m, n; // размер матрицы
    int length; // количество тестов
    double **matr = NULL; // массив для матрицы
    double *arr = NULL; // массив решений
    Er error = OK;
    double EPS = 0.00000001;

    
    Testcase test[] = {
        {"input1.txt", (double[]){2.25, -0.75, -0.75}, OK},
        {"input2.txt", (double[]){3, 0.5, 1}, OK},
        {"input3.txt", (double[]){3, -3}, OK}
        
    };
    
    length = sizeof(test) / sizeof(test[0]);

    
    for(int l = 0; l < length; l++){
        if((input = fopen(test[l].inp, "r")) == NULL){
            printf("Ошибка открытия файла в тесте №%d", l + 1);
            return -1;
        }
        if(fscanf(input, "%d %d", &n, &m) != 2){
            printf("Ошибка чтения файла в тесте №%d", l + 1);
            fclose(input);
            return -1;
        }

        matr = (double**)malloc(n * sizeof(double*));
		if (matr == NULL) {
			printf("Ошибка выделения памяти в тесте №%d\n", l + 1);
			fclose(input);
			return -1;
		}
		for (int i = 0; i < n; i++) {
			matr[i] = (double*)malloc(m * sizeof(double));
			if (matr[i] == NULL) {
				printf("Ошибка выделения памяти в тесте №%d\n", l + 1);
				fclose(input);
				return -1;
			}
		}
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (fscanf(input, "%lf", &matr[i][j]) != 1) {
					printf("Ошибка чтения файла в тесте №%d\n", l + 1);
					fclose(input);
					for (int k = 0; k < n; k++) {
						free(matr[k]);
					}
					free(matr);
					return -1;
				}
			}
		}
		
		//for(int i = 0; i < n; i++){
		//    for(int j = 0; j < m; j++){
		//        printf("%lf\t", matr[i][j]);
		//    }
		//    printf("\n");
		//}
		
		arr = (double*)malloc(n * sizeof(double));
		if(arr == NULL){
			printf("Ошибка выделения памяти в тесте №%d\n", l + 1);
			fclose(input);
			for (int i = 0; i < n; i++){
				free(matr[i]);
			}
			free(matr);
			return -1;
		}
		
		
		for(int i = 0; i < n; i++){
		    arr[i] = 0;
		}
		
		MethZeyd(matr, &arr, &error, n, m, EPS);
		
		
		for(int i = 0; i < n; i++){
		    if(fabs(arr[i] - test[l].res[i]) > EPS || error == LIMIT || error == NOT_CORRECT){
		        printf("Тест №%d не пройден\n", l + 1);
		        break;
		    }
		}
		if(error == OK){
		    printf("Тест №%d успешно пройден\n", l + 1);
		    for(int i = 0; i < n; i++){
                printf("x%d = %lf\n", i + 1, arr[i]);
            }
		}
		printf("\n");
		for (int i = 0; i < n; i++){
			free(matr[i]);
		}
		free(matr);
		free(arr);
		fclose(input);
    }
    return 0;
}