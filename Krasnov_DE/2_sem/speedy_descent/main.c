#include "speedy_descent.h"

double** Fill_matrix(double** matrix, double* B_col, const char* file_name, int size, error *err){  //the function fills the matrix and separately the solution column
    FILE  *f1;
    int i,j;
    *err=OK;
    f1=fopen(file_name,"r");
    if(f1==NULL){
        *err=EMPTY_FILE;
        return 0;
    }
    if(size<1){
        *err=INCORRECT_SIZE;
        fclose(f1);
        return 0;
    }

    matrix=(double**)malloc(size*sizeof(double*));
    for(i=0;i<size;i++){
        matrix[i]=(double*)malloc(size*sizeof(double));

    }

    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            fscanf(f1,"%lf",&matrix[i][j]);
        }
    }
    for(i=0;i<size;i++){
        fscanf(f1,"%lf", &B_col[i]);
    }
    fclose(f1);
    return matrix;
}

typedef struct{
    const char *file;
    int size;
    double *res;
    error err;
} TestCase;


int main(void){
    error err;
    int test_num;
    double eps = 1e-7;
    double** mat;
    double* B_col;
    int size;
    double* solution;
    int flag=0;
    int i,j;


    TestCase tests[]={
        {"data1.txt", 2, (double[]){-1,2}, OK},
        {"data2.txt", 3, (double[]){1,2,2}, OK},
        {"data3.txt", 3, (double[]){5,3,7}, EMPTY_FILE},
        {"data4.txt", 4, (double[]){1,0,1,0}, OK},
        {"data5.txt", 5, (double[]){1,2,3,4,5}, INCORRECT_ARG },
        {"data6.txt", -1, (double[]){}, INCORRECT_SIZE },
    };

    test_num = sizeof(tests) / sizeof(tests[0]);
    for(i=0;i<test_num;i++){
        size=tests[i].size;
        if(size>0){
            B_col=(double*)malloc(size*sizeof(double));
            solution=(double*)malloc(size*sizeof(double));
        }

        mat=Fill_matrix(mat, B_col, tests[i].file,size,&err);

        solution=Get_system_solution(mat,B_col,solution,size,eps,&err);
        if(err!=tests[i].err){
            printf("test %d failed, errors not equals\n",i+1);
        }
        else if(err == EMPTY_FILE){
            printf("test %d passed,file not open\n",i+1);
            free(solution);
            free(B_col);
        }
        else if(err == INCORRECT_SIZE){
            printf("test %d passed, size is not int\n",i+1);
        }
        else if(err==LIMIT){
            printf("test %d passed,transaction limit has been exceeded\n",i+1);
            for(j=0;j<size;j++){
                free(mat[j]);
            }
            free(mat);
            free(solution);
            free(B_col);
        }
        else if(err==INCORRECT_ARG){
            printf("test %d passed,error in calculations\n",i+1);
            for(j=0;j<size;j++){
                free(mat[j]);
            }
            free(mat);
            free(solution);
            free(B_col);
        }
        else{
            flag=0;
            for(j=0;j<size;j++){
                if(fabs(solution[j]-tests[i].res[j])>10*eps){
                    flag=1;
                    break;
                }
            }
            if(flag == 0){
                printf("test %d passed\n",i+1);
            }
            else{
                printf("test %d failed, the values %lf and %lf are ​​different\n",i+1,solution[j],tests[i].res[j]);
            }
            for(j=0;j<size;j++){
                free(mat[j]);
            }
            free(mat);
            free(solution);
            free(B_col);
        }
    }
    return 0;
}
