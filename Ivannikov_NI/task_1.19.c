#include <stdio.h>
int func(FILE *IN);//Возвращает 1,если больше возрастающих,и 0,если невозрастающих
int func(FILE *IN){
    double prev,cur;//предыдущий и текущиий элементы последовательности
    int insideIncreased = 0;
    int numIncreased=0,numNonIncreased = 0;
    int lenNonIncreased;
    if (scanf(IN,"%lf",&prev) != 1){//некорректное считывание 
        printf("File empty\n");
        return -1;
    }
    lenNonIncreased = 1;
    while (fscanf(IN,"%lf",&cur) == 1){
        if (cur>prev){
            if (!insideIncreased){//если у нас возрастающая последовательность
                insideIncreased = 1;
                ++numIncreased;
                if(lenNonIncreased > 1)
                    ++numNonIncreased;
            }
        } else{
            if (insideIncreased){
                insideIncreased = 0;
                lenNonIncreased = 0;
            }
            ++lenNonIncreased;
        }
        prev = cur;
    }
    if (lenNonIncreased > 0)
        ++numNonIncreased;
    return((numIncreased > numNonIncreased) ? 1 : 0);

}
int main(void){
    FILE *IN,*OUT;
    IN=fopen("input.txt","r");
    if (IN == NULL){
        printf("File input.txt not opened\n");
        return -1;
    }
    int res;
    res=func(IN);
    fclose(IN);
    if (res!=0)
        return -1;
    OUT=fopen("output.txt","w");
    if(OUT == NULL){
        printf("File output.txt not opened\n");
        return -1;
    }
    fprintf(OUT,"%d\n",res);
    fclose(OUT);
    return 0;
}
