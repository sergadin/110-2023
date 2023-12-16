#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define ERROR -1
#define GOOD 0

int Search(double* arrA, int lenA, double* arrB, int lenB);

int Search(double* arrA, int lenA, double* arrB, int lenB)
{
    double sum_B;
    int x = 0;

    //Проверка, что файл существует
    if ((arrA == NULL) ||(arrB == NULL))
	{
		return ERROR;
	}
    
    //Проверка, что данные корректные
	if ((!(lenA > 0)) || (!(lenB > 0)))
    {
        return ERROR;
    }
    
    if (lenB < lenA)
    {
        lenA = lenB;
    }
    
    for(int i = 0; i < lenA; i++)
    {
        sum_B = 0;
        
        for(int j = 0; j < i + 1; j++)
        { 
            sum_B += arrB[j];
        }
        
        if (arrA[i] > sum_B)
        {
            arrA[x++] = arrA[i];
        }
        
    }
    
    return x;
}




int main(void)
{
    FILE* A;
    FILE* B;
    FILE* OUT;
    double* arrA = NULL;
    double* arrB = NULL;
    int lenA;
    int lenB;
    int code;
    
    //Открыли файл А
    A = fopen("inA.txt", "r");
    
    //Проверка, что файл существует
    if (A == NULL)
	{
        fclose(A);
        printf("ERROR - NULL A\n");
		return ERROR;
	}
	
	//Проверка, что файл не пуст
	if (feof(A))
    {
        fclose(A);
        printf("ERROR - pust A\n");
        return ERROR;
    }
    
    //Проверка, что данные корректные
    if (fscanf(A, "%d", &lenA) != 1)
	{
        fclose(A);
        printf("ERROR - ne cheslo dlina A\n");
		return ERROR;
	}
	
	//Проверка, что данные корректные
	if (!(lenA > 0))
    {
        fclose(A);
        return ERROR;
    }
    
    arrA = (double*)malloc((lenA + 1) * sizeof(double));
    
    //Проверка, что мы выделили данные
	if (arrA == NULL)
	{
        fclose(A);
        printf("ERROR - skaleoz A\n");
		return ERROR;
	}

	for (int i = 0; i < lenA; i++)
	{
        
        //Проверка, что данные корректные
		if (fscanf(A, "%lf", &arrA[i]) != 1)
		{
            fclose(A);
            printf("ERROR - ne cheslo A\n");
			return ERROR;
		}

	}
	
    //Открыли файл В
    B = fopen("inB.txt", "r");
    
    //Проверка, что файл существует
    if (B == NULL)
	{
        fclose(B);
        printf("ERROR - NULL B\n");
		return ERROR;
	}
	
	//Проверка, что файл не пуст
	if (feof(B))
    {
        fclose(B);
        printf("ERROR - pust B\n");
        return ERROR;
    }
    
    //Проверка, что данные корректные
    if (fscanf(B, "%d", &lenB) != 1)
	{
        fclose(B);
        printf("ERROR - ne cheslo dlina B\n");
		return ERROR;
	}
	
	//Проверка, что данные корректные
	if (!(lenB > 0))
    {
        fclose(B);
        return ERROR;
    }
    
    arrB = (double*)malloc((lenB + 1) * sizeof(double));
    
    //Проверка, что мы выделили данные
	if (arrB == NULL)
	{
        fclose(B);
        printf("ERROR - skaleoz B\n");
		return ERROR;
	}

	for (int j = 0; j < lenB; j++)
	{
        
        //Проверка, что данные корректные
		if (fscanf(B, "%lf", &arrB[j]) != 1)
		{
            fclose(B);
            printf("ERROR - ne cheslo B\n");
            return ERROR;
        }
    }
    
    code = Search(arrA, lenA, arrB, lenB);
    
    fclose(A);
    fclose(B);
    
    if (code == ERROR)
    {
        return ERROR;
    }
    
    OUT = fopen("output.txt", "w");
    
    fprintf(OUT, "%d\n", code);
    
    for (int k = 0; k < code; k++)
    {
        fprintf(OUT, "%lf ", arrA[k]);
    }
    
    fprintf(OUT, "\n");
    fclose(OUT);
    
    return GOOD;
}
