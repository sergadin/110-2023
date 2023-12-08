#include <stdio.h>
#include <stdlib.h>

int x_segments_changement(float* array, const int length, const float x, const char* output_name);

int main(int argc, char** argv)
{
    FILE* inputfile;
    char* input_filename;
    char* output_filename;
    int ans;
    float x;
    float* array;
    int length;
    int cnt = 0;
    int i = 0;
    if (argc != 4){
        printf("incorrect number of arguments. need three arguments - x, input and output filenames\n");
	    return 1;
    }
    sscanf(argv[1], "%f", &x);
    input_filename = argv[2];
    output_filename = argv[3];
    inputfile = fopen(input_filename, "r");
    array = (float*)malloc((length + 2) * sizeof(float));
    if (array == NULL){
        printf("memory allocation error\n");
        return 6;
    }
    if (!fscanf(inputfile, "%d", &length)) {
		printf("input data error\n");
        return 2;
    }
    for (int i = 1; i < (length + 1); i++) {
		if (fscanf(inputfile, "%d", &array[i]) != 1) {
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
    	printf("incorrect input data - nondigit stuff or incorrct length\n");
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

int x_segments_changement(float* array, const int length, const float x, const char* output_filename)
{
    FILE* output;
    int j = 0;
    int k = 0;
    int start = -1;
    output = fopen(output_filename, "w");
    if (!output){
        return -5;
    }
    for (int j = 1; j < (length + 1); j++){
        if ((array[j] == x) && (start == -1)){
            start == j - 1;
        }
        else if ((array[j] != x) && (start != -1)){
            for (int k = start; k < j; k++){
                array[k] = 0.5 * (array[start] + array[j]);
            }
        start = -1;
        }
    }
    for (int j = 1; j < (length + 1); j++){
        fprintf(output, "%f", array[j]);
    }
    return 0;
}