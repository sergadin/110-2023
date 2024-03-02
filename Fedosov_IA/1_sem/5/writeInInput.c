#include <stdlib.h>
#include <stdio.h>
#include <time.h>



int main(void){
	FILE * fout = fopen("input.txt", "w");
	int n;
	
	printf("Введите количество точек: \n");
	
	scanf("%d", &n);
	fprintf(fout, "%d \n", n);
	
	srand(time(NULL));

	for (int i = 0; i < 2 * n; i++)
	{
		fprintf(fout, "%d   %d\n", (rand() % 500), (rand() % 500));
	}
	fclose(fout);
	
	return 0;
}
