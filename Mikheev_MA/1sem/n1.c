#include <stdio.h>

int main(void)
{
    int x, y, z, num, cur=0;
    FILE *input, *output;
    input = fopen("input.txt", "r");
    if(input == NULL){
        printf("Не удалось открыть файл");
        return -1;
    }
    fscanf(input, "%d %d", &x, &y);
    if (x == 0){
        printf("Указана некорректная последовательность");
        return -1;
    }
    z = x;
    while(y != 0){
        fscanf(input, "%d", &y);
        if(x > y && y != 0){
            cur = cur + 1;
            num = cur;
            y = x;
        }
        else{
            cur = cur + 1;
        }
    }
    output = fopen("output.txt", "w");
    if(x == z){
        fprintf(output, "Номер наименьшего - %d", num);
    }
    else{
        fprintf(output, "Номер наименьшего - %d", num + 1);
    }
    return 0;
}