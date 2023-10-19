#include <stdio.h>


int Schet(FILE*);


int main(void){
	FILE *fout, *fin;
	int Result;
	fin = fopen("input.txt", "r");
	
	if (fin == NULL){
		printf("error\n");
		return -3;
	}
	
	Result = Schet(fin);

	fout = fopen ("output.txt", "w");

	fprintf (fout, "%d", Result);
	
	return 0;
}
	

int Schet(FILE *fin){
	int count = 0;
	int current;	
	int previous;

	if (fscanf(fin, "%d", &previous) != 1){
		printf("error\n");
		return -2;
	}

	while (fscanf(fin, "%d", &current) == 1){
		if (current > previous){
			count ++;
		}
		previous = current;
	}

	if (feof (fin) == 0){
		printf("error\n");
		return -1;
	}

	return count;
}

					
