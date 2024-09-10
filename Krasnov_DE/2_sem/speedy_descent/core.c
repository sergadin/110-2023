#include "speedy_descent.h"

double** Matrix_multiplication(double** matrix,double** transpone_matrix, int size){    //multiplies a matrix by the matrix transposed of the given one
    double** result;
    int i,j,k;
    result = (double**)malloc(size*sizeof(double*));
    for(i=0;i<size;i++){
        result[i]=(double*)malloc(size*sizeof(double));
    }

    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            result[i][j]=0;
            for(k = 0; k < size; k++){
                result[i][j]= result[i][j] + matrix[i][k]*transpone_matrix[k][j];
            }
        }

    }
    return result;
}


double* Get_matrix_times_vector(double** matrix, double* vector, double* result, int size){     //multiplies a matrix by a vector
    int i,j;
    for(i=0;i<size;i++){
        result[i]=0;
        for(j=0;j<size;j++){
            result[i]=result[i]+matrix[i][j]*vector[j];
        }
    }
    return result;
}


double** Get_transpone_matrix(double** matrix, double** transpone_matrix, int size){    //transposes the given matrix
    int i,j;
    for(i = 0; i < size; i++){
        for(j = 0; j < size; j++){
            transpone_matrix[i][j] = matrix[j][i];
        }
    }
    return transpone_matrix;
}

double Get_scalar_product(double* vector1,double* vector2,int size){    //calculates the scalar product of two vectors
    int i;
    double scalar_product = 0;
    for(i = 0; i < size; i++){
        scalar_product = scalar_product + vector1[i] * vector2[i];
    }
    return scalar_product;
}


double* Get_vector_difference(double* vector1, double* vector2, double* result, int size){  //calculates the vector difference
    int i;
    for(i = 0; i < size; i++){
        result[i]=vector1[i]-vector2[i];
    }
    return result;
}

double* Get_vector_number(double* vector,double number,int size){   //multiply vector by number
    int i;
    for(i=0;i<size;i++){
        vector[i]=vector[i]*number;
    }

    return vector;
}


double* Get_system_solution(double** matrix, double* B_col, double* solution, int size, double eps, error* err){
    double* residual;
    double** transpone;
    double len_r;
    double k;
    int i,j;
    double* Atr_res;
    double* A_sol;
    double* A_Atr_res;
    int limit=10000;
    double** multi; //A*At
    if(*err != OK){
        return 0;
    }

    Atr_res=(double*)malloc(size*sizeof(double));
    A_sol=(double*)malloc(size*sizeof(double));
    A_Atr_res=(double*)malloc(size*sizeof(double));
    residual=(double*)malloc(size*sizeof(double));

    transpone = (double**)malloc(size*sizeof(double*));
    for(i=0;i<size;i++){
        transpone[i]=(double*)malloc(size*sizeof(double));
    }

    transpone=Get_transpone_matrix(matrix,transpone,size);

    for(i=0;i<size;i++){
        solution[i]=0;
        residual[i]=(-1)*B_col[i];
    }

    multi = Matrix_multiplication(matrix,transpone,size);


    A_Atr_res=Get_matrix_times_vector(multi,residual,A_Atr_res,size);
    Atr_res=Get_matrix_times_vector(transpone,residual,Atr_res,size);

    k = Get_scalar_product(residual,A_Atr_res,size)/Get_scalar_product(A_Atr_res,A_Atr_res,size);
    if(isnan(k) || isinf(k)){
        *err=INCORRECT_ARG;
        free(Atr_res);
        free(residual);
        for(j=0;j<size;j++){
            free(transpone[j]);
        }
        free(transpone);
        free(A_sol);
        free(A_Atr_res);
        for(j=0;j<size;j++){
            free(multi[j]);
        }
        free(multi);
        return 0;
    }
    solution = Get_vector_difference(solution,Get_vector_number(Atr_res,k,size),solution,size);
    limit=limit-1;
    len_r=sqrt(Get_scalar_product(residual,residual,size)); //good
    while(len_r >= eps && limit > 0){
        A_sol=Get_matrix_times_vector(matrix,solution,A_sol,size);
        residual=Get_vector_difference(A_sol,B_col,residual,size);
        A_Atr_res=Get_matrix_times_vector(multi,residual,A_Atr_res,size);
        Atr_res=Get_matrix_times_vector(transpone,residual,Atr_res,size);
        k = Get_scalar_product(residual,A_Atr_res,size)/Get_scalar_product(A_Atr_res,A_Atr_res,size);
        if(isnan(k) || isinf(k)){
            *err=INCORRECT_ARG;
            free(Atr_res);
            free(residual);
            for(j=0;j<size;j++){
                free(transpone[j]);
            }
            free(transpone);
            free(A_sol);
            free(A_Atr_res);
            for(j=0;j<size;j++){
                free(multi[j]);
            }
            free(multi);
            return 0;
        }
        solution = Get_vector_difference(solution,Get_vector_number(Atr_res,k,size),solution,size);
        len_r=sqrt(Get_scalar_product(residual,residual,size));
        limit=limit-1;
    }
    if(limit==0){
        *err=LIMIT;
        return 0;
    }
    free(Atr_res);
    free(residual);
    for(j=0;j<size;j++){
        free(transpone[j]);
    }
    free(transpone);
    free(A_sol);
    free(A_Atr_res);
    for(j=0;j<size;j++){
        free(multi[j]);
    }
    free(multi);
    return solution;
}

/*The function searches for a vector solution to a system of linear equations using the fast descent method.
the function receives as input the address of an array of arrays (double** matrix),
the address of the right column of the matrix (double* B_col), the address of the solution vector (double* solution),
the size of the square matrix (int size), the accuracy of calculations (double eps), the error address.
If successful, the program should fill the decision array with the correct values ​​and return its address.
*/



