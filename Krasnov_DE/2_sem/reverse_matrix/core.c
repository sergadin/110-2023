#include "find_reverse_matrix.h"

double* Get_Minor(double* matrix, int n, int row, int col){ //the function creates a minor without a row (int row) and a column (int col)
    double* minor;
    int i,j=0;
    minor = (double*)malloc((n-1)*(n-1)*sizeof(double));
    for(i = 0; i < n * n; i++){
        if(i % n != col && i / n != row){
            minor[j]=matrix[i];
            j++;
        }
        else{
            continue;
        }
    }
    return minor;
}

double Get_determinant(double* arr, int n){//the function calculates the determinant of a matrix of size n *n
    double determinant=0;
    double* p;
    int k=1;
    int i;
    if(n < 1){
        return 0;
    }
    if(n==1){
        determinant=arr[0];
        return determinant;
    }
    if(n==2){
        determinant=arr[0]*arr[3]-arr[1]*arr[2];
        return determinant;
    }
    if(n > 2){
        for(i = 0; i < n; i++){
            p = Get_Minor(arr, n, 0, i);
            determinant = determinant + k * arr[i] * Get_determinant(p, n-1);
            k = k * (-1);
            free(p);
        }
    }
    return(determinant);
}

double* Get_transpone_matrix(double *arr, int n){//function to transpose the matrix fed into it
    int i,j;
    double c;
    for(i = 0; i < n; i++){
        for(j = 0; j < i; j++){
            c=arr[i*n+j];
            arr[i*n+j]=arr[j*n+i];
            arr[j*n+i]=c;
        }
    }
    return arr;
}

double* Matrix_multiplication(double* matrix1, double* matrix2, int size){
    double* result;
    int i,j,k;
    result = (double*)malloc(size*size*sizeof(double));
    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            result[i*size + j]=0;
            for(k=0;k<size;k++){
                result[i*size + j]= result[i*size + j] + matrix1[i*size+k]*matrix2[k*size+j];
            }
        }

    }
    return result;
}

void Print_matrix(double* mat,int size){
    int j;
    for(j=0;j<size*size;j++){
        if(j % size == size-1){
            printf("%lf\n",mat[j]);
        }
        else{
            printf("%lf ",mat[j]);
        }
    }
}

int Identity_matrix_test(double* mat1,double* mat2, int size, double eps){
  int flag=0;
  int i;
  for(i=0;i<size*size;i++){
    if(fabs(mat1[i]-mat2[i])>eps){
      flag=1;
    }
  }
  return flag;
}


double* Get_reverse_matrix(double *arr, int n,double eps, error *err){
    if(*err==EMPTY_FILE){
        free(arr);
        return 0;
    }
    double determinant=Get_determinant(arr, n);
    if(fabs(determinant) < eps){
        *err = NO_INVERSE;
        free(arr);
        return 0;
    }
    int i;
    int row, col;
    int sgn;
    double* p;
    p = (double*)malloc(n*n*sizeof(double));
    for(i = 0; i < n * n; i++){
        row = i / n;
        col = i % n;
        sgn = pow(-1,row+col);
        double* minor = Get_Minor(arr, n, row, col);
        p[i] = sgn * Get_determinant(minor, n-1) / determinant;
        free(minor);
    }
    p = Get_transpone_matrix(p, n);
    free(arr);
    return p;
}
/*The function calculates the inverse of a matrix using the algebraic complement matrix.
The input is the address of an array, including matrix elements, matrix size, calculation accuracy, error address.
*/
