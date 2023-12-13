#include <stdio.h>


int bites_inverse(int N, int i, int j);

int main(int argc, char** argv){
    int i;
    int j;
    int N;
    int c;
    if (argc != 4){
        printf("incorrect number of arguments. need tree arguments: number for inverting and inverse borders\n");
	    return 1;
    }
    if ((sscanf(argv[1], "%d", &N) != 1) || (sscanf(argv[2], "%d", &i) != 1) || (sscanf(argv[3], "%d", &j) != 1)){
        printf("incorrect input data - need natural numbers");
        return 2;
    }
    if ((N < 1) || (i < 1) || (j < 1)){
        printf("incorrect input data - need natural numbers");
        return 2;
    }
    if (i > j){
        c = j;
        j = i;
        i = c;
    }
    N = bites_inverse(N, i, j);
    printf("%d", N);
    return 0;
}

int bites_inverse(int N, int i, int j)
{
    int mask = ((1 << ((j - i) + 1)) - 1) << (i - 1);
    return N ^ mask;    
}