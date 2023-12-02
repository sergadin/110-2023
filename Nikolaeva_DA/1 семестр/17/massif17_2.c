#include <stdio.h>
#include <stdlib.h>
FILE* data;
 
int Check(int*array, int N, int x); 
int dense(int *array, int N);

int Check(int*array, int N, int x)
{
    for (int i = 0; i < N; i++)
    {
        if (array[i] == x)
        {
            return 1;
        }
    }
    return 0;
}


int dense(int *array, int N)
{   
    
    int a = array[0];
    int min = a;
    int max = a;
    
    for (int i = 1; i < N; i++)
    {
        
        a = array[i];
        
        if(min > a)
        {
            min = a;
        }
        
        if(max < a)
        {
            max = a;
        }
    }
    
    //ряд одинаковых чисел 
    if (max == min) 
    {
        return -1;
    }
    
    for (int i0 = min + 1; i0 < max; i0++)
    {
        if (!Check(array, N, i0)) 
        {
            return -1;
        }
    }
    
    return 1;
}


int main(void)
{
        int itog;
        int n;
        FILE *answer;
        int *array = NULL;
        
        
        answer = fopen("output.txt", "w");
        
        //Проверка существует ли answer
        if (!answer) 
        {     
            printf("What?\n");
            return -1;
        }
 
        data = fopen("np.txt", "r");
        
        //Проверка есть ли data
        if (!data) 
        {     
            printf("ERR\n");
            return -1;
        }
 
 
        //Проверяем, считалось ли число
        if (fscanf(data, "%d", &n)!=1)
        {
                printf("no values\n");
                return -1;
        }
        
        array = (int *)malloc(n*sizeof(int));
        
        for (int i = 0; i < n; i++)
        {       
                // считался ли элемент
                if(fscanf(data, "%d", &array[i]) != 1) 
                {
                        printf("FGH\n");
                        return -1;
                }
        }
        
        fclose(data);
        itog = dense(array, n);
        
        if (itog == 1) 
        {
                printf("плотный\n");
        }
        
        if (itog == -1)
        {
                printf("не плотный\n");
 
        }
 
        fclose(answer);
        return 0;
}
