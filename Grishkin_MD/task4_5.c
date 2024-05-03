#include <stdio.h>
#include <stdlib.h>

int* generateNumbers(int n);

int main(void) {
    int n;
    int* arr;

    printf("vvedite N: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("not korr N\n");
        return -1;
    }
    arr = (int*)malloc( n * sizeof(int));
    if(arr == NULL){
        printf("memory error");
        return -1;
    }


    arr = generateNumbers(n);

    for (int i = 0; i < n; i++) {
        printf("%d\n", arr[i]);
    }

    free(arr);

    return 0;
}

int* generateNumbers(int n) {
    int count = 0;
    unsigned char byte1;
    unsigned char byte2;
    unsigned char reversedByte2;
    int* numbers = (int*)malloc(sizeof(int) * n);

    for (int i = 0; count < n; i++) {
        byte1 = i & 0xFF;
        byte2 = (i >> 8) & 0xFF;
        reversedByte2 = 0;

        for (int j = 0; j < 8; j++) {
            reversedByte2 |= ((byte2 >> j) & 1) << (7 - j);
        }

        if (byte1 == reversedByte2) {
            numbers[count] = i;
            count++;
        }
    }

    return numbers;
}

