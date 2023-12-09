#include <stdio.h>
#include <stdlib.h>

int right_cyclically_array_shift_by_one(int* array, int length);

int main(int argc, char** argv)
{
    FILE* inputfile;
    char* input_filename;
    int ans;
    int* array;
    int length;
    if (argc != 2){
        printf("incorrect number of arguments. need one argument - input filename\n");
	    return -1;
    }   
    input_filename = argv[1];  
    inputfile = fopen(input_filename, "r");
    array = (int*)malloc((length) * sizeof(int));
    if (array == NULL){
        printf("memory allocation error\n");
        return 6;
    }
    if (!fscanf(inputfile, "%d", &length)) {
		printf("input file error\n");
		return 2;
    }
    for (int i = 0; i < length; i++) {
		if (fscanf(inputfile, "%d", &array[i]) != 1) {
			printf("input data error\n");
			return 2;
		}
	}
    ans = right_cyclically_array_shift_by_one(array, length);
    if (ans == -2){
	    printf("can't open input file\n");
	    return 2;
    }
    if (!feof(inputfile)){
    	printf("incorrect input data - nondigit stuff or incorrct length\n");
	    return 3;
    }
    printf("Array shifted.\n");
    for (int i = 0; i < (length); i++){
        printf("%d\n", array[i]);
    }
    fclose(inputfile);
    return 0;
}

int right_cyclically_array_shift_by_one(int* array, int length)
{
    int elem = 0;
    elem = array[length - 1];
    for (int i = 1; i < (length); i++){
        array[length - i] = array[length - i - 1];
    }
    array[0] = elem;
    return 0;
}
