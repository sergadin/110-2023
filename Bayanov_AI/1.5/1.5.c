
#include <stdio.h>
#include <math.h>
int Function(FILE*vvod, char c[1000], float X)
{
  float a;
  int t=0;
  float e=0.000001;
  vvod=fopen(c, "r");
  if(fscanf(vvod, "%f", &a)==EOF)
     t=-1;
         else
            {
                if(fabs(a-X)<e)
                    t++;
               while(!feof(vvod))
                       {
                         fscanf(vvod, "%f", &a);
                           if(fabs(a-X)<e)
                                    t++;
                       }

             }
       return(t);
}

 int main(void)
  {
   FILE*vvod;
   char nazvanie[1000];
   float X;
   
   printf("������� �������� ����� � �����, ������� ���� ������: ");
    scanf("%s", nazvanie);
      scanf("%f", &X);

   vvod=fopen(nazvanie, "r");
      if(vvod==NULL)
        {
         printf("�� ������� ������� ����");
         return -1;
         }
      fclose(vvod);
          if(Function(vvod, nazvanie, X)==0)
                 printf("���");
                   else
                      if(Function(vvod, nazvanie, X)==-1)
                         printf("���� ������");
                           else
                         printf("��");
     return 0;
   }