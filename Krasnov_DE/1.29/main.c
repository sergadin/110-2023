#include <stdio.h>
#include <stdlib.h>


float tochka (FILE *f1, float x);
float proizvodnaya (FILE *f2, float y);


int main(void){

    float c, z, a;
    int k=0;
    FILE *f1;
    FILE *f2;
    FILE *f3;
    f1 = fopen("input.txt", "r");
    f2 = fopen("input.txt", "r");
    f3 = fopen("input.txt", "r");
    if(f1 == NULL){
        printf("file not open");
        return -1;
    }
    while((a=fscanf(f3, "%f", &z))!=EOF){
        if(a!=1){
            printf("est char");
            return -1
        }
        k++;
    }
    if(k==0){
        printf("file pust");
        return -1;
    }

    printf("vvedi tochku X\n");
    scanf("%f", &c);
    printf("znajenie v tochke x ravno %f\n", tochka(f1, c));
    printf("znajenie proizvod v tochke x ravno %f", proizvodnaya(f2, c));
    fclose(f1);
    fclose(f2);
    fclose(f3);
    return 0;
}

float tochka (FILE *f1, float x){
    float chislo, znajenie_v_tochke = 0, stepen_x = 1;
    int flag = 0 ;
    while(fscanf (f1, "%f", &chislo) == 1){
            znajenie_v_tochke = znajenie_v_tochke + chislo * stepen_x ;
            flag = flag + 1;
            stepen_x = stepen_x * x;
        }
    return znajenie_v_tochke;
    }



float proizvodnaya (FILE *f2, float y){
    float chislo, proizvodnay_v_tochke = 0, stepen_y = 1;
    int flag = 0;
    while(fscanf(f2, "%f", &chislo) == 1){
            if(flag >= 1){
                proizvodnay_v_tochke = proizvodnay_v_tochke + chislo * stepen_y * flag;
                stepen_y = stepen_y * y;
            }
            flag = flag + 1;

        }
    return proizvodnay_v_tochke;
    }




