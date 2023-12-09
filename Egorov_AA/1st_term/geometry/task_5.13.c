#include <stdio.h>


int main(void){
	FILE* input;
    int n;
    int* x-axis, * y-axis;
    if ((input = fopen("input.txt", "r") == NULL) {
        printf("failed to open input file");
        return -1;
    }
    
    fscanf(input, "%d", &n);
    
    x-axis = (int*)malloc(n * sizeof(int));
    if (x-axis == NULL){
        printf("memory allocation error");
        return -2;
    }
    
    y-axis = (int*)malloc(n * sizeof(int));
    if (y-axis == NULL){
        printf("memory allocation error");
        return -3;
    }
    
    for (int i = 0; i < n; i++)
        fscanf(input, "%d", &x-axis[i]);
    for (int i = 0; i < n; i++)
        fscanf(input, "%d", &y-axis[i]);
    
    
    
}
