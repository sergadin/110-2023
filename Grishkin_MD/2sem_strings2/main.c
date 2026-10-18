#include "compare_files.h"

void read_file(const char *filename, char lines[MAX_LINES][MAX_LINE_LENGTH], int *line_count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    *line_count = 0;
    while (fgets(lines[*line_count], MAX_LINE_LENGTH, file) && *line_count < MAX_LINES) {
        (*line_count)++;
    }

    fclose(file);
}


int main(void)
{
    char linesA[MAX_LINES][MAX_LINE_LENGTH];
    char linesB[MAX_LINES][MAX_LINE_LENGTH];
    int countA, countB;

    read_file("fileA.txt", linesA, &countA);
    read_file("fileB.txt", linesB, &countB);

    compare_files(linesA, countA, linesB, countB);

    return 0;
}
