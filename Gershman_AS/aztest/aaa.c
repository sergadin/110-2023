#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int is_good_el(double* arrB, int len_B, int index_A, double val_A);


int is_good_el(double* arrB, int len_B, int index_A, double val_A)
{
    double sum = 0;
    for(int i = 0;(i <= index_A); i++)
    {
        sum += arrB[i];
        if (i == len_B - 1)
        {
            break;
        }
    }
    
    if (val_A > sum)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    
}


int main(void)
{
    FILE* inA;
    FILE* inB;
    FILE* output;
    double* arrA = NULL;
    double* arrB = NULL;
    int len_A, len_B, cnt = 0;
    inA = fopen("inA.txt", "r");
    if(inA == NULL)
    {
        return -1;
    }
    
    inB = fopen("inB.txt", "r");
    if(inB == NULL)
    {
        fclose(inA);
        return -1;
        
    }
    
    output = fopen("output.txt", "w");
    if(output == NULL)
    {
        fclose(inA);
        fclose(inB);
        return -1;
    }
    
    if (fscanf(inA, "%d", &len_A) != 1)
    {
        fclose(inA);
        fclose(inB);
        fclose(output);
        return -1;
    }
    if (fscanf(inB, "%d", &len_B) != 1)
    {
        
        fclose(inA);
        fclose(inB);
        fclose(output);
        return -1;
    }
    arrA = (double*)malloc((len_A) * sizeof(double));
    if (arrA == NULL)
    {
        fclose(inA);
        fclose(inB);
        fclose(output);
        free(arrA);
        return -1;
    }
    for(int i = 0; i < len_A; i++)
    {
        if(fscanf(inA, "%lf", &arrA[i]) != 1)
        {
            fclose(inA);
            fclose(inB);
            fclose(output);
            free(arrA);
            free(arrB);
            return -1;
        }
    }
    arrB = (double*)malloc((len_B) * sizeof(double));
    if (arrB == NULL)
    {
        fclose(inA);
        fclose(inB);
        fclose(output);
        free(arrA);
        free(arrB);
        return -1;
    }
    for(int i = 0; i < len_B; i++)
    {
        if(fscanf(inB, "%lf", &arrB[i]) != 1)
        {
            fclose(inA);
            fclose(inB);
            fclose(output);
            free(arrA);
            free(arrB);
            return -1;
        }
    }
    
    for(int i = 0; i < len_A; i++)
    {
        if(is_good_el(arrB, len_B, i, arrA[i]) == 1)
        {
            cnt++;
        }
    }
    fprintf(output, "%d ", cnt);
    for(int i = 0; i < len_A; i++)
    {
        if(is_good_el(arrB, len_B, i, arrA[i]) == 1)
        {
            fprintf(output, "%lf ", arrA[i]);
        }
    }
    free(arrA);
    free(arrB);
    fclose(inA);
    fclose(inB);
    fclose(output);
}
