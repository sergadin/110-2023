#include <stdio.h> 
 
int Opredeleniesquare(unsigned int icon[32], int stroka, int strnum); 
int PoiskKvadrata(unsigned int icon[32]); 
 
int main(void) { 
    unsigned int icon[32]; 
    for (int i = 0 ; i < 32 ; i++ ) 
    { 
        scanf( "%u", &icon[i] ); 
    } 
 
    int result = PoiskKvadrata(icon); 
 
    if (result != -1)  
    { 
        printf("The black square is in the rows: %d - %d\n", result+1, result+6); 
    } 
    else  
    { 
        printf("There is no black square on the icon\n"); 
    } 
 
    return 0; 
} 
 
int PoiskKvadrata(unsigned int icon[32]) { //ищет 6 подряд идущих единиц
    unsigned int memory, column, rab; 
    int i, j, counter = 0,  strnum; 
    for (i = 0 ; i < 32; i ++)  
    { 
        column = icon[i]; 
        for ( j = 0 ; j < 32; j ++ )  
        { 
            rab = column % 2; 
            if (rab == 1)  
            { 
                if (counter == 0) 
                { 
                    strnum = j; 
                    memory = column; 
                } 
                counter ++; 
                if (counter == 6)  
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
    for (int i = stroka + 1; i < stroka + 6; i ++)  
    { 
        column = icon[i]; 
        for (int j = 0; j < 32; j++) 
        { 
            if (j == strnum) 
            { 
                rab = column % 2; 
                if (rab == 0) 
                    return 0; 
            } 
            if ((j > strnum  && j < strnum + 5) && (i== stroka + 4 || i == stroka + 1)) 
            { 
                rab = column % 2; 
                if (rab == 1) 
                    return 0; 
            } 
            if ((j > strnum && j < strnum + 5) && i == stroka + 5) 
            { 
                rab = column % 2; 
                if (rab == 0) 
                    return 0; 
            } 
            if ((j == strnum+1 && j == strnum + 4) && (i == stroka + 3 && i == stroka + 2)) 
            { 
                rab = column % 2; 
                if (rab == 1) 
                    return 0; 
            } 
            if ((j == strnum + 2 && j == strnum + 3) && (i == stroka + 3 && i == stroka + 2)) 
            { 
                rab = column % 2; 
                if (rab == 0) 
                    return 0; 
            } 
            if (j == strnum + 5)  
            { 
                rab = column % 2; 
                if (rab == 0) 
                    return 0; 
            } 
            column = column >> 1; 
        } 
    } 
    return 1; 
} 
/* 
1 
1 
0
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
1 
1 
1 
0 
1 
-89303805 
-89303685 
-89303733 
-89303733 
-89303685 
-89303805 
0 
1 
1 
*/