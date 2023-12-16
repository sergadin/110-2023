// Множество точек определяет выпуклый многоугольник. Найти его максимальный и минимальный диаметры.

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>


struct Point{
        double x;
        double y;
};
double minDim(struct Point polygon[], int n);
double distance(struct Point p1, struct Point p2);
double maxDim(struct Point polygon[], int n);

//Функция считает расстояние между 2 точками
double distance(struct Point p1, struct Point p2){
	double dx = p2.x - p1.x;
	double dy = p2.y - p1.y;
	return  sqrt(dx * dx + dy * dy);
}
//Функция находит минимальный диаметр

double minDim(struct Point polygon[], int n) {
    double min_d = INFINITY;
    for(int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        double rast1 = distance(polygon[i], polygon[j]);
        if(rast1 < min_d)
            min_d = rast1;
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
	if(scanf("%d", &n)!=1){
		printf("Ошибка считывания\n");
		return 0;
		
		}
	if(n<0){
		printf("Отрицательное значение");
		return 0;
	}
	struct Point polygon[n];
	printf("Введите координаты точек: \n");
	for(int i = 0; i < n; i++){
		printf("Точка %d", i + 1);
		if(scanf("%lf %lf", &polygon[i].x, &polygon[i].y)!=2){
			printf("Введено неправильне количество координат");
			return 0;
		}
	}
	minD = minDim(polygon, n);
	maxD = maxDim(polygon, n);
	printf("Минимальный диаметр: %lf\n", minD);
	printf("Максимальный диаметр: %lf\n", maxD);
	return 0;
}



