#include "difference.h"

static void FindMaxLengthAndNumber(FILE* file, size_t* length, size_t* number)
{	
	FILE *file;
    	char *buffer = NULL;
	size_t buffer_size = 0;
	size_t read;
	size_t c = 0;
	int max_length = 0;

    	while ((read = getline(&buffer, &buffer_size, file)) != -1)
    	{
        	if (read > max_length){
            		max_length = read;
       		}
		c++;
    	}
    	free(buffer);

    	size_t *length = max_length;
	size_t *number = c;
}

int FindDifference(char* Afilename, char* Bfilename, char* outputfilename, error* err)
{
	FILE* A;
	FILE* B;
	FILE* out;
	char* linea = NULL;
	char** linesB = NULL;
	size_t lena = 0;
	size_t lenb = 0;
	size_t len = 0;
	size_t number_a = 0;
	size_t number_b = 0;
	size_t start = 0;
	size_t found = 0;
	int prev_founded = -1;
	out = fopen(outputfilename, "w");
	if (out == NULL){
		err = OUTPUT_ERROR;
		return -1;
	}
	A = fopen(Afilename, "r");
        if (A == NULL){
                err = INPUT_ERROR;
		fclose(out);
                return -1;
        }
        B = fopen(Bfilename, "r");
        if (B == NULL){
                err = INPUT_ERROR;
                fclose(A);
		fclose(out);
                return -1;
        }
	FindMaxLengthAndNumber(A, &lena, &number_a);
	FindMaxLengthAndNumber(B, &lenb, &number_b);
	if (lena > lenb){
		len = lena;
	}
	else{
		len = lenb;
	}
	linea = (char*)malloc(len * sizeof(char));
	if (linea == NULL){
		err = MALLOC_ERROR;
		fclose(A);
		fclose(B);
		fclose(out);
		return -1;
	}
	linesB = (char**)malloc(max_lines * sizeof(char *));
    	for (int i = 0; i < number_b; i++){
        	linesB[i] = (char *)malloc(len * sizeof(char));
    	}

	if (lineb == NULL){
		err = MALLOC_ERROR;
		free(linea);
		fclose(A);
		fclose(out);
		fclose(B);
		return -1;
	}
	fprintf(out, "перед первой строкой добавлено:")
	for (int i = 0; i < number_a; i++){
		fgets(&linea, len, A);
		for (int j = start; j < number_b; j++){
			if (strcmp(linea, linesB[j]) == 0){
				found = 1;
				start = j + 1;
				prev_founded = i;
				if (prev_founded > 0){
					fprintf("между строками ")
				}
				break;
			}
			fprintf(out, "%s", linesB[j]);
		}
		if (found == 0){
			fprintf(out, "Удалена строка: %s", lines)
		}
	}
}
