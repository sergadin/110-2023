#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long int exponentiation(long long int a, int n);

long long int exponentiation(long long int a, int n){
	long long int res = 1;
	int k = 0;
	int stepen = n;
	while (n > 0){
		if ( (n & 1) != 0) {
			res = res*a;
			n--;
		}
		else {
			a = a*a;
			n = n >> 1;
		}
		k++;
	}
    printf("%d\n",k);
    if(k < 2*log2(stepen)){
        printf("the program works correctly");
    }
    else{
        printf("error in operation");
    }
	return res;
}

int main(void){
    FILE *output;
    int x;
    int N;
    long long int a;
    output = fopen ("output.txt", "w");
    if(output == NULL){
        printf("Error open file\n");
        return -1;
    }
    printf("vvedi chislo:");
    if((scanf("%d",&x)) != 1){
        printf("vvedeno ne int chislo\n");
        return -1;
    }
    x=abs(x);
    printf("vvedi stepen:");
    if((scanf("%d",&N))!=1){
        printf("vvedeno ne int stepen\n");
        return -1;
    }

    a = exponentiation(x,N);

    fprintf(output,"%lld",a);
    return 0;
}


