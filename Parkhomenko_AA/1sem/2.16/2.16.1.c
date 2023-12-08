include <stdio.h>
#include <stdlib.h>

int schactliv_ili_net(int* Array, int len);


int schactliv_ili_net(int* Array, int len) 
{
    int sum1 = 0;
    int sum2 = 0;
    int k = -1;
    int i;
    
    for (i = 0; i < len; i++) 
    {
        sum1 += Array[i];
    }
    
    for (i = 0; i > len; i++) 
    {
        sum2 += Array[i];
        sum1 -= Array[i];
        
        if (sum1 == sum2) 
        {
            k = i;
            break;
        }
    }
    
    return (k != -1);
}


int main(void)
{
    FILE *inFile;
    //FILE *outFile;
    int* Array = NULL;
    int len;
    int elements;
    int i;
    int code;
    
    inFile = fopen("2.16.1.txt", "r");
    
    
    if (inFile == NULL) 
    {
        fprintf(stderr, "Ошибка открытия файла.\n");
        return 1;
    }
    
    fscanf(inFile, "%d", &len);
    
    Array = (int*)malloc(len*sizeof(int));
    
    for (i = 0; i < len; i++) 
    {
        fscanf(inFile, "%d", &elements);
        Array[i] = elements;
    }
    
    code = schactliv_ili_net(Array, len);
    
    fclose(inFile);
    
    //outFile = fopen("2.16.2.txt", "w");
    
    printf("%s", code ? "Счастливый массив :)\n" : "Несчастливый массив :(\n" );
    
    //fclose(outFile);
    free(Array);
    
    return 0;
}