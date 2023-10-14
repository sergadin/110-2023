#include <stdio.h>

int main(void)
{
    int x, y, z, read, num, cur=0;
    FILE *input, *output;
    input = fopen("input.txt", "r");
    if(input == NULL){
        printf("Не удалось открыть файл\n");
        return -1;
    }
    fscanf(input, "%d %d", &x, &y);
    if (x == 0){
        printf("Указана некорректная последовательность\n");
        return -1;
    }
    z = x;
    while(y != 0){
        read = fscanf(input, "%d", &y);
        if(read == 1){
            if(x >= y && y != 0){
                cur = cur + 1;
                num = cur;
                x = y;
            }
            else{
                cur = cur + 1;
            }
        }
        else{
            printf("Ошибка введенной последовательности\n");
            return -1;
        }
    }
    output = fopen("output.txt", "w");
    if(x == z && num < 1){
        fprintf(output, "Номер наименьшего - %d\n", num);
    }
    else{
        fprintf(output, "Номер наименьшего - %d\n", num + 1);
    }
    return 0;
}