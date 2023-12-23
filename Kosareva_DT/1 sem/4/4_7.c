#include <stdio.h>

int main(void);
int digits(int n);

int main(void) {
	int n, check;
	
	check = scanf("%d", &n);
	if (check != 1) {
		return -1;
	}
	
	digits(n);
}

int digits(int n) {
	int i, first, second;
	
	for (i=1; i<n; i+=2) {
		first = i;
		second = 0;
		while (first > second) {
			second = second << 1 + (first & 1);
			first = first >> 1;
		}
		if (first == second) {
			printf("%d ", i);
		}
		else if (second >> 1 == first) {
			printf("%d ", i);
		}
	}
	
	return 0;
}
