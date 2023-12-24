#include <stdio.h> 
 
int Opredeleniesquare(unsigned int icon[32], int stroka, int strnum); 
int PoiskKvadrata(unsigned int icon[32], unsigned int* ykazcol); 
 
int main(void) { 
    FILE* txt; 
    unsigned int icon[32], colnum, *ykazcol, i, j; 
    char simvol; 
    ykazcol = &colnum; 
    txt = fopen(&txt, "in.txt", "r"); 
    if (txt == NULL) { 
        printf("Не удалось открыть файл\n"); 
        return -1; 
    } 
 
    for (int i = 0 ; i < 32 ; i++ ) 
    { 
        icon[i]=0; 
    } 
 
    for (i=0;i<32;i++) { 
        for (j = 0; j < 32; j++) { 
            simvol=fgetc(txt); 
            printf("%c", simvol); 
            if (simvol == '*') 
                icon[i] = icon[i] + (1 << j); 
        } 
        printf("\n"); 
        fgetc(txt); 
    } 
 
    fclose(txt); 
     
 
    int result = PoiskKvadrata(icon, ykazcol); 
 
    if (result != -1)  
    { 
        printf("The black square is in the rows: %d - %d\n", result+1, result+6); 
        printf("The black square is in the columns: %d - %d\n", colnum + 1, colnum + 6); 
    } 
    else  
    { 
        printf("There is no black square on the icon\n"); 
    } 
 
    return 0; 
} 
 
int PoiskKvadrata(unsigned int icon[32], unsigned int * ykazcol) { 
    unsigned int memory, column; 
    int i, j,  rab,  strnum; 
    for (i = 0 ; i < 32; i ++)  
    { 
        column = 63; 
        for ( j = 0 ; j < 32; j ++ )  
        { 
            rab = (column& icon[i]) >> j; 
            if (rab == 63)  
            { 
                if (Opredeleniesquare(icon, i, j)) 
                { 
                    *ykazcol = j; 
                    return i; 
                } 
                     
            } 
            column = column << 1; 
        } 
    } 
    return -1; 
} 
 
int Opredeleniesquare(unsigned int icon[32], int stroka, int col) { 
    int i, rab, column=63; 
    for (int i = stroka + 1; i < stroka + 6; i ++)  
    { 
        rab = ((column<<col) & icon[i]) >> col; 
        if (rab != 33 && (i == stroka + 1 || i == stroka + 4)) 
        { 
            return 0; 
        } 
        if (rab != 45 && (i == stroka + 3 || i == stroka + 2)) 
        { 
            return 0; 
        } 
        if (rab != 63 && i == stroka + 5) 
        { 
            return 0; 
        } 
    } 
    return 1; 
}