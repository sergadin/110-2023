#include <stdio.h>
#include <stdlib.h>

int get_quantity(int x);


int get_quantity(int x){
    int k=0;
    while(x>0){
        if((x & 1) != 0){
            k++;
        }
        x = x >> 1;
    }

    return k;
}


main (void){
    FILE *output;
    int x;
    int quantity;
    printf ("Vvedi X: ");
    scanf ("%d", &x);
    x=abs(x);
    output = fopen ("output.txt", "w");
    if(output == NULL){
        printf("Error open file\n");
        return -1;
    }
    quantity= get_quantity(x);
    if(quantity % 2 == 0){
        fprintf (output, "chetno");
    }
    else{
        fprintf (output, "ne chetno");
    }
    fclose (output);
    return 0;
}



