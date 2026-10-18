include "determinant.h"


typedef struct{  	//структура теста
    const char* inp;
    double exp;
} Test;


int main(void){
    FILE* input;
    int n;   	 		// размер матрицы
    int length; 		// количество тестов
    double** mat; 		// массив для матрицы
    double res;
    int p = 1;

    Test tests[] = {
        {"test1.txt", -9.20811},
        {"test2.txt", 0},
        {"test3.txt", -450.606},
    };

    length = sizeof(test) / sizeof(test[0]);

    for(int i = 0; i < length; i++){
        result = 0;
        if((input = fopen(tests[i].inp, "r")) == NULL){
            printf("FILE_ERROR Test %d", i + 1);
            return -1;
        }
	if(fscanf(input, "%d", &n) != 1){
            printf("FILE_ERROR Test %d", i + 1);
            fclose(input);
            return -1;
        }

	mat = (double**)malloc(n * sizeof((double*) * n));
        if(mat == NULL){
            printf("MALLOC_ERROR Test %d", i + 1);
            fclose(input);
            return -1;
        }

	for (int i = 0; i < n; i++){
		mat[i] = (double*)malloc(n * sizeof(double));
		if (mat[i] == NULL){
			printf("MALLOC_ERROR\n");
			fclose(input);
			free(mat);
			return -1;
		}
	}

        for(int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
	            if((fscanf(input, "%d", &mat[i][j])) != 1){
        	        printf("FILE_ERROR Test %d", i + 1);
                	fclose(input);
                	free(mat);
                	return -1;
            		}
		}
        }
	for (int i = 0; i < n; i++){
		p *= (-1);
	}
	res = calculate(&mat, n, p, 0);
        if (fabs(res - test[i].exp) < 1e-4){
            printf("Тест №%d успешно пройден\nОпределитель = %lf\n", i + 1, res);
        }
        else{
            printf("Тест №%d не пройден\n", i + 1);
        }

        fclose(input);
        free(arr);
        free(mat);
    }
    return 0;
}


