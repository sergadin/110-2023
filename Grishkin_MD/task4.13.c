#include <stdio.h>

int findConfig(int a, int b, int k);

int findConfig(int a, int b, int k)
{
     int res = 1;
     int mask;
     int pos = 0;
     int flag = 0;

     for(int i = 0; i < k; i++) {
        res *= 2;
     }
     res --;
     for(int i = 0; i < 33-k; i++ ){
     if((b & res) == ((a >> i) & res)){
        pos = i + 1;
        flag  = 1;
        }
     }
     if(flag){
        return pos;
     }
     else return 0;

}

int main(void)
{
     unsigned int a;
     unsigned int b;
     unsigned int k;
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
     if((scanf("%d", &k) != 1)|| (k < 1)) {
        printf("not korr k\n");
        return -1;
     }

     findConfig(a, b, k);

     config =  findConfig(a, b, k);

     if(config == 0){
        printf("not found");
     }
     else printf("%d", config);

     return 0;
}
