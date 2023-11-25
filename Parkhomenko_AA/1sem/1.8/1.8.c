#include <stdio.h>
#include <string.h>
#include <math.h>

int OSHIBKA = 0;
int vozr_ili_ybiv_posl(FILE *f) 
//Определить является ли последовательность возрастающей, убывающей

{
int vozr_posl = 0, ybiv_posl = 0;
double tek, pred;

if (fscanf(f, "%lf", &tek) != 1) {
    OSHIBKA = -1;
    return -1;
}

while (fscanf(f, "%lf", &pred) == 1) {
    if (tek < pred) {
        vozr_posl = 1;
    } else if (tek > pred) {
        ybiv_posl = 1;
    }
    tek = pred;
}

if (vozr_posl == 1 && ybiv_posl == 1) {
    return -1;
} else if (vozr_posl == 1) {
    return 1;
} else if (ybiv_posl == 1) {
    return 0;
}
return -1;
}

int main(void) {
int opred_posl;
FILE *f = fopen("1.8.txt", "r");
if (f == NULL) {
    printf("error opening the file\n"); 
    return -1;
}

opred_posl = vozr_ili_ybiv_posl(f);

if (opred_posl == OSHIBKA) {
    printf("error\n"); 
    return -1;
} else if (opred_posl == 1) {
    printf("Последовательность возрастает\n");
} else if (opred_posl == 0) {
    printf("Последовательность убывает\n");
}

fclose(f); 

return 0;
}