#include <stdio.h> 
 
int PoiskKvadrata(unsigned int icon[32]); 
 
int main() { 
    unsigned int icon[32]; 
    for (int i = 0; i < 32; i++) { 
        scanf_s("%u", &icon[i]); 
    } 
 
    int result = PoiskKvadrata(icon); 
 
    if (result != -1) { 
        printf("The black square is in the rows: %d - %d\n", result+1, result+4); 
    } 
    else { 
        printf("There is no black square on the icon\n"); 
    } 
 
    return 0; 
} 
 
int PoiskKvadrata(unsigned int icon[32]) { 
    unsigned int memory, column; 
    int i, j,  rab, counter=0,  strnum; 
    for (i=0;i<32;i++) { 
        column = icon[i]; 
        for (j=0;j<32;j++) { 
            rab = column % 2; 
            if (rab == 0) { 
                if (counter == 0) { 
                    strnum = j; 
                    memory = column; 
                } 
                counter++; 
                if (counter == 4) { 
                    for (int ii = i + 1; ii < i + 4; ii++ ) { 
                        column = icon[ii]; 
                        for (int jj = 0; jj < 32; jj++) { 
                            if (jj == strnum) { 
                                rab = column % 2; 
                                if (rab == 1) 
                                    goto metka; 
                            } 
                            if ((jj == strnum + 1 || jj == strnum + 2) && ii<i+3) { 
                                rab = column % 2; 
                                if (rab == 0) 
                                    goto metka; 
                            } 
                            if ((jj == strnum + 1 || jj == strnum + 2) && ii == i + 3) { 
                                rab = column % 2; 
                                if (rab == 1) 
                                    goto metka; 
                            } 
                            if (jj == strnum+3) { 
                                rab = column % 2; 
                                if (rab == 1) 
                                    goto metka; 
                            } 
                            column = column >> 1; 
                        } 
                    } 
                    return i; 
                metka: 
                    counter = 0; 
                    column = memory; 
                } 
            } 
            else { 
                counter = 0; 
            } 
            column = column >> 1; 
        } 
        counter = 0; 
    } 
    return -1; 
}