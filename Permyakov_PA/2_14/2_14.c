#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define OUTSIDE -2
#define BEGINNING -1

int x_segments_changement(float* array, int length, float x);

int main(int argc, char** argv)
{
<<<<<<< HEAD
    FILE* inputfile;
    char* input_filename;
    int ans;
    float x;
    float* array;
    int length;
    if (argc != 3){
        printf("incorrect number of arguments. need three arguments - x and input filename\n");
	    return 1;
    }
    if (sscanf(argv[1], "%f", &x) != 1){
        printf("incorrect input data - need real number\n");
	    return 2;
    }
    input_filename = argv[2];
    inputfile = fopen(input_filename, "r");
    if (!inputfile){
        printf("incorrect inputfile\n");
        return 3;
    }
    if (!fscanf(inputfile, "%d", &length)) {
		printf("input data error\n");
        return 5;
    }
    array = (float*)malloc((length) * sizeof(float));
    if (array == NULL){
        printf("memory allocation error\n");
        return 4;
    }
    for (int i = 0; i < length; i++) {    
        if (fscanf(inputfile, "%f", &array[i]) != 1){
            printf("incorrect array length\n");    
            return -6;
        }
    }
    if (!feof(inputfile)){
	    printf("incorrect input data - nondigit stuff or incorrect length\n");
	    return 7;
    }
    ans = x_segments_changement(array, length, x);
    if (ans == -2){
	    printf("can't open input file\n");
	    return 3;
    }
    printf("Elements changed.\n");
    for (int i = 0; i < length; i++){
        printf("%f\n", array[i]);
    }
    fclose(inputfile);
    free(array);
    return 0;
=======
	FILE* inputfile;
	char* input_filename;
	int ans;
	float x;
	float* array;
	int length;
	if (argc != 3){
		printf("incorrect number of arguments. need three arguments - x and input filename\n");
		return 1;
	}
	if (sscanf(argv[1], "%f", &x) != 1){
		printf("incorrect input data - need real number\n");
		return 2;
	}
	input_filename = argv[2];
	inputfile = fopen(input_filename, "r");
	if (!inputfile){
		printf("incorrect inputfile\n");
		return 3;
	}
	if (!fscanf(inputfile, "%d", &length)) {
		fclose(inputfile);	
		printf("input data error\n");
		return 5;
	}
	array = (float*)malloc((length) * sizeof(float));
	if (array == NULL){
		fclose(inputfile);
		free(array);
		printf("memory allocation error\n");
		return 4;
	}
	for (int i = 0; i < length; i++) {    
		if (fscanf(inputfile, "%f", &array[i]) != 1){
			fclose(inputfile);
			free(array);
			printf("incorrect array length\n");    
			return -6;
		}
	}
	if (!feof(inputfile)){
		fclose(inputfile);
		free(array);
		printf("incorrect input data - nondigit stuff or incorrect length\n");
		return 7;
	}
	ans = x_segments_changement(array, length, x);
	if (ans == -2){
		fclose(inputfile);
		free(array);
		printf("can't open input file\n");
		return 3;
	}
	printf("Elements changed.\n");
	for (int i = 0; i < length; i++){
		printf("%f\n", array[i]);
	}
	fclose(inputfile);
	free(array);
	return 0;
>>>>>>> 123
}

int x_segments_changement(float* array, int length, float x)
{
	int start = OUTSIDE;
	int start_num;
	int end_num;
	for (int j = 0; j < (length); j++){
		if (fabs(array[j] - x) < 0.00001){
			if (start == OUTSIDE){
				start = j - 1;
			}
		}
		if (((fabs(array[j] - x) > 0) && (start != OUTSIDE)) ||
			       	((fabs(array[j] - x) < 0.00001) && (j == (length - 1)))){
			start_num = array[start];
			end_num = array[j];
			if (start == BEGINNING){
				start_num = 0;
			}
			if (j == (length - 1)){
				end_num = 0;
				j = length;
			}
			for (int k = start + 1; k < j; k++){
				array[k] = 0.5 * (start_num + end_num);
			}
			start = -2;
		}
	}
	return 0;
}
