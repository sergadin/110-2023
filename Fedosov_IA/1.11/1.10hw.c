#include <stdio.h>

int main(void){

	FILE *fin, *fout;
	int counter = 0;
	int x;
    	int mtemp;
	int btemp;	
	fin = fopen("input.txt", "r");
        if (fin == NULL){
		printf("Не удалось открыть файл\n");
		return -1;
	}

	if (fscanf(fin, "%d", &mtemp) != 1){
	       printf ("Файл пуст\n");
	       return -2;
	}	       
	btemp = mtemp + 1;

	while ( fscanf(fin, "%d", &x)  == 1) {
		if (mtemp == x || mtemp == btemp){
			counter += 1;
		}
		btemp = mtemp;
		mtemp = x;
	}
	if (feof (fin) == 0){
		printf("error");
		return -1;
	}		

	if (mtemp == btemp){
		counter += 1;
	}	

	fout = fopen("output.txt", "w");
	fprintf (fout, "%d\n", counter);
	fclose(fin);
	fclose(fout);

	return 0;
}

	
	
