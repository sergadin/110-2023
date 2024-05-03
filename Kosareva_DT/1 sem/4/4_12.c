#include <stdio.h>

int main(void);
unsigned char contain(int digit, int i);

unsigned char contain(int digit, int i) {
	return (digit >> (24 - i*8)) & 255;
}

int main(void) {
	int digit;
	FILE *f;
	unsigned char a[4];
	
	scanf("%d", &digit);
	
	printf("%d\n%d\n%d\n%d\n", contain(digit, 0), contain(digit, 1), contain(digit, 2), contain(digit, 3));
	
	return 0;
}
