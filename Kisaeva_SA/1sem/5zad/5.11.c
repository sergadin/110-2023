// 5.11 Даны центры равномерно растущих кругов на плоскости. При столкновении друг с другом столкнувшиеся круги 
// прекращают свой рост. Найти радиусы кругов, когда процесс роста остановится полностью

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define ERROR -1

typedef struct {
   double x;
   double y;
   double R;
   int grow;
} Circle;

int read_file(FILE *file_in, Circle **circles);
void find_radius(Circle *circles, int kol_centre);


int read_file(FILE *file_in, Circle **circles) {
	Circle *arr;
	double elem, scan_el;
	int kol_el = 1;
	int kol_centre;
	
	if (fscanf(file_in, "%lf", &elem) != 1) {
		printf("file pust / ne tot tip u pervogo elementa\n");
		return ERROR;
	}
	
	while((scan_el = fscanf(file_in, "%lf", &elem)) != EOF) {
		if (scan_el != 1) { 
			printf("ne tot tip u elementov\n");
			return ERROR;
		}
		kol_el++;
	}
	
	if ((kol_el % 2) != 0) {
		printf("error, kol_el nechet\n");
		return ERROR;
	}
	
	kol_centre = kol_el / 2;
	
	arr = (Circle *)malloc((kol_centre) * sizeof(Circle));
	
	if (arr == NULL) {
		printf("memory error\n");
		return ERROR;
	}
	
	rewind(file_in);
	
	for(int i = 0; i < kol_centre; i++) {
		fscanf(file_in, "%lf %lf", &arr[i].x, &arr[i].y);
		arr[i].R = 0;
		arr[i].grow = 1;
	}
	
	*circles = arr;
	return kol_centre;
}


void find_radius(Circle *circles, int kol_centre) {
	int index_i = -1, index_j = -1;
	double distance = 0, radius = 0;
	double min_radius = -1;
	
	for(int i = 0; i < kol_centre; i++) {
		if (circles[i].grow == 1) { // если ещё не нашли конечный радиус у конкретной окружности
			for(int j = 0; j < kol_centre; j++) {
				if (i != j) {
					distance = sqrt(pow(circles[i].x - circles[j].x, 2) + pow(circles[i].y - circles[j].y, 2)); // расстояние между центрами
					if (circles[j].grow == 0) { // если сравниваем с окр-тью, которая нашла свой конечный радиус
						radius = distance - circles[j].R; 
					}
					else {
						radius = distance / 2.0;
					}
					if (min_radius < 0) {
						min_radius = radius;
						index_i = i;
					} 
					else if (radius < min_radius) {
						min_radius = radius;
						index_i = i;
						index_j = j;
					}
				}
			}
		}
	}
	
	if (index_i != -1) {
		circles[index_i].R = min_radius;
		circles[index_i].grow = 0;
		if ((index_j != -1) && (circles[index_j].grow == 1)) {
			circles[index_j].R = min_radius;
			circles[index_j].grow = 0; 
		}
	}
}


int main(void) {
    FILE *file_in, *file_out;
    int kol_centre = 0;
    Circle *circles;
	
    file_in = fopen("input.txt", "r");
    if (file_in == NULL) {
		printf("error opening the file_in\n");
        return -1;
    }
	
	file_out = fopen("output.txt", "w");
	if (file_out == NULL) {
		printf("error opening the file_out\n");
		fclose(file_in);
        return -1;
    }
	
	kol_centre = read_file(file_in, &circles);
	
    if (kol_centre == ERROR) {
        printf("error in file_in \n");
		fclose(file_in);
		fclose(file_out);
		free(circles);
        return -1;
    }
	
    if (kol_centre == 1) {
        printf("zadan tol'ko odin krug \n");
		fclose(file_in);
		fclose(file_out);
		free(circles);
        return 0;
    }
	
	for(int i = 0; i < kol_centre; i++) {
		find_radius(circles, kol_centre);
	}
	
	for(int i = 0; i < kol_centre; i++) {
		fprintf(file_out, "центр (%lf ; %lf) и R = %lf \n", circles[i].x, circles[i].y, circles[i].R);
		fprintf(file_out, "\n");
	}
	
	printf("rezultat napechatan\n");
	
    fclose(file_in);
	fclose(file_out);
    free(circles);
    return 0;
}