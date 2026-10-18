#include "strings.h"

int main(void) {
    FILE *f = fopen("input.txt", "r");
    if (f == NULL) {
        perror("Failed to open input file");
        return -1;
    }

    FILE *n = fopen("output.txt", "w");
    if (n == NULL) {
        perror("Failed to open output file");
        fclose(f);
        return -1;
    }

    solution(f, n);

    if (error_code == ERR) {
        fprintf(stderr, "An error occurred during processing.n");
        fclose(f);
        fclose(n);
        return -1;
    }

    fclose(n);

    n = fopen("output.txt", "r");
    if (n == NULL) {
        perror("Failed to open output file for reading");
        fclose(f);
        return -1;
    }

    fseek(n, 0, SEEK_END);
    long outputSize = ftell(n);
    fseek(n, 0, SEEK_SET);

    char *outputContent = (char *)malloc(outputSize);
    if (outputContent == NULL) {
        fprintf(stderr, "Failed to allocate memory for output content.n");
        fclose(f);
        fclose(n);
        return -1;
    }

    fread(outputContent, 1, outputSize, n);
    outputContent[outputSize] = '\0';

    if (strlen(outputContent) == 0) {
        fprintf(stderr, "Output file is empty.n");
        free(outputContent);
        fclose(f);
        fclose(n);
        return -1;
    }

    //printf("Output content:%s", outputContent);
    const char *expectedWord = "hgkgkgkdfdf";

    if (strcmp(outputContent, expectedWord) == 0) {
        printf("Output matches the expected word: %s", expectedWord);
    } else {
        printf("Output does not match. Expected: %s, Got: %s", expectedWord, outputContent);
        return -1;
    }

    free(outputContent);
    fclose(f);
    fclose(n);

    return 0;
}
