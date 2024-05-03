#include <stdlib.h>
float tochka (FILE *f1, float x);
float proizvodnaya (FILE *f2, float y);

float tochka (FILE *f1, float x){
    float chislo, znajenie_v_tochke = 0, stepen_x = 1;
    int flag = 0 ;
    while(fscanf (f1, "%f", &chislo) == 1){ //öčęë ń÷čňűâŕţůčé âńĺ ÷čńëŕ čç ďîńëĺäîâŕňĺëüíîńňč
            znajenie_v_tochke = znajenie_v_tochke + chislo * stepen_x ;
            flag = flag + 1;
            stepen_x = stepen_x * x;
        }
        flag = flag + 1;
    return znajenie_v_tochke;
}


float proizvodnaya (FILE *f2, float y){
    float chislo, proizvodnay_v_tochke = 0, stepen_y = 1;
    int flag = 0;
    while(fscanf(f2, "%f", &chislo) == 1){ //öčęë ń÷čňűâŕţůčé âńĺ ÷čńëŕ čç ďîńëĺäîâŕňĺëüíîńňč
            if(flag >= 1){
                proizvodnay_v_tochke = proizvodnay_v_tochke + chislo * stepen_y * flag;
                stepen_y = stepen_y * y;
            }
            flag = flag + 1;

        }
    return proizvodnay_v_tochke;
}


int main(){
    float c, z;
    char file_name[20];
    FILE *f1;
    FILE *f2;
    printf("vvedi nazvanie file\n");
    scanf("%s", file_name);
    f1 = fopen(file_name, "r");
    f2 = fopen(file_name, "r");
    if(f1 == NULL){
        printf("file not open");
        return -1;
    }
    if(feof(f2)==0){
        printf("file pust");
        return -1;
    }
    printf("vvedi tochku X\n");
    scanf("%f", &c);
    printf("znajenie v tochke x ravno %f\n", tochka(f1, c));
    printf("znajenie proizvod v tochke x ravno %f", proizvodnaya(f2, c));
    fclose(f1);
    fclose(f2);

        return 0;
}
