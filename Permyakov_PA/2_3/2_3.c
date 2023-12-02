#include <stdio.h>

int right_cyclically_array_shift_by_one(const char* input_name, const char* output_name);

int main(int argc, char** argv)
{
    char* input_filename;
    char* output_filename;
    int ans;
    FILE *inputfile;
    int length;
    int *array;
    if (argc != 3){
        printf("incorrect number of arguments. need two arguments - input and output filenames\n");
	    return -1;
    }
    input_filename = argv[1];
    output_filename = argv[2];
    inputfile = fopen(input_filename, "r");
    array = (int*)malloc((length) * sizeof(int));
    for (int i = 1; i < length; i++){
        fseek(inputfile, i, SEEK_END);
	array[i - 1] = fgetc(inputfile);
    }
    ans = right_cyclically_array_shift_by_one(array, length);
    if (!inputfile){
	printf("can't open input file\n");
	return 1;
    }
    if (ans == -1){
    	printf("can't open output file\n");
        return 2;
    }
    if (ans == -3){
    	printf("incorrect input data - nondigit stuff\n");
	return 3;
    }
    printf("Array shifted.\n");
    return 0;
}
int right_cyclically_array_shift_by_one(const int* array, const int* length)
{
    FILE *outputfile;
    inputfile = fopen(input_name, "r");
    outputfile = fopen(output_name, "w");
    if (!outputfile){
        return 1;
    }
    fseek(inputfile, length, SEEK_END);
    fprintf(outputfile, "%d", fgetc(inputfile));
    for (int i = 1; i < length + 1; i++){
        fseek(inputfile, i, SEEK_END);
	fprintf(outputfile, "%d", fgetc(inputfile));
    }
    if (!feof(inputfile)){
	fclose(inputfile);
	return -3;
    }
    fclose(inputfile);
    fclose(outputfile);
    return 0;
}
