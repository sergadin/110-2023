// Множество точек определяет выпуклый многоугольник. Найти его максимальный и минимальный диаметры.

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>


struct Point{
        double x;
        double y;
};

double distance(struct Point p1, struct Point p2);
double minDim(struct Point polygon[], int n);
double maxDim(struct Point polygon[], int n);

 /* unsigned int coren(unsigned int a)
{
   unsigned int  x;
   x = (a/0x3f + 0x3f)>>1;
   x = (a/x + x)>>1;
   x = (a/x + x)>>1;
   return(x); 
}
unsigned int isqrt(unsigned int x)
{
   unsigned int m, y, b;
   m = 0x4000;
   y = 0;
   while (m != 0){
      b = y | m;
      y = y >> 1;
      if (x >= b) {
         x = x - b;
         y = y | m;
      }
      m = m >> 2;
   }
   return y;
}*/

//Функция считает расстояние между 2 точками
double distance(struct Point p1, struct Point p2){
	double dx = p2.x - p1.x;
	double dy = p2.y - p1.y;
	return  sqrt(dx * dx + dy * dy);
}
//Функция находит минимальный диаметр(Находим расстояние между 2 точками, находя самую удалённую


double minDim(struct Point polygon[], int n){
	struct Point A = polygon[0];
	for(int i = 1; i < n; i++){
		if(polygon[i].x < A.x){
			A = polygon[i];
		}
	}
	double min_d;
	min_d = 0;
	struct Point B;
	for(int i = 0; i < n; i++){
		double rast1 = distance(A, polygon[i]);
		if(rast1 > min_d){
			min_d = rast1;
			B = polygon[i];
		}
		
	}
	return min_d;

}
//Функция находит самую левую и самую правую точки, для которых ищет расстояниие
double maxDim(struct Point polygon[], int n){
double max_d = 0;
	for(int i = 0; i < n; i++){
		for(int j = i + 1; j < n; j++){
			struct Point p1 = polygon[i];
			struct Point p2 = polygon[j];
			double next_rust = 0;
			for(int k = 0; k < n; k++){
				if((k != i) && (k != j)){
					struct Point p = polygon[k];
					double storona = (p.x - p1.x) * (p2.y - p1.y) - (p.y - p1.y) * (p2.x - p1.x);
					if(storona < 0){
						double rast2 = distance(p1, p);
						if(rast2 > next_rust){
							next_rust = rast2;
						}
					
					}
				}
			}
			if(next_rust > max_d)
				max_d = next_rust;
			
		}
	}
	return max_d;
}

int main(void){
	int n;
	double minD;
	double maxD;
	printf("Введите количество точек: ");
	scanf("%d", &n);
	struct Point polygon[n];
	printf("Введите координаты точек: \n");
	for(int i = 0; i < n; i++){
		printf("Точка %d", i + 1);
		scanf("%lf %lf", &polygon[i].x, &polygon[i].y);
	}
	minD = minDim(polygon, n);
	maxD = maxDim(polygon, n);
	printf("Минимальный диаметр: %lf\n", minD);
	printf("Максимальный диаметр: %lf\n", maxD);
	return 0;
}



