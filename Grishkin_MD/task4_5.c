#include <stdio.h>
#include <stdlib.h>

int generateBytes(int n);

int main(void)
{
    int n;
    int* arr;
    printf("Vvedite N: ");
    if((scanf("%d", &n) != 1)|| (n < 0)){
        printf("not korr k\n");
        return -1;
    }
    arr = (int*)malloc(n * sizeof(int));
    if(arr == NULL){
        printf("memory error");
        return -1;
    }

    generateBytes(n);
    arr = generateBytes(n);

    for(int i = 0; i < n; i++){
        printf("%d\n", arr[i]);
    }
    free(arr);
    return 0;
}

int generateBytes(int n)
{
    int Byte2;
    int Byte1;
    int num;
    int startBit;
    int nextBit;
    int count = 0;
    int* numbers;
    numbers = (int*)malloc(n * sizeof(int));
    if(numbers == NULL){
        printf("memory error2");
        return -2;
    }

    for (Byte2 = 0; count < n; Byte2++){
        for (int Byte1 = 0; count < n; Byte1++){
                 num = (Byte1 << 8) + (Byte2 << 16);
            for (nextBit = 7, startBit = 0; startBit < 8; nextBit--, startBit++){
                if ((Byte1 >> nextBit) & 1){
                    num += (1 << startBit);
                }
            }
            numbers[count] = num;
            count++;
        }
    }
    return numbers;
    free (numbers);
}

