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
double distance(struct Point p1, struct Point p0);
double maxDim(struct Point polygon[], int n);


double distance(struct Point p1, struct Point p0){
	double dx = p0.x - p1.x;
	double dy = p0.y - p1.y;
	return  sqrt(dx * dx + dy * dy);
}


double minDim(struct Point polygon[], int n) {
	// Находим координаты центра многоугольника
	double sumX = 0, sumY = 0;
	for (int i = 0; i < n; i++) {
		sumX += polygon[i].x;
		sumY += polygon[i].y;
	}
	double centerX = sumX / n;
	double centerY = sumY / n;
	double rast[n];
	for(int i = 0; i < n; i++){
		rast[i] = sqrt(pow(polygon[i].x - centerX, 2) + pow(polygon[i].y - centerY, 2));

	}
	double min_d = rast[0];
	for (int i = 1; i < n; i++) {
		if (rast[i] < min_d) {
			min_d = rast[i];
		}
	}

	return 2 * min_d;
}

//Функция находит самую левую и самую правую точки, для которых ищем расстояниие
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



