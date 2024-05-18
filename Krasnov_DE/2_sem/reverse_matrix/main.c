#include "find_reverse_matrix.h"


typedef struct{
    const char *file;
    int size;
    error err;
} dataSet;

double* fill_matrix(const char* file_name,int size, error *err ){
    double *matrix;
    FILE *f1;
    int i;
    *err = OK;
    f1 = fopen(file_name,"r");
    if(f1 == NULL){
        *err = EMPTY_FILE;
        return 0;
    }
    matrix = (double *)malloc(size*size*sizeof(double));
    if(matrix == NULL){
        *err= NO_INVERSE;
        return 0;
    }
    for(i=0;i<size*size;i++){
        fscanf(f1,"%lf",&matrix[i]);
    }
    fclose(f1);
    return matrix;
}


int main(void){
    error err;
    int test_num;
    double *result;
    double *mat;
    int size;
    int i,j;
    double eps=1e-6;
    dataSet tests[] = {
        {"data1.txt", 3, NO_INVERSE},
        {"data2.txt", 2, OK},
        {"data3.txt", 3, EMPTY_FILE},
        {"data4.txt", 2, NO_INVERSE},
        {"data5.txt", 4, NO_INVERSE },
        {"data6.txt", -1, NO_INVERSE },
        {"data7.txt", 5, OK },
    };

    test_num = sizeof(tests) / sizeof(tests[0]);

    for (i = 0; i < test_num; i++)
    {   size = tests[i].size;
        mat = fill_matrix(tests[i].file, size, &err);
        result = Get_reverse_matrix(mat, size, eps, &err);
        if (err != tests[i].err)
        {
            printf("test %d failed, the expected result of the algorithm was not obtained\n", i + 1);
        }
        else if (err == EMPTY_FILE || err == NO_INVERSE )
        {
            printf("test %d passed, the expected result of the algorithm was obtained\n", i + 1);
        }
        else if (err == OK)
        {
            printf("test %d passed successfully, the inverse matrix is ​​equal to \n",i+1);
            for(j=0;j<size*size;j++){
                if(j % size == size-1){
                    printf("%lf\n",result[j]);
                }
                else{
                    printf("%lf ",result[j]);
                }
            }
        }
        printf("\n");
        free(result);

    }
    return 0;
}
