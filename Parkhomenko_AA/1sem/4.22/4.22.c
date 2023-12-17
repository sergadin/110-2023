#include <stdio.h> 
 
int Opredeleniesquare(unsigned int icon[32], int stroka, int strnum); 
int PoiskKvadrata(unsigned int icon[32]); 
 
int main() { 
    unsigned int icon[32]; 
    for (int i = 0 ; i < 32 ; i++ ) 
    { 
        scanf_s( "%u", &icon[i] ); 
    } 
 
    int result = PoiskKvadrata(icon); 
 
    if (result != -1)  
    { 
        printf("The black square is in the rows: %d - %d\n", result+1, result+4); 
    } 
    else  
    { 
        printf("There is no black square on the icon\n"); 
    } 
 
    return 0; 
} 
 
int PoiskKvadrata(unsigned int icon[32]) { 
    unsigned int memory, column; 
    int i, j,  rab, counter=0,  strnum; 
    for (i = 0 ; i < 32; i ++)  
    { 
        column = icon[i]; 
        for ( j = 0 ; j < 32; j ++ )  
        { 
            rab = column % 2; 
            if (rab == 0)  
            { 
                if (counter == 0) 
                { 
                    strnum = j; 
                    memory = column; 
                } 
                counter ++; 
                if (counter == 4)  
                { 
                    if ( Opredeleniesquare( icon, i, strnum ) ) 
                        return i; 
                    counter = 0; 
                    column = memory; 
                } 
            } 
            else  
            { 
                counter = 0; 
            } 
            column = column >> 1; 
        } 
        counter = 0; 
    } 
    return -1; 
} 
 
int Opredeleniesquare(unsigned int icon[32], int stroka, int strnum) { 
    int i, j, rab, column; 
    for (int i = stroka + 1; i < stroka + 4; i ++)  
    { 
        column = icon[i]; 
        for (int j = 0; j < 32; j++) 
        { 
            if (j == strnum) 
            { 
                rab = column % 2; 
                if (rab == 1) 
                    return 0; 
            } 
            if ((j == strnum + 1 || j == strnum + 2) && i < stroka + 3)  
            { 
                rab = column % 2; 
                if (rab == 0) 
                    return 0; 
            } 
            if ((j == strnum + 1 || j == strnum + 2) && i == stroka + 3) 
            { 
                rab = column % 2; 
                if (rab == 1) 
                    return 0; 
            } 
            if (j == strnum + 3)  
            { 
                rab = column % 2; 
                if (rab == 1) 
                    return 0; 
            } 
            column = column >> 1; 
        } 
    } 
    return 1; 
} 
/* 
0 
6 
6 
0 
0 
1 
1 
1 
1 
1 
1 
11 
1 
1 
1 
1 
1 
1 
1 
1 
1 
1 
1 
1 
1 
1 
1 
6 
6 
0 
1 
1 
*/