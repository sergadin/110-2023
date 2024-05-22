#include "reverse_matrix.h"


typedef struct{     //creating a test structure
    const char *file;
    int size;
    error err;
} TestCase;

/*The function allocates memory for an array and creates it
if the file is successfully opened and the matrix size is checked for positivity*/

double* fill_matrix(const char* file_name, int size, error *err ){
    double *matrix;
    int i;
    *err = OK;
    FILE *f1;
    f1 = fopen(file_name,"r");
    if(f1 == NULL){
        *err = EMPTY_FILE;
        return 0;
    }
    if(size <= 0){
        *err = INCORRECT_SIZE;
        fclose(f1);
        return 0;
    }
    matrix = (double *)malloc(size * size * sizeof(double));
    for(i = 0; i < size * size; i++){
        fscanf(f1, "%lf", &matrix[i]);
    }
    fclose(f1);
    return matrix;
}


int main(void){
    error err;
    int test_num;
    double *result;
    double *mat;
    double *copy;
    double *proove;
    double *puk;
    int size, i, j, flag;
    double eps=1e-6;
    TestCase tests[] = {
        {"data1.txt", 3, NO_INVERSE},   //creating a set of different tests
        {"data2.txt", 2, OK},
        {"data3.txt", 3, EMPTY_FILE},
        {"data4.txt", 2, NO_INVERSE},
        {"data5.txt", 4, NO_INVERSE},
        {"data6.txt", -1, INCORRECT_SIZE},
        {"data7.txt", 5, OK}

    };

    test_num = sizeof(tests) / sizeof(tests[0]);    //count the number of tests
    for(i = 0; i < test_num; i++){
        size = tests[i].size;
        mat = fill_matrix(tests[i].file, size, &err);    //filling the array
        /*create a copy of the array necessary
        for verification if the program executes successfully
        */
        if(err == OK){
            copy = (double*)malloc(size * size * sizeof(double));
            for(j = 0; j < size * size; j++){
                copy[j] = mat[j];
            }
        }
        result = Get_reverse(mat,size,eps,&err);

        if(err != tests[i].err){
            printf("test %d failed,the errors are different\n",i+1);
        }

        else if(err == EMPTY_FILE){
            printf("test %d passed,  file does not exist\n",i+1);
        }

        else if(err == INCORRECT_SIZE){
            printf("test %d passed, size < 0\n",i+1);
        }

        else if(err == NO_INVERSE){
            printf("test %d passed, inverse matrix does not exist\n",i+1);
            free(result);
            free(copy);
        }

        else{
            proove = Matrix_multiplication(result,copy,size);//a matrix that is supposed to be identity
            puk = Matrix_multiplication(result,proove,size);
            flag = Identity_matrix_test(puk,result,size,eps); //checking matrices for matches

            if(flag == 0){
                printf("test %d passed, reverse matrix equal to\n",i+1);
                Print_matrix(result,size);
                printf("\n");
                Print_matrix(proove,size);
            }

            else{
                printf("test %d failed,error in calculations\n",i+1);
            }

            free(result);
            free(copy);
            free(proove);
            free(puk);
        }
    }
    return 0;
  }



