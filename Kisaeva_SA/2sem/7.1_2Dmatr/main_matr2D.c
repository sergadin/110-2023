#include <math.h>
#include "rang2D.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	const char *file_name; // имя файла, в котором хранится матрица
	int N; // кол-во строк
	int M; // кол-во столбцов
	error err; // код ошибки
} test_case;

int main (void) {
	FILE *f = NULL;
	int rang_ = 0;
	error err;
	int N = 0;
	int M = 0;
	int error_counter = 0; // счётчик для выявления ошибок
	double **matr = NULL; // массив, храниящий нашу матрицу "в 2D"
	double eps = 1e-5;
	int n_tasks = 0;
	
	test_case tests[] = {
		{"test1.txt", 2, 2, OK},
		{"test2.txt", 0, 0, NO_MATR},
		{"test3.txt", 4, 4, OK},
		{"test4.txt", 5, 4, OK}
	};
	
	n_tasks = sizeof(tests) / sizeof(tests[0]);
	for (int i = 0; i < n_tasks; i++) {
		if ((tests[i].N == 0) && (tests[i].M == 0)){
			err = NO_MATR;
			goto terminate;
		}
		N = tests[i].N;
		M = tests[i].M;
		f = fopen(tests[i].file_name, "r"); //Открытие файла и запись матрицы в массив
		if (f == NULL){
			printf("test %d - file error\n", i + 1);
			err = FILE_WR;
			goto terminate;
		}
		matr = (double**)malloc(N*sizeof(double*));
		if (matr == NULL){
			printf ("test %d - malloc error\n", i + 1);
			fclose(f);
			err = MEMORY_ERR;
			goto terminate;
		}
		for (int s = 0; s < N; s++) {
			matr[s] = (double *)malloc(M * sizeof(double));
			if (matr[s] == NULL){
				printf("test %d - operativ memory err\n", i + 1);
				for (int j = 0; j < s; j++){
					free(matr[j]);
				}
				free(matr);
				fclose(f);
				err = MEMORY_ERR;
				goto terminate;
			}
			for (int j = 0; j < M; j++){
				if (fscanf(f, "%lf", &matr[s][j])!=1){
					printf("test %d - error in file, malo znach\n", i + 1);
					err = FILE_WR;
					fclose(f);
					for (int i = 0; i < N; i++){							
						free(matr[i]);
					}
					free(matr);
					goto terminate;
				}
			}
		}
		fclose(f);
		
		rang_ = rang(N, M, matr, eps, &err);
		
		terminate:
		if(err != tests[i].err){
			printf("Test %d - FAIL\n", i + 1);
		}
		else if(err == OK){
			printf ("Test %d - rang = %d\n", i + 1, rang_);
			for(int i = 0; i < N; i++) {
				free(matr[i]);
			}
			free(matr);
		}
		else{
			printf("Test %d - PROSHEL\n", i + 1);
		}
	}
	return 0;	
}




//////////////////////////////////////////////////////invers
/*

#include "./utils/utils.h"

struct testing
{
  const char *File_name;
  int N;
  int M;
  double epsilon;
};

int
main (void)
{
  FILE *f = NULL;
  int N = 0;
  int M = 0;
  int error_counter = 0;
  double **matr = NULL;
  double epsilon = 0;
  struct testing test_number[4] = 
  {
	{"Test1.txt", 2, 2, 0.00001},
	{"Test2.txt", 2, 3, 0.000001},
	{"Test3.txt", 4, 4, 0.00001},
	{"Test4.txt", 5, 4, 0.000001}
  };
  for (int i = 0; i < 4; i++)
	{
	  matr = NULL;
	  error_counter = 0;
	  N = test_number[i].N;
	  M = test_number[i].M;
	  epsilon = test_number[i].epsilon;
	  matr = (double **) malloc ((N) * sizeof (double *));
	  if (matr == NULL)
		{
		  printf ("Test %d\n Malloc error\n", i + 1);
		  continue;
		}
	  for (int i = 0; i < N; i++)
		{
		  matr[i] = NULL;
		  matr[i] = (double *) malloc ((M) * sizeof (double));
		  if (matr[i] == NULL)
			{
			  for (int j = 0; j < i; j++)
				free (matr[j]);
			  error_counter++;
			  break;
			}
		}
	  if (error_counter != 0)
		{
		  free (matr);
		  printf ("Malloc error");
		  continue;
		}
	  f = fopen (test_number[i].File_name, "r");
	  if (f == NULL)
		{
		  for (int i = 0; i < N; i++)
			free (matr[i]);
		  free (matr);
		  printf ("Test %d\n File not open", i + 1);
		  continue;
		}
	  for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
		  fscanf (f, "%lf", &matr[i][j]);
	  fclose (f);
	  printf ("Test %d\n Rang: %d\n", i + 1, rang (N, M, matr, epsilon));
	  for (int i = 0; i < N; i++)
		free (matr[i]);
	  free (matr);
	}
  return 0;
}
*/