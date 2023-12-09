// 5.11 Даны центры равномерно растущих кругов на плоскости. При столкновении друг с другом столкнувшиеся круги 
// прекращают свой рост. Найти радиусы кругов, когда процесс роста остановится полностью

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define EPS 0.005

typedef struct {
   double x;
   double y;
   double R;
} Circle;

int read_file(FILE *file_in, Circle **circles);
void radius_grow(Circle *circles, int kol_centre);


int read_file(FILE *file_in, Circle **circles) {
	Circle *arr;
	double elem, scan_el;
	int kol_el = 1;
	int kol_centre;
	
	if (fscanf(file_in, "%lf", &elem) != 1) {
		printf("file pust / ne tot tip u pervogo elementa\n");
		return -1;
	}
	
	while((scan_el = fscanf(file_in, "%lf", &elem)) != EOF) {
		if (scan_el != 1) { 
			printf("ne tot tip u elementov\n");
			return -1;
		}
		kol_el++;
	}
	
	if ((kol_el%2) != 0) {
		printf("error, kol_el nechet\n");
		return -1;
	}
	
	kol_centre = kol_el / 2;
	
	arr = (Circle *)malloc((kol_centre*2) * sizeof(Circle));
	
	if (arr == NULL) {
		printf("memory error\n");
		return -1;
	}
	
	rewind(file_in);
	
	for(int i = 0; i < kol_centre; i++) {
		fscanf(file_in, "%lf %lf", &arr[i].x, &arr[i].y);
		arr[i].R = 0;
		arr[i + kol_centre].R = -1;
	}
	
	*circles = arr;
	return kol_centre;
}


void radius_grow(Circle *circles, int kol_centre) {
	double r1, r2, sum_r, distance;
	double pnt1_x, pnt2_x, pnt1_y, pnt2_y;
	
	for(int i = 0; i < kol_centre; i++) {
		pnt1_x = circles[i].x;
		pnt1_y = circles[i].y;
		r1 = circles[i].R;
		for(int j = i + 1; j < kol_centre; j++) {
			pnt2_x = circles[j].x;
			pnt2_y = circles[j].y;
			r2 = circles[j].R;
			sum_r = r1 + r2;
			distance = sqrt(pow(pnt1_x - pnt2_x, 2) + pow(pnt1_y - pnt2_y, 2));
			if ((sum_r > distance) || (fabs(sum_r - distance) < (EPS/10.0))) {
				circles[i + kol_centre].R = r1;
				circles[j + kol_centre].R = r2;
			}
		}
	}
	
	for(int i = 0; i < kol_centre; i++) {
		if(circles[i + kol_centre].R < 0.0) {
			circles[i].R += EPS;
		}
	}
	
	for(int i = kol_centre; i < 2 * kol_centre; i++) {
		if(circles[i].R < 0.0) {
			radius_grow(circles, kol_centre);
		}
	}
}



int main(void) {
    FILE *file_in, *file_out;
    int kol_centre = 0;
    Circle *circles;
	
    file_in = fopen("input.txt", "r");
    if(file_in == NULL) {
		printf("error opening the file_in\n");
        return -1;
    }
	
	file_out = fopen("output.txt", "w");
	if(file_in == NULL) {
		printf("error opening the file_in\n");
		fclose(file_in);
        return -1;
    }
	
	kol_centre = read_file(file_in, &circles);
	
    if (kol_centre == -1) {
        printf("ne prochit file_in \n");
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

	radius_grow(circles, kol_centre);
	
	for(int i = 0; i < kol_centre; i++) {
		fprintf(file_out, "центр (%lf ; %lf) и R = %lf \n", circles[i].x, circles[i].y, circles[i + kol_centre].R);
		fprintf(file_out, "\n");
		fprintf(file_out, "\n");
	}
	
    fclose(file_in);
	fclose(file_out);
    free(circles);
    return 0;
}