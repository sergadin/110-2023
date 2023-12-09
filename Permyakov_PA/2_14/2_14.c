#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int x_segments_changement(float* array, const int length, const float x, const char* output_name);

int main(int argc, char** argv)
{
    FILE* inputfile;
    char* input_filename;
    int ans;
    float x;
    float* array;
    int length;
    if (argc != 4){
        printf("incorrect number of arguments. need three arguments - x, input and output filenames\n");
	    return 1;
    }
    sscanf(argv[1], "%f", &x);
    input_filename = argv[2];
    inputfile = fopen(input_filename, "r");
    array = (float*)malloc((length) * sizeof(float));
    if (array == NULL){
        printf("memory allocation error\n");
        return 6;
    }
    if (!fscanf(inputfile, "%d", &length)) {
		printf("input data error\n");
        return 2;
    }
    for (int i = 0; i < (length); i++) {
		if (fscanf(inputfile, "%f", &array[i]) != 1) {
			printf("input data error\n");
            return 2;
		}
	}
    ans = x_segments_changement(array, length, x, output_filename);
    if (ans == -2){
	    printf("can't open input file\n");
	    return 3;
    }
    if (!feof(inputfile)){
    	printf("incorrect input data - nondigit stuff or incorrect length\n");
	    return 4;
    }
    if (ans == -5){
    	printf("can't open output file\n");
	    return 5;
    }
    printf("Elemnts changed.\n");
    free(array);
    fclose(inputfile);
    return 0;
}

int x_segments_changement(float* array, const int length, const float x)
{
    FILE* output;
    int start = -2;
    for (int j = 0; j < (length); j++){
        if ((fabs(array[j] - x) < 0.000001) && (start == -2)){
            start = j - 1;
        }
        else if ((fabs(array[j] - x) > 0) && (start != -2)){
	    if (start == -1){
	        for (int k = start; k < j; k++){
                array[k] = 0.5 * (0 + array[j]);
            	}
	    }
	    else if (j == length - 1){
	    	for (int k = start; k < j; k++){
                array[k] = 0.5 * (0 + array[j]);
                }
	    }
	    else {
            for (int k = start; k < j; k++){
                array[k] = 0.5 * (array[start] + array[j]);
            }
            start = -1;
	    }
        }
    }
    return 0;
}
