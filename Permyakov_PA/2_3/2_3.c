#include <stdio.h>

int right_cyclically_array_shift_by_one(const char* input_name, const char* output_name);

int main(int argc, char** argv)
{
    FILE* inputfile;
    char* input_filename;
    char* output_filename;
    int ans;
    int* array;
    int length;
    int cnt = 0;
    if (argc != 3){
        printf("incorrect number of arguments. need two arguments - input and output filenames\n");
	    return -1;
    }
    input_filename = argv[1];
    output_filename = argv[2];
    inputfile = fopen(input_filename, "r");
    fscanf(input_filename, "%d", length);
    while (fscanf(input_filename, "%d", array[i])){
        i++;
        cnt++;
    }
    
    if (cnt != length){
        printf("incorrect array length :(\n");
        return 4;
    }
    ans = right_cyclically_array_shift_by_one(input_filename, output_filename);
    if (ans == -2){
	    printf("can't open input file\n");
	    return 2;
    }
    if (!feof(inputfile)){
    	printf("incorrect input data - nondigit stuff\n");
	    return 3;
    }
    fclose(inputfile);
    if (ans == -5){
    	printf("can't open output file\n");
	    return 5;
    }
    printf("Array shifted.\n")
    return 0;
}
int right_cyclically_array_shift_by_one(const int* array, const int length, const char* output_name)
{
    FILE *outputfile;
    outputfile = fopen(output_name, "w");
    if (outputfile == NULL){
        return -5;
    }
    fprintf(outputfile, "%d", array[length - 1]);
    for (int i = 1; i < length, i++){
        fprintf(outputfile, "%d", array[i])
    }
    fclose(outputfile);
    return 0;
}