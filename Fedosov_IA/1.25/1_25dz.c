#include <stdio.h>


int function(FILE*);


int main(void){
	FILE *fout, *fin;
	int res;

	fin = fopen("input.txt", "r");

	if (fin == NULL){
		printf("error\n");
		return -1;
	}

	res = function(fin);

	fout = fopen ("output.txt", "w");

	fprintf (fout, "%d", res);

	return 0;

	fclose("input.txt");
	fclose("output.txt");

}


int function(FILE *fin){
	int counter = 0;
	int third;
	int second;
	int first;
	int temp1 = 0;  //переменная для хранения номера настоящего минимума
	int temp2 = 0;	//переменная для хранения номера предыдущего минимума
	int result = 0;

	if (fscanf(fin, "%d", &first) != 1){
		printf ("error\n");
		return -2;
	}

	second = first;

	if (fscanf(fin, "%d", &first) != 1){
                printf ("error\n");
		return -2;
	}

	if (second >= first){
		temp1 = 1;
	}

	third = second;
	second = first;
	
	while (fscanf(fin, "%d", &first) == 1){

		counter ++;

		if (first >= second && third >= second){
			temp2 = temp1;
			temp1 = counter;
		}	

		if (result <= temp1 - temp2 - 1){
			result = temp1 - temp2 - 1;
		}

		third = second;
		second = first;
	}

	if (second < third){
		counter ++;
		temp2 = temp1;
		temp1 = counter;
		if (result <= temp1 - temp2 - 1){
			result = temp1 - temp2 - 1;
		}
	}

	if (feof(fin) == 0){
		printf("error\n");
		return -5;
	}
	
	return result;
}

