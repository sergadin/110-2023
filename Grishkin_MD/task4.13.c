#include <stdio.h>

int findConfig(int a, int b, int k);

int findConfig(int a, int b, int k)
{
     int mask;
     int pos = 0;
     int sovpadenie = 0;

     mask = (1 << k) - 1;

     for(int i = 0; i < sizeof(int) * 8 - k; i++ ){
     if((b & mask) == ((a >> i) & mask)){
        pos = i + 1;
        sovpadenie  = 1;
        }
     }
     if(sovpadenie){
        return pos;
     }
     else {
        return 0;
     }

}

int main(void)
{
     int a;
     int b;
     int k;
     int config;

     printf("vvedite chislo a:");
     if(scanf("%d", &a) != 1 ){
        printf("not korr a\n");
        return -1;
     }


     printf("vvedite chislo b:");
     if(scanf("%d", &b) != 1){
        printf("not korr b\n");
        return -1;
     }

     printf("vvedite  polozhitel'noe chislo k:");
     if((scanf("%d", &k) != 1)|| (k < 1) || k > sizeof(int) * 8) {
        printf("not korr k\n");
        return -1;
     }

     findConfig(a, b, k);

     config = findConfig(a, b, k);

     if(config == 0){
        printf("not found");
     }
     else printf("position: %d", config);

     return 0;
}
