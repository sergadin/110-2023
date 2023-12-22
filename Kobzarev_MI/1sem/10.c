#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int different_numbers_counter(FILE* input);

int different_numbers_counter(FILE* input) {
    int curr, prev, count;
    count = 0;
    if (fscanf(input, "%d", &curr) != 1) {
        printf("Error reading the file");
        return 0;
    }
    count++;
    prev = curr;
    while (fscanf(input, "%d", &curr) != EOF) {
        if (prev > curr) {
            return -1;
        }
        if (prev < curr) {
            count++;
            prev = curr;
        }
    }
    return count;
}

int main(void)
{
    FILE* input;
    int ans = 0;
    input = fopen("input.txt", "r");
    if (input == NULL)
    {
        printf("Error: could not open the file");
        return -1;
    }

    ans = different_numbers_counter(input);
    if (ans == -1) {
        printf("Error: the sequence does not meet the condition");
        return -1;
    }
    if (ans > 0) {
        printf("%d", ans);
    }
    fclose(input);
    return 0;
}