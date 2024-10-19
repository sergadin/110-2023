#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void freeMatrix(char ***matrix, int rows, int cols) 
{
    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j<cols; j++) 
        {
        if(matrix[i][j]!=NULL)
            {
              free(matrix[i][j]);
            }   
        }
        free(matrix[i]);
        
    }
    free(matrix);
}

char ***createMatrix(int rows, int cols) 
{
    char ***matrix = malloc(rows * sizeof(char **));
    for (int i = 0; i < rows; i++) 
    {
        matrix[i] = malloc(cols * sizeof(char *));
        for (int j = 0; j < cols; j++) 
        {
            matrix[i][j] = NULL;
        }
    }
    return matrix;
}

char *multiplyStrings(const char *a, const char *b) 
{
    int lenA = strlen(a);
    int lenB = strlen(b);
    char *result = malloc(lenA + lenB + 1);
    strcpy(result, a);
    strcat(result, b);
    return result;
}

char *addStrings(const char *a, const char *b) 
{
    char *result = malloc(strlen(a) + strlen(b) + 4); 
    strcpy(result, a);
    strcat(result, " + ");
    strcat(result, b);
    return result;
}

char ***multiplyMatrices(char ***A, int rowsA, int colsA, char ***B, int rowsB, int colsB, int *rowsC, int *colsC) 
{
    if (colsA != rowsB) 
    {
        printf("нельзя умножить.\n");
        return NULL;
    }

    *rowsC = rowsA;
    *colsC = colsB;
    char ***C = createMatrix(*rowsC, *colsC);

    for (int i = 0; i < rowsA; i++) 
    {
        for (int j = 0; j < colsB; j++) 
        {
            C[i][j] = malloc(1);
            C[i][j][0] = '\0';
            for (int k = 0; k < colsA; k++) 
            {
                if (A[i][k] != NULL && B[k][j] != NULL) 
                {
                    char *temp = multiplyStrings(A[i][k], B[k][j]);
                    char *newResult = NULL;
                    if(strlen(C[i][j])>0)
                    {
                      newResult = addStrings(C[i][j], temp);
                    }
                    else
                    {
                      newResult = malloc(strlen(C[i][j]) + strlen(temp) + 1);
                      strcpy(newResult, C[i][j]);
                      strcat(newResult, temp);
                    }
                    free(C[i][j]);
                    C[i][j] = newResult;
                    free(temp);
                }
            }
        }
    }
    return C;
}

int main() 
{
    int rowsA=0, colsA=0, rowsB=0, colsB=0;
    FILE *matrIn = fopen("matrin.txt", "r");
    if(matrIn == NULL){
      printf("не открылось\n");
      return -1;
    }
    if (fscanf(matrIn, "%d %d", &rowsA, &colsA)!=2)
    {
      printf("не прочиталось\n");
      fclose(matrIn);
      return -1;
    }
    char ***A = createMatrix(rowsA, colsA);
    for (int i = 0; i < rowsA; i++) 
    {
        for (int j = 0; j < colsA; j++) 
        {
            A[i][j] = malloc(10000000000000 * sizeof(char));
            if(fscanf(matrIn, "%s", A[i][j])!=1)
            {
              printf("не прочиталось\n");
              fclose(matrIn);
              freeMatrix(A, rowsA, colsA);
              return -1;
            }
        }
    }

    if(fscanf(matrIn, "%d %d", &rowsB, &colsB)!=2)
    {
      printf("не прочиталось\n");
      fclose(matrIn);
      freeMatrix(A, rowsA, colsA);
      return -1;
    }
    char ***B = createMatrix(rowsB, colsB);
    for (int i = 0; i < rowsB; i++) 
    {
        for (int j = 0; j < colsB; j++) 
        {
            B[i][j] = malloc(100 * sizeof(char));
            if(fscanf(matrIn, "%s", B[i][j])!=1)
            {
              printf("не прочиталось\n");
              fclose(matrIn);
              freeMatrix(A, rowsA, colsA);
              freeMatrix(B, rowsB, colsB);
              return -1;
            }
        }
    }
  fclose(matrIn);
    int rowsC=0, colsC=0;
    char ***C = multiplyMatrices(A, rowsA, colsA, B, rowsB, colsB, &rowsC, &colsC);
    freeMatrix(A, rowsA, colsA);
    freeMatrix(B, rowsB, colsB);
    FILE *matrOut = fopen("matrout.txt", "w");
    if(matrOut == NULL)
    {
      printf("не открылось\n");
      fclose(matrIn);
      freeMatrix(C, rowsC, colsC);
      return -1;
    }
   
    if (C != NULL) 
    {
        for (int i = 0; i < rowsC; i++) 
        {
            for (int j = 0; j < colsC; j++) 
            {
                fprintf(matrOut, "%s ", C[i][j]);
            }
            fprintf(matrOut, "\n");
        }
    }
    fclose(matrOut);
    freeMatrix(C, rowsC, colsC);
    return 0;
}