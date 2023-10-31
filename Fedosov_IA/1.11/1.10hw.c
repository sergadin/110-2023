#include <stdio.h>

int main(void){

	FILE *fin, *fout;
	int counter = 0;
	int first_num;
    	int medium_num;
	int last_num;	
	fin = fopen("input.txt", "r");
        if (fin == NULL){
		printf("Не удалось открыть файл\n");
		return -1;
	}

	if (fscanf(fin, "%d", &medium_num) != 1){
	       printf ("Файл пуст\n");
	       return -2;
	}	       
	last_num = medium_num + 1;

	while ( fscanf(fin, "%d", &first_num)  == 1) {
		if (medium_num == first_num || medium_num == last_num){
			counter += 1;
		}
		last_num = medium_num;
		medium_num = first_num;
	}
	if (feof (fin) == 0){
		printf("error");
		return -1;
	}		

	if (medium_num == last_num){
		counter += 1;
	}	

	fout = fopen("output.txt", "w");
	fprintf (fout, "%d\n", counter);
	fclose(fin);
	fclose(fout);

	return 0;
}

	
	
