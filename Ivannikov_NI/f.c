#include <stdio.h>
#include <stdlib.h> 


int fun(const char *sf, float *D);


int fun(const char *sf, float *D)
{
    int x,n=0,sumx2=0,sumx1=0,err=0;
    FILE *f;
    f=fopen(sf,"r");
    if(f!=NULL)
    {
    if(fscanf(f,"%d",&x)!=1)
        err=-2;
    else
    {
        sumx2=sumx2+x*x;
        sumx1=sumx1+x;
        n=n+1;
        while (fscanf(f,"%d",&x)==1)
        {
        sumx2=sumx2+x*x;
        sumx1=sumx1+x;
        n=n+1;
        }   
        *D=(float)((sumx2*n-sumx1*sumx1))/(n*n);
    }
    fclose(f);
    }
    else 
        err=-1;
    return err;
}


int main(void)
{
    int err=0;
    float D;
    err=fun("txt.txt",&D);
    if(err==-1)
        printf("can't open file \n");
    if(err==-2)
        printf("not enough data in file\n");
    else
        printf("D = %f\n",D);
    return err;
}
