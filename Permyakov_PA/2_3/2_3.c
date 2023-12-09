#include <stdio.h>
#include <stdlib.h>

int right_cyclically_array_shift_by_one(const int* array, const int length, const char* output_name);

int main(int argc, char** argv)
{
    FILE* inputfile;
    char* input_filename;
    char* output_filename;
    int ans;
    int* array;
    int length;
    int cnt = 0;
    int i = 0;
    if (argc != 3){
        printf("incorrect number of arguments. need two arguments - input and output filenames\n");
	    return -1;
    }   
    input_filename = argv[1];
    output_filename = argv[2];  
    inputfile = fopen(input_filename, "r");
    array = (int*)malloc((length) * sizeof(int));
    if (array == NULL){
        printf("memory allocation error\n");
        return 6;
    }
    if (!fscanf(inputfile, "%d", &length)) {
		printf("input file error\n");
    }
    for (int i = 0; i < length; i++) {
		if (fscanf(inputfile, "%d", &array[i]) != 1) {
			printf("input data error\n");
		}
	}
    ans = right_cyclically_array_shift_by_one(array, length, output_filename);
    if (ans == -2){
	    printf("can't open input file\n");
	    return 2;
    }
    if (!feof(inputfile)){
    	printf("incorrect input data - nondigit stuff or incorrct length\n");
	    return 3;
    }
    if (ans == -5){
    	printf("can't open output file\n");
	    return 5;
    }
    printf("Array shifted.\n");
    free(array);
    fclose(inputfile);
    return 0;
}

int right_cyclically_array_shift_by_one(const int* array, const int length, const char* output_filename)
{
    FILE *outputfile;
    outputfile = fopen(output_filename, "w");
    if (outputfile == NULL){
        return -5;
    }
    fprintf(outputfile, "%d\n", array[length - 1]);
    for (int i = 0; i < (length - 1); i++){
        fprintf(outputfile, "%d\n", array[i]);
    }
    fclose(outputfile);
    return 0;
}