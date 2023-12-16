#include<stdio.h>
#include<stdlib.h>

int gg(double* A, double* B, int len1, int len2);
int gg(double* A, double* B, int len1, int len2){
	double summa = 0;
	int count = 0;
	for(int i = 0; i< len1; i++){
		if(i<len2){
			summa+=B[i];
			if(A[i] > summa){
				A[count] = A[i];
				count++;
			}
		}
		else{
			A[i] = 0;
		}
	}
	return count;
}
int main(void){
FILE* input1;
FILE* input2;
FILE* answer;
double *A = NULL;
double* B=NULL;
int n1;
int n2;
int n;
input1 = fopen("inA.txt", "r");
input2 = fopen("inB.txt", "r");
answer = fopen("output.txt","w");
if(!answer){
	printf("What");
	return -1;
}
if(!input1){
	printf("No input1");
		return -1;
}
if(!input2){
        printf("No input2");
                return -1;
}
if(fscanf(input1, "%d", &n1)!=1){
        printf("No value");
	return -1;
}
if(fscanf(input2, "%d", &n2)!=1){
        printf("No value");
        return -1;
}
 A=(double*)malloc(n1*sizeof(double));
 B=(double*)malloc(n2*sizeof(double));

for(int i = 0; i < n1; i++){
	fscanf(input1,"%lf", &A[i]);
}
for(int i = 0; i < n2; i++){
        fscanf(input2,"%lf", &B[i]);
}
fclose(input1);
fclose(input2);
n = gg(A, B, n1, n2);
for(int i = 0; i < n; i++){
       fprintf(answer, "%lf", A[i]);
}
fclose(answer);
free(A);
free(B);
return 0;
}
