#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct{
	double x;
	double y;
}Point;

double minDim(Point *polygon, int n);
double maxDim(Point *polygon, int n);
double distance(Point p1, Point p0);


double distance(Point p1, Point p0){
	double dx = p0.x - p1.x;
	double dy = p0.y - p1.y;
	return  sqrt(dx * dx + dy * dy);
}


double minDim(Point *polygon, int n) {
	// Находим координаты центра многоугольника
	double sumX = 0, sumY = 0;
	for (int i = 0; i < n; i++) {
		sumX += polygon[i].x;
		sumY += polygon[i].y;
	}
	double x0 = sumX / n;
	double y0 = sumY / n;
	double rast[n];
	double xa = polygon[0].x,xb,ya = polygon[0].y,yb,xh,yh, sin,cos;
	for(int i = 1; i < n+1; i++){
		xb = polygon[i%n].x;
		yb = polygon[i%n].y;
		cos = ((xa - x0)*(xb - x0) + (ya - y0)*(yb - y0))/(sqrt((xa - x0)*(xa - x0) + (ya - y0)*(ya - y0))*sqrt((xb - x0)*(xb - x0) + (yb - y0)*(yb - y0)));
		sin = sqrt(1 - cos*cos);
		rast[i-1] = (sqrt((xa-x0)*(xa - x0) + (ya - y0)*(ya - y0))*sqrt((xb - x0)*(xb - x0)+(yb - y0)*(yb - y0))*sin)/(sqrt((xa-xb)*(xa-xb)+(ya-yb)*(ya-yb)));
		xa = xb;
		ya = yb;
	}
	double min_d = rast[0];
	for (int i = 0; i < n; i++) {
		if (rast[i] < min_d) {
			min_d = rast[i];
		}
	}

	return 2 * min_d;
}

//Функция находит самую левую и самую правую точки, для которых ищем расстояниие
double maxDim(Point *polygon, int n){
	double max_d = 0;
	for(int i = 0; i < n; i++){
		for(int j = i + 1; j < n; j++){
			Point p1 = polygon[i];
			Point p2 = polygon[j];
			double next_rust = 0;
			for(int k = 0; k < n; k++){
				if((k != i) && (k != j)){
					Point p = polygon[k];
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
	Point * polygon = NULL;
	
	printf("Введите количество точек: ");
	if(scanf("%d", &n)!= 1){
		printf("Ошибка считывания\n");
		return 0;

	}
	if(n<0){
		printf("Отрицательное значение");
		return 0;
	}
	polygon = (Point *)malloc(n * sizeof(Point));
	if (polygon == NULL){
		printf("memory err\n");
	}
	printf("Введите координаты точек:\n");
	for(int i = 0; i < n; i++){
		printf("Точка %d\n", i + 1);
		if(scanf("%lf %lf", &polygon[i].x, &polygon[i].y)!= 2){
			printf("Некорректно введены координаты");
			return 0;
		}
	}
	minD = minDim(polygon, n);
	maxD = maxDim(polygon, n);
	printf("Минимальный диаметр: %lf\n", minD);
	printf("Максимальный диаметр: %lf\n", maxD);
	return 0;
}
