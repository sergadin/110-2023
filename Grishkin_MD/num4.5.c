#include <stdio.h>

void generateBytes(int n);

int main(void)
{
    int n;
    printf("Enter N: ");
    scanf("%d", &n);

    generateBytes(n);


    return 0;
}

void generateBytes(int n)
{
    int num;
    int startBit;
    int nextBit;
    int count = 0;

    for (int j = 0; count < n; j++){
        for (int i = 0; count < n; i++){
            num = (i << 8) + (j << 16);
            for (startBit = 7, nextBit = 0; nextBit < 8; startBit--, nextBit++){
                if ((i >> startBit) & 1)
                    num += (1 << nextBit);
            }
            printf("%u\n", num);

            count++;
        }
    }
}


