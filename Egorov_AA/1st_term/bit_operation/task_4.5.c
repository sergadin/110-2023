#include <stdio.h>

void longToCharArray(long num, unsigned char* byteArray) {
    for (int i = 0; i < sizeof(long); i++) {
        byteArray[i] = (num >> (8 * (sizeof(long) - i - 1)));
    }
}

long charArrayToLong(char* byteArray) {
    long num = 0;
    for (int i = 0; i < sizeof(long); i++) {
        num += ((long)(byteArray[i]) << (8 * (sizeof(long) - i - 1)));
    }
    return num;
}

int main(void) {
    long number = 29458723; // Пример числа
    unsigned char byteArray[sizeof(long)];
    longToCharArray(number, byteArray);
    printf("long to char array: ");
    for (int i = 0; i < sizeof(long); i++) {
        printf("%c \n", byteArray[i]);
    }
    printf("\n");

    long new_number = charArrayToLong(byteArray);
    printf("char array to long: %ld\n", new_number);

    return 0;
}
