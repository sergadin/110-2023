#include <stdio.h>


unsigned char getByte(long number, int i, int* error);
long changeByte(long number, int i, unsigned char newValue, int* error);


unsigned char getByte(long number, int i, int* error) {

    if (i < 1 || i > sizeof(long)) {
        printf("wrong index\n");
        *error = 1;
    }

    unsigned char byte = (number >> ((i - 1) * 8)) & 0xFF;

    return byte;
}


long changeByte(long number, int i, unsigned char newValue, int* error) {

    if (i < 1 || i > sizeof(long)) {
        printf("wrong index\n");
        *error = 1;
    }

    number &= ~(0xFF << ((i - 1) * 8));
    number |= ((long)newValue << ((i - 1) * 8));

    return number;
}


int main() {
    long number = 0x12345678;
    int i = 4, error = 0;
    unsigned char newValue = 0b1101111;

    printf("given long number - %lx\n\n", number);
    if (error) {
        printf("wrong index\n\n");
        error = 0;
    }
    else {
        printf("%ith byte's value - %d\n\n", i, getByte(number, i, &error));
    }

    printf("given long number - %lx\n\nwill change %ith byte's value to %d\n\n", number, i, newValue);
    if (error) {
        printf("wrong index\n\n");
    }
    else {
        printf("new number - %lx\n\n", changeByte(number, i, newValue, &error));
    }

    return 0;
}
