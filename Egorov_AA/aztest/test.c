#include <stdio.h>
#include <stdlib.h>

int correctLen(int len_a, int len_b, FILE* ina, FILE* inb);
int goodElement(double a_elem, int i, double* arr_b);


int goodElement(double a_elem, int i, double* arr_b){
    double sum = 0;
    for (int j = 0; j < i; j++){
        sum += arr_b[j];
    }
    if (a_elem > sum)
        return 1;
    else
        return 0;
}

int correctLen(int len_a, int len_b, FILE* ina, FILE* inb){
    int count_a = 0, count_b = 0;
    double temp;
    while(fscanf(ina, "%lf", &temp) == 1) {
        count_a++;
    }
    while(fscanf(inb, "%lf", &temp) == 1) {
        count_b++;
    }
    if ((count_a == len_a) && (count_b == len_b)){
        return 0;
    }
    else {
        return 1;
    }
}


int main(void) {
	FILE* ina, * inb, * out;
	double* arr_a, * arr_b;
    int len_a, len_b, count = 0;
    
	if ((ina = fopen("inA.txt", "r")) == NULL){
        printf("nety ina\n");
		return -1;
	}
	
	if ((inb = fopen("inB.txt", "r")) == NULL){
        printf("nety inb\n");
		fclose(ina);
		return -1;
	}
	if ((out = fopen("output.txt", "w")) == NULL){
        
        printf("nety out\n");
		fclose(ina);
		fclose(inb);
		return -1;
	}
	
	if (fscanf(ina, "%d", &len_a) != 1){
        fclose(ina);
        fclose(inb);
        fclose(out);
        return -1;
    }
    if (fscanf(inb, "%d", &len_b) != 1){
        fclose(ina);
        fclose(inb);
        fclose(out);
        return -1;
    }
    
    if (correctLen(len_a, len_b, ina, inb)){
        
        printf("len govna3\n");
        fclose(ina);
        fclose(inb);
        fclose(out);
        return -1;
    }
    
    arr_a = (double*)malloc(len_a * sizeof(double));
    if (arr_a == NULL) {
        fclose(ina);
        fclose(inb);
        fclose(out);
        return -1;
    }
    arr_b = (double*)malloc(len_b * sizeof(double));
    if (arr_b == NULL) {
        fclose(ina);
        fclose(inb);
        fclose(out);
        free(arr_a);
        return -1;
    }
    
    rewind(ina);
    rewind(inb);
    
    fscanf(ina, "%d", &len_a);
    fscanf(inb, "%d", &len_b);
    
    for (int i = 0; i < len_a; i++) {
        if (fscanf(ina, "%lf", &arr_a[i]) != 1) {
        fclose(ina);
        fclose(inb);
        fclose(out);
        free(arr_a);
        free(arr_b);
        return -1;
        }
    }
    
    
    for (int i = 0; i < len_b; i++) {
        if (fscanf(inb, "%lf", &arr_b[i]) != 1) {
        fclose(ina);
        fclose(inb);
        fclose(out);
        free(arr_a);
        free(arr_b);
        return -1;
        }
    }
    
    for (int i = 0; i < len_a; i++) {
        if (goodElement(arr_a[i], len_b, arr_b)) {
            count++;
        }
    }
    
    fprintf(out, "%d ", count);
    
    for (int i = 0; i < len_a; i++) {
        if (goodElement(arr_a[i], len_b, arr_b)) {
            fprintf(out, "%.2lf ", arr_a[i]);
        }
    }
    
    fclose(ina);
    fclose(inb);
    fclose(out);
    free(arr_a);
    free(arr_b);
    
    return 0;
}
