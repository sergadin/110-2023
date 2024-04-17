#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "hermit_interpolation.h"


typedef struct{  //структура для проведения тестов функции
    double* domain;
    int n;
    double* f_values;
    double* df_values;
    double* new_domain;
    int N;
    Error error;
    double* result;
} TestCase;

//функция для записи точек и значений функции в файл
void write_in_file(double* domain, double* f_values, int n, double* new_domain, double* new_f_values, int N, FILE* fout1, FILE* fout2) {
    fprintf (fout1, "# plotting_data.dat\n");
    fprintf (fout1, "# X  Y\n");
    for(int i = 0; i < n; i++) {
        fprintf(fout1, "%lf     %lf\n", domain[i], f_values[i]);
    }
    
    fprintf (fout2, "# plotting_data.dat\n");
    fprintf (fout2, "# X  Y\n");
    for(int i = 0; i < N; i++) {
        fprintf(fout2, "%lf     %lf\n", new_domain[i], new_f_values[i]);
    }

}


int main(void){	
    FILE* fout1;
    FILE* fout2;
    FILE* fout3;
    FILE* fout4;

	double* result; //результат выполнения основной функции
    Error error;

    //массивы для функции cos(x)
    double arr1[9] = {0, 0.2, 0.4, 0.6, 0.8, 1, 1.2, 1.4, 1.6};
    double arr2[9] = {1, 0.98, 0.921, 0.8253, 0.6967, 0.5403, 0.3623, 0.1699, -0.0291};
    double arr3[9] = {0, -0.1986, -0.3894, -0.5646, -0.7173, -0.8414, -0.932, -0.9854, -0.9995};
    double arr4[5] = {0.1, 0.3, 0.7, 1.3, 1.5};
    double arr5[5] = {0.9950041, 0.95533648, 0.76484218, 0.26749882, 0.0707372};

    //массивы для функции xln(x)
    double arr6[12] = {0, .1, .2, .3, .4, .5, .6, .7, .8, .9, 1, 1.1};
    double arr7[12] = {0, -.2302, -.3218, -.3611, -.3665, -.3465, -.3064, -.2496, -.1785, -.0948, 0, .1048};
    double arr8[12] = {1, -1.3025, -.6094, -.2039, .0837, .3068, .4891, .6433, .7768, .8946, 1, 1.0953};
    double arr9[11] = {.05, .15, .25, .35, .45, .55, .65, .75, .85, .95, 1.05};
    double arr10[] = {-.1497, -.2845, -.3465, -.3674, -.3593, -.3288, -.28, -.2157, -.1381, -.0487, .0512};


	TestCase tests[] = {
        {   //функция cosx
            arr1,
            9,
            arr2,
            arr3,
            arr4,
            5,
            OK,
            arr5
        },
        {   //функция xlnx
            arr6,
            12,
            arr7,
            arr8, 
            arr9,
            11, 
            OK,
            arr10
        }

	};
	
	for (int i = 0; i < 2; i ++) { 
        result = (double*)malloc(sizeof(double) * tests[i].N);
		result = hermite_interpolation (tests[i].domain, tests[i].n, tests[i].f_values, tests[i].df_values, tests[i].new_domain, tests[i].N, &error);
        if (error != tests[i].error) {
            printf("Тест %d не пройден\n", i + 1);
        } else if (error == EMPTY){
            printf("В тесте %d длина массива с заданными точками равна 0\n", i + 1);
        } else if (error == NO_ANSWER) {
            printf("В тесте %d задана нулевая сетка\n", i + 1);
        } else if (error == BORDERS) {
            printf("В тесте %d новая сетка содержит точки, выходящие за граница заданных точек\n", i + 1);
        } else {
            printf("В тесте %d приближенные значения равняются:\n", i + 1);
            for (int j = 0; j < tests[i].N; j++) {
                printf("Приближенное значение в точке %lf: %lf, точное значение : %lf\n",tests[i].new_domain[j], result[j], tests[i].result[j]);
            }
            if(i == 0) {
                fout1 = fopen("data1.txt", "w");
                fout2 = fopen("data2.txt", "w");
                write_in_file(tests[i].domain, tests[i].f_values, tests[i].n, tests[i].new_domain, result, tests[i].N, fout1, fout2);
                fclose(fout1);
                fclose(fout2);
                printf("График занесен в файл output1.png, фиолетовый точки - исходные, синие - полученные путем приближения\n");
            } else {
                fout3 = fopen("data3.txt", "w");
                fout4 = fopen("data4.txt", "w");
                write_in_file(tests[i].domain, tests[i].f_values, tests[i].n, tests[i].new_domain, result, tests[i].N, fout3, fout4);
                fclose(fout3);
                fclose(fout4);
                printf("График занесен в файл output2.png, фиолетовый точки - исходные, синие - полученные путем приближения\n");
            }
        }
        free(result);
	}
	return 0;	
}