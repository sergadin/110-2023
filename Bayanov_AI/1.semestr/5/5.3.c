
#include <stdio.h>
#include<stdlib.h>
#include <math.h>

double tg(double * pointx, double *point_y, int N);

int Sign_line(double * point_x, double *point_y, int N1, int N2);

int Checking_for_the_end_point(double *point_x, double *point_y, int N, int quantity);

int Replacing_coordinates(double *point_x, double *point_y, int quantity, double X, double Y);

int Checking_for_an_internal_point(double *point_x, double *point_y, int quantity, double X, double Y);

double Viewing_angle(double *point_x, double *point_y, int quantity);

int Replacing_coordinates(double *point_x, double *point_y, int quantity, double X, double Y)
{
    for(int i=0; i<quantity; i++)
    point_x[i] = point_x[i] - X;
    for(int i=0; i<quantity; i++)
    point_y[i] = point_y[i] - Y;
}

int Sign_line(double * point_x, double *point_y, int N1, int N2)
{
    if((point_y[N1]*point_x[N2]-point_x[N1]*point_y[N2]) > 0)
      return 1;
    if((point_y[N1]*point_x[N2]-point_x[N1]*point_y[N2]) < 0)
      return -1;
    return 0;
}

int Checking_for_the_end_point(double *point_x, double *point_y, int N, int quantity)
{
    int sign; 
    for(int i=0; i < quantity;i++)
    {
    if(Sign_line(point_x, point_y, N, i) == 0)
    continue;
    sign = Sign_line(point_x, point_y, N, i);
    break;
    }
    for(int i=0; i < N; i++)
     {
      if( Sign_line(point_x, point_y, N, i) == 0)
         continue;
      if(sign != Sign_line(point_x, point_y, N, i))
        return -1;
     }
    for(int i=N+1; i < quantity; i++)
      {
      if( Sign_line(point_x, point_y, N, i) == 0)
         continue;
      if(sign != Sign_line(point_x, point_y, N, i))
        return -1;
     }
    return 1;
}

int Checking_for_an_internal_point(double *point_x, double *point_y, int quantity, double X, double Y)
{
   int counter = 0;
   Replacing_coordinates(point_x, point_y, quantity, X, Y);
    for(int i=0; i < quantity; i++)
     if(Checking_for_the_end_point(point_x, point_y, i , quantity) == 1)
      counter ++;
  if(counter == 0)
  return 1;
  
  return -1;
}

double Viewing_angle(double *point_x, double *point_y, int quantity)
{
    double tg1 = 0;
    double tg2 = 0;
    double artg1 = 0;
    double artg2 = 0;
    int N = 0;
    for(int i=0; i < quantity; i++)
     if(Checking_for_the_end_point(point_x, point_y, i , quantity) == 1)
     {
      tg1 = point_y[i]/point_x[i];
      tg2 = tg1;
      N = i;
      break;
     }
     
     for(int i=0; i < quantity; i++)
     if(Checking_for_the_end_point(point_x, point_y, i , quantity) == 1)
     {
      if(Sign_line(point_x, point_y, N, i) == 0)
      {
        if(point_x[i]*point_x[N] < 0)
        return 180;
        if(point_y[i]*point_y[N] < 0)
        return 180;
      continue;
      }
      tg2 = point_y[i]/point_x[i];
      break;
     }
     artg1 = atan(tg1)*180/3.14159;
     artg2 = atan(tg2)*180/3.14159;
     if(artg1*artg2 < 0)
     return(180-fabs(artg1-artg2));
     
     return(fabs(artg1-artg2));
     
}

int main(void)
{
    int quantity = 0;
    double *point_x = NULL;
    double *point_y = NULL;
    FILE *input;
    double X = 0;
    double Y = 0;
    double angle = 0;
    printf("Enter X: ");
    scanf("%lf", &X);
    printf("Enter Y: ");
     scanf("%lf", &Y);
    input = fopen("input.txt", "r");
    fscanf(input, "%d", &quantity);
    point_x = (double *) malloc ((quantity)* sizeof(double));
    point_y = (double *) malloc ((quantity)* sizeof(double));
    
    for(int i=0; i < 2*quantity; i++)
    if(i%2 == 0)
     fscanf(input, "%lf", &point_x[i/2]);
     else
     fscanf(input, "%lf", &point_y[i/2]);
     fclose(input);
     
     if(Checking_for_an_internal_point(point_x, point_y, quantity, X, Y) == 1)
     {
      printf("The point is inside");
      return 0;
     }
   angle = Viewing_angle(point_x, point_y, quantity);
    printf("%lf ", angle);
    free(point_x);
    free(point_y);
    return 0;
}
