#include <stdio.h>
#include <stdlib.h>

void symbol_writing_symbols(const unsigned int* data, const int length, char symbol);

void row_writer(const unsigned int row, char symbol);

int main(int argc, char** argv)
{
    FILE* inputfile;
    char* inputfile_name;
    unsigned int* data;
    int length;
    char symbol;
    if (argc != 3){
        printf("incorrect number of arguments. need two argument - input filename and symbol to write with\n");
        return 1;
    }
    inputfile_name = argv[1];
    if (!sscanf(argv[2], "%c", &symbol)){
        printf("incorrect input data - need symbol instead of string");
        return 2;
    }
    inputfile = fopen(inputfile_name, "r");
    if (!inputfile){
        printf("incorrect inputfile\n");
        return 2;
    }
    if (!fscanf(inputfile, "%d", &length)){
        printf("incorrect input data. input file must be of the form: number of symbols on the first line, then data.\n");
        return 3;
    }
    length *= 2;
    data = (unsigned int*)malloc((length) * sizeof(unsigned int));
    if (data == NULL){
        printf("memory allocation error\n");
        return 5;
    }
    for (int i = 0; i < length; i++){
        if (!fscanf(inputfile, "%u", &data[i])){
            printf("incorrect input data\n");
            return 4;
        }
    }
    symbol_writing_symbols(data, length, symbol);
    return 0;
}

void symbol_writing_symbols(const unsigned int* data, const int length, char symbol)
{
    int mask = ((1 << 8) - 1);
    for (int j = 0; j < 32; j += 8){
        for (int i = 0; i < (length); i += 2){
            row_writer(((mask << j) & data[i]) >> j, symbol);
            printf("\t");
        }
        printf("\n");
    }
    for (int j = 0; j < 32; j += 8){
        for (int i = 1; i < (length); i += 2){
            row_writer(((mask << j) & data[i]) >> j, symbol);
            printf("\t");
        }
        printf("\n");
    }
}

void row_writer(const unsigned int row, char symbol)
{
    for (int k = 0; k < 8; k++){
        if (row & (1 << k)){
            printf("%c", symbol);
        }
        else {
            printf(" ");
        }
    }
}