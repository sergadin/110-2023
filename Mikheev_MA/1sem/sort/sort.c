#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <time.h>
#define ER_READ -1 
#define ER_MEMORY -2
#define NOT_CORRECT -3
#define CORRECT -4
#define RANDOM_OK -5
#define SUCCESS 0
#define ER_OPEN -6
#define FAILED -7

void generate_random_mas(int *mas, int length); // генерация рандомного массива
void sort_insert(int *mas, int length); // сортировка вставками
void swap_el(int *a, int *b); // функция меняет 2 элемента местами
int correct_sort(int *mas, int length); // корректность сортировки
void shift_down(int *mas, int k);
void shift_up(int *mas, int k);
void sort_heap(int *mas, int length);
int test(FILE* output, int *mas, int length); // тест сортировок указанной длины
int compare(const void* i, const void* j);



int compare(const void* i, const void* j){
	return (*(int*)i - *(int*)j);
}



int test(FILE* output, int *mas, int length){
    clock_t start_1, end_1, start_2, end_2, start_3, end_3;
    double time_1, time_2, time_3 = 0;
    
    generate_random_mas(mas, length);
    start_1 = clock();
    sort_insert(mas, length);
    end_1 = clock();
    time_1 = (double)(end_1 - start_1) / CLOCKS_PER_SEC;
    if(correct_sort(mas, length) == NOT_CORRECT){
        return FAILED;
    }
    
    generate_random_mas(mas, length);
    start_2 = clock();
    sort_heap(mas, length);
    end_2 = clock();
    time_2 = (double)(end_2 - start_2) / CLOCKS_PER_SEC;
    if(correct_sort(mas, length) == NOT_CORRECT){
        return FAILED;
    }
    
    generate_random_mas(mas, length);
    start_3 = clock();
    qsort(mas, length, sizeof(int), compare);
    end_3 = clock();
    time_3 = (double)(end_3 - start_3) / CLOCKS_PER_SEC;
    if(correct_sort(mas, length) == NOT_CORRECT){
        return FAILED;
    }
    
    
    fprintf(output, "Длина массива - %d\nВремя сортировки вставками - %lf\nВремя пирамидальной сортировки - %lf\nВремя qsort - %lf\n\n", length, time_1, time_2, time_3);

}



void sort_insert(int *mas, int length){
    int current;
    int j;
    
    for(int i = 1; i < length; i++){
        current = mas[i];
        j = i - 1;
        
        for(j; j >= 0 && mas[j] > current; j--){
            mas[j + 1] = mas[j];
        }
        mas[j + 1] = current;
    }
}



void sort_heap(int *mas, int length){
    int k;
    
	for (k = 1; k < length; k++){
		shift_up(mas, k);
	}
	for (k = length - 1; k > 0; k--){
		swap_el(mas, mas + k);
		shift_down(mas, k);
	}
}

void shift_up(int *mas, int k){
	int j;
	while(k > 0){
		j = (k - 1) / 2;
		if (mas[k] > mas[j]) {
			swap_el(mas + k, mas + j);
		}
		else {
			break;
		}
		k = j;
	}
}

void shift_down(int *mas, int k){
	int i, i1, i2;
	if(k < 2){
		return;
	}
	for(i = 0; i < k; ){
		i1 = 2 * i + 1;
		i2 = i1 + 1;
		if(i1 >= k){
			break;
		}
		if((i2 < k) && (mas[i1] < mas[i2])){
			i1 = i2;
		}
		if(mas[i] < mas[i1]){
			swap_el(mas + i, mas + i1);
			i = i1;
		}
		else{
		    break;
		}
	}
}



int correct_sort(int *mas, int length){
    for(int i = 1; i < length; i++){
        if(mas[i - 1] > mas[i]){
            return NOT_CORRECT;
        }
    }
    return CORRECT;
}



void generate_random_mas(int *mas, int length){
    srand(time(NULL));
    //int test = 20;
    for(int i = 0; i < length; i++){
        mas[i] = rand();
    }
}



void swap_el(int *a, int *b){
    int current;
    current = *a;
    *a = *b;
    *b = current;
}



int main(void)
{
    FILE* output;
    int length;
    int *mas = NULL;
    int *mas2 = NULL;
    int *mas3 = NULL;
    int res;
    
    
    output = fopen("output.txt", "w");
    
    if(output == NULL){
        printf("Ошибка открытия файла\n");
        return ER_OPEN;
    }
    
    printf("Введите длину случайного массива\n");
    if(scanf("%d", &length) != 1){
        printf("Некорректная длина\n");
        fclose(output);
        return ER_READ;
    }
    
    if(length < 1){
        printf("Некорректная длина\n");
        fclose(output);
        return ER_READ;
    }
    
    mas = (int*) malloc(length * sizeof(int*));
    mas2 = (int*) malloc(5 * length * sizeof(int*));
    mas3 = (int*) malloc(10 * length * sizeof(int*));
    
    if(mas == NULL){
        printf("Ошибка памяти\n");
        fclose(output);
        return ER_MEMORY;
    }
    
    if(mas2 == NULL){
        printf("Ошибка памяти\n");
        fclose(output);
        free(mas2);
        return ER_MEMORY;
    }
    
    if(mas3 == NULL){
        printf("Ошибка памяти\n");
        fclose(output);
        free(mas);
        free(mas2);
        return ER_MEMORY;
    }
    
    
    res = test(output, mas, length); // тесты при разной длине
    if(res == FAILED){
        goto bad;
    }
    res = test(output, mas2, 5 * length);
    if(res == FAILED){
        goto bad;
    }
    res = test(output, mas3, 10 * length);
    if(res == FAILED){
        goto bad;
    }

    fclose(output);
    free(mas);
    free(mas2);
    free(mas3);
    return SUCCESS;
    
    bad:
    printf("Сортировка работает некорректно\n");
    fclose(output);
    free(mas);
    free(mas2);
    free(mas3);
    return NOT_CORRECT;
}