#include <stdio.h>

int is_mirror(byte1, byte2) {
    return ((byte1 & 0xFF) ^ (((byte2 >> 4) & 0x0F) | ((byte2 << 4) & 0xF0))) == 0;
}

int main() {
    int N;
    int count = 0;
    int num = 1;
    int byte1;
    int byte2;

    printf("Number: ");
      if ((scanf ("%d", &N) != 1) || (N < 1)) {
		printf ("nekorrektnoe chislo\n");
        return -1;
    }

    printf("The first %d numbers with the lowest byte being a mirror image of the next byte:\n", N);

    while (count < N) {
         byte1 = (num & 0xFF);
         byte2 = ((num >> 8) & 0xFF);

        if (is_mirror(byte1, byte2)) {
            printf("%d\n", num);
            count++;
        }
        num++;
    }

    return 0;
}
