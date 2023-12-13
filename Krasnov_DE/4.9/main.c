#include <stdio.h>
#include <stdlib.h>


long long int exponentiation(long long int a, long long int n);

long long int exponentiation(long long int a, long long int n){
	long long int res = 1;
	int k = 0;
	while (n > 0){
		if (n & 1 != 0) {
			res = res*a;
			n--;
		}
		else {
			a = a*a;
			n = n >> 1;
		}
		k++;
	}
    printf("%d",k);
	return res;
}

int main(void){
    FILE *output;
    long long int x;
    long long int N;
    output = fopen ("output.txt", "w");
    if(output == NULL){
        printf("Error open file\n");
        return -1;
    }
    printf("vvedi chislo:");
    scanf("%lld",&x);
    x=abs(x);
    printf("vvedi stepen:");
    scanf("%lld",&N);

    x = exponentiation(x,N);

    fprintf(output,"%lld",x);
    return 0;
}


