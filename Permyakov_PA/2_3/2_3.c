#include <stdio.h>

int right_cyclically_array_shift_by_one(const char* input_name, const char* output_name);

int main(int argc, char** argv)
{
    char* input_filename;
    char* output_filename;
    int ans;
    if (argc != 3){
        printf("incorrect number of arguments. need two arguments - input and output filenames\n");
	    return -1;
    }
    input_filename = argv[1];
    output_filename = argv[2]
    ans = right_cyclically_array_shift_by_one(input_filename, output_filename);
    if (ans == -2){
	    printf("can't open input file\n");
	    return 2;
    }
    if (ans == -3){
    	printf("incorrect input data - nondigit stuff\n");
	    return 3;
    }
    printf("Array shifted.\n")
    return 0;
}
int right_cyclically_array_shift_by_one(const char* input_name, const char* output_name)
{
    FILE *inputfile;
    FILE *outputfile;
    int first_elem;
    int elem;
    inputfile = fopen(input_name, "r");
    outputfile = fopen(output_name, "w");
    fscanf(inputfile, "%d", &first_elem);
    fscanf(inputfile, "%d", &first_elem);
    while (fscanf(inputfile, "%d", &elem) == 1){
        fprintf(outputfile, "%d\n", elem);
    }
    fprintf(outputfile, "%d\n", first_elem);
    if (!feof(inputfile)){
	    fclose(inputfile);
	    return -3;
    }
    fclose(inputfile);
    fclose(outputfile);
    return 0;
}