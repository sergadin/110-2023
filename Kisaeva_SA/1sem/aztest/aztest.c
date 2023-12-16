#include <stdio.h>
#include <stdlib.h>

int elem_in_file_A_horosh(double *mas_A, double *mas_B, int len_A, int len_B);

//если и элемент больше чем сумма элементов в мас б, то и элемент хорорший
int elem_in_file_A_horosh(double *mas_A, double *mas_B, int len_A, int len_B) {
    double sum_el_B = 0;
    int kol_horosh_el_in_A = 0;
    
    if (len_A <= len_B){
        for (int i = 0; i < len_A; i++) {
            sum_el_B += mas_B[i];
            if (mas_A[i] > sum_el_B) {
                mas_A[i + len_A] = mas_A[i];
                kol_horosh_el_in_A ++;
            }
        }
    }
    else if (len_A > len_B){
        for (int j = len_B; j < len_A; j++) {
            if (mas_A[j] > sum_el_B) {
                mas_A[j + len_A] = mas_A[j];
                kol_horosh_el_in_A ++;
            }
        }
    }
    return kol_horosh_el_in_A;
}


int main(void) {
	int len_A, len_B, kol_horosh_el_in_A;
    int len_A_in_file = 0, len_B_in_file = 0;
	FILE *in_A;
    FILE *in_B;
	FILE *out;
    double *mas_A = NULL;
    double *mas_B = NULL;
    int  scan_A, scan_B;
    double el_A, el_B;
    
    in_A = fopen("inA.txt", "r");
	if (in_A == NULL) {
		printf("error opening the file_A\n");
		return -1;
	}
	
	in_B = fopen("inB.txt", "r");
	if (in_B == NULL) {
		printf("error opening the file_B\n");
        fclose(in_A);
		return -1;
	}
	
	out = fopen("output.txt", "w");
    if (out == NULL) {
		printf("error opening the file_out\n");
        fclose(in_A);
        fclose(in_B);
		return -1;
	}
	
	if ((fscanf(in_A, "%d", &len_A) != 1) || (len_A <= 0)) {
		printf("error with len_A\n");
        fclose(in_A);
        fclose(in_B);
        fclose(out);
		return -1;
	}
	
    if ((fscanf(in_B, "%d", &len_B) != 1) || (len_B <= 0)) {
		printf("error with len_B\n");
        fclose(in_A);
        fclose(in_B);
        fclose(out);
		return -1;
	}
    
    while ((scan_A = fscanf(in_A,"%lf", &el_A)) != EOF) {
        if (scan_A != 1) {
            printf("error with elements in file_A");
            fclose(in_A);
            fclose(in_B);
            fclose(out);
            return -1;
        }
        len_A_in_file ++;
    }
    if (len_A_in_file > len_A) {
        printf("error with elements in file_A");
        fclose(in_A);
        fclose(in_B);
        fclose(out);
        return -1;
    }
    
    while ((scan_B = fscanf(in_B,"%lf", &el_B)) != EOF) {
    if (scan_B != 1) {
        printf("error with elements in file_B");
        fclose(in_A);
        fclose(in_B);
        fclose(out);
        return -1;
        }
        len_B_in_file ++;
    }
    if (len_B_in_file > len_B) {
        printf("error with elements in file_B");
        fclose(in_A);
        fclose(in_B);
        fclose(out);
        return -1;
    }
	
	rewind(in_A);
    rewind(in_B);
    
    mas_A = (double*) malloc((len_A * 2)*sizeof(double));
     if (mas_A == NULL) {
        printf("Memory error mas_A\n");
        fclose(in_A);
        fclose(in_B);
        fclose(out);
        return -1;
    }
    for (int i = 0; i < len_A; i++) {
        fscanf(in_A, "%lf", &mas_A[i]);
    }
    
    mas_B = (double*) malloc((len_B)*sizeof(double));
    if (mas_B == NULL) {
        printf("Memory error mas_B\n");
        fclose(in_A);
        fclose(in_B);
        fclose(out);
        return -1;
    }
    for (int i = 0; i < len_B; i++) {
        fscanf(in_A, "%lf", &mas_B[i]);
    }
    
    kol_horosh_el_in_A = elem_in_file_A_horosh(mas_A, mas_B, len_A, len_B);
    if (kol_horosh_el_in_A == 0) {
        printf("net horosh el in file_A\n");
        free(mas_A);
        free(mas_B);
        fclose(in_A);
        fclose(in_B);
        fclose(out);
        return 0;
    }

	for (int i = 0; i < kol_horosh_el_in_A; i++) {
		fprintf(out, "%lf ", mas_A[i + len_A]);
	}
	
	free(mas_A);
    free(mas_B);
    fclose(in_A);
    fclose(in_B);
    fclose(out);
	return 0;
}
