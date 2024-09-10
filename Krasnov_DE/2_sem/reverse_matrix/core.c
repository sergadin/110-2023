#include "reverse_matrix.h"

double* Get_Minor(double* matrix,double* minor, int n, int row, int col){
    int i,j=0;
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


double Get_det(double* arr, int n,double eps){
    double* copy;
    int i;
    double determinant=1;
    copy=(double*)malloc(n*n*sizeof(double));
    for(i=0;i<n*n;i++){
        copy[i]=arr[i];
    }
    copy=Get_stepped(n, n, copy, eps);
    for(i=0;i<n;i++){
        determinant=determinant*copy[i*n+i];
    }
    free(copy);
    return determinant;
}


double* Get_transpone_matrix(double *arr, int n){
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


double* Get_reverse(double* arr,int n, double eps, error *err){
    double determinant;
    int i;
    int row,col;
    int sgn;
    double* minor;
    double* p;
    if(*err!=OK){
        return 0;
    }

    determinant=Get_det(arr, n, eps);
    if(fabs(determinant) < eps){
        *err = NO_INVERSE;
        free(arr);
        return 0;
    }

    minor=(double*)malloc((n-1)*(n-1)*sizeof(double));
    p=(double*)malloc(n*n*sizeof(double));
    for(i = 0; i < n * n; i++){
        row = i / n;
        col = i % n;
        sgn = pow(-1,row+col);
        minor = Get_Minor(arr,minor, n, row, col);
        p[i] = sgn * Get_det(minor,n-1,eps) / determinant;
    }
    p= Get_transpone_matrix(p, n);
    free(arr);
    free(minor);
    return p;
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


void line_difference (int numb_columns, double *matr, int first_number, int second_number, double c){
    int i;
    for (i = 0; i < numb_columns ; i++){
        matr[numb_columns * first_number + i] = matr[numb_columns * first_number + i]- matr[numb_columns * second_number + i] * c;
	}
}


void swap (int numb_colums, double *matr, int i, int j)
{
  double a;
  for (int k = 0; k < numb_colums; k++)
	{
	  a = matr[numb_colums * i + k];
	  matr[numb_colums * i + k] = matr[numb_colums * j + k];
	  matr[numb_colums * j + k] = a;
	}
}


double* Get_stepped(int N, int M, double *matr, double epsilon)
{
  int rang = 0;
  double leader = 1;
  double repeat_leader = 1;
  int i,j = 0;
  for (j = 0; j < M; j++)
	{
	  i = rang;
	  while (i < N)
		{
		  if (fabs (matr[M * i + j]) < epsilon)
			{
			  i++;
			  continue;
			}
		  leader = matr[M * i + j];
		  swap (M, matr, rang, i);

		  for (int k = i + 1; k < N; k++)
			{
			  repeat_leader = matr[M * k + j];
			  if (fabs (repeat_leader) > epsilon)
				line_difference (M, matr, k, rang, repeat_leader / leader);
			}
		  rang++;
		  break;
		}
	}
  return matr;
}

/*The get_reverse function calculates the inverse of a matrix by counting algebraic additions and reducing the matrix to echelon form.
The input is the address of the array (containing matrix elements)(double* arr), matrix size(int size), calculation accuracy(double eps), error address(error *err).
*/
