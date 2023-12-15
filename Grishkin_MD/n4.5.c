#include <stdio.h>

int findMirrorNumber(int n);

int main(void) {
    int n;
    printf("Vvedite N: ");
     if ((scanf ("%d", &n) != 1) || (n < 1)) {
        printf ("nekorrektnoe chislo\n");
        return -1;
    }

    for (int i = 0; i < n; i++) {
        printf("%d\n", findMirrorNumber(i+1));
    }

    return 0;
}

int findMirrorNumber(int n) {
    int num;
    int upByte;
    int lowByte;
    int upBit;
    int lowBit;
    int count = 0;

    for (upByte = 0; count < n; upByte++){
        for (lowByte = 0; lowByte >= 0 && count < n; lowByte++){
            num = (lowByte << 8) + (upByte << 16);
            for ( upBit = 7, lowBit = 0; lowBit < 8; upBit--, lowBit++){
                if ((lowByte >> upBit) & lowBit){
                    num += (1 << lowBit);
                }
            }
            count++;
        }
    }
    return num;
}
