#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int search(int* arr, int len, int x);

int search(int* arr, int len, int x)
{
    int left, right, mid, ans;
    
    left = arr[0];
    right = arr[len-1];
    
    if(x <= arr[0]){
        ans = 0;
        return ans;
    }
    
    if(x >= arr[len-1])
    {
        ans = len;
        return ans;
    }
    
    
    while(left<=right)
    {
        mid = (left + right)/2;
        
        if(x > arr[mid] && x < arr[mid+1])
        {
            ans = mid + 1;
            return ans;
        }
        
        if(x > arr[mid])
        {
            left = mid + 1;
        }
        if(x < arr[mid])
        {
            right = mid - 1;
        }
        if(x == arr[mid]){
            ans = mid;
            return ans;
        }
    }
}

int main(void)
{
    FILE* inp;
    int len, i, ans, x;
    int* arr;

    inp = fopen("input.txt", "r");

    if (inp == NULL)
    {
        printf("No input file");
        return -1;
    }
    if (fscanf(inp, "%d", &len) != 1)
    {
        printf("Error reading the file");
        fclose(inp);
        return -1;
    }

    arr = (int*)malloc(len * sizeof(int));

    if (arr == NULL)
    {
        printf("Memory allocation error");
        fclose(inp);
        return -1;
    }

    for (i = 0; i < len; i++)
    {
        fscanf(inp, "%d", &arr[i]);
    }
    
    for(i = 1; i<len; i++)
    {
        if(arr[i]<arr[i-1]){
            printf("Wrong sequence");
            fclose(inp);
            free(arr);
            return -1;
        }
    }
    
    scanf("%d", &x);
    
    ans = search(arr, len, x);
    
    printf("%d", ans);
    
    fclose(inp);
    free(arr);
    return 0;
}