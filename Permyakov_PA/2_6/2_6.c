#include <stdio.h>
#include <stdlib.h>

int sets_interseption(const int* array1, const int* array2, const int length1, const int length2, const char* output_filename);

int main(int argc, char** argv)
{
    FILE* inputfile1;
    FILE* inputfile2;
    char* input_filename1;
    char* input_filename2;
    char* output_filename;
    int ans;
    int* array1;
    int* array2;
    int length1;
    int length2;
    int cnt = 0;
    int i = 0;
    if (argc != 4){
        printf("incorrect number of arguments. need three arguments - two input and output filenames\n");
	    return -1;
    }   
    input_filename1 = argv[1];
    input_filename2 = argv[2];
    output_filename = argv[3];  
    inputfile1 = fopen(input_filename1, "r");
    inputfile2 = fopen(input_filename2, "r");
    if (inputfile1 == NULL){
        printf("can't open first input file");
        return 1;
    }
    if (inputfile2 == NULL){
        printf("can't open second input file");
        return 1;
    }
    if (!fscanf(inputfile1, "%d", &length1)){
        printf("incorrect input data\n");
	    return 3;
    }
    array1 = (int*)malloc((length1) * sizeof(int));
    while (fscanf(inputfile1, "%d", &array1[i]) == 1){
        i++;
        cnt++;
    }
    if (cnt != length1){
        printf("incorrect first array length :(\n");
        return 4;
    }
    cnt = 0;
    i = 0;
    if (!fscanf(inputfile2, "%d", &length2)){
        printf("incorrect input data\n");
	    return 3;
    }
    array2 = (int*)malloc((length2) * sizeof(int));
    while (fscanf(inputfile2, "%d", &array2[i]) == 1){
        i++;
        cnt++;
    }
    if (cnt != length2){
        printf("incorrect second array length :(\n");
        return 4;
    }
    ans = sets_interseption(array1, array2, length1, length2, output_filename);
    if (ans == -2){
	    printf("can't open input file\n");
	    return 2;
    }
    if (!feof(inputfile1)){
    	printf("incorrect first input data - nondigit stuff\n");
	    return 3;
    }
    if (!feof(inputfile2)){
    	printf("incorrect second input data - nondigit stuff\n");
	    return 3;
    }
    fclose(inputfile1);
    fclose(inputfile2);
    if (ans == -5){
    	printf("can't open output file\n");
	    return 5;
    }
    free(array1);
    free(array2);
    printf("Interseption done.\n");
    printf("Length: %d", ans);
    return 0;
}

int min(int a, int b)
{
    
}

int sets_interseption(const int* array1, const int* array2, const int length1, const int length2, const char* output_filename)
{
    int* interseption;
    int counter = 0;
    outputfile = fopen(output_filename, "w");
    if (outputfile == NULL){
        return -5;
    }
    for (i = 0; i < length1; i++){
        for (j = 0; j < length2; j++){
            if (array1[i] == array2[j]){
                fprintf(outputfile, "%d\n", array1[i]);
                counter++;
            }
        }
    }
    fclose(outputfile);
    return counter;
}
