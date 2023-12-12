#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
	double x, y;
} Point;


void fillArray(Point** p, FILE* input, int n);
void findStraight(double** a, double** b, double** c, Point* p, int n);
void findNewStraight(double** c, Point* p, int n, double h);
void getNewPolygon(double** a, double** b, double** c, Point** p1, Point** p2, int n, int h);


void fillArray(Point** p, FILE* input, int n) {

	*p = (Point*)malloc(n * sizeof(Point));
	if (*p == NULL) {
		printf("memory allocation error");
		return;
	}

	for (int i = 0; i < n; i++)
		fscanf(input, "%lf %lf", &(*p)[i].x, &(*p)[i].y);
}


void findStraight(double** a, double** b, double** c, Point* p, int n) {

	*a = (double*)malloc(n * sizeof(double));
	*c = (double*)malloc(n * sizeof(double));
	*b = (double*)malloc(n * sizeof(double));

	if (*a == NULL || *b == NULL || *c == NULL) {
		printf("memory allocation error");
		return;
	}


	for (int i = 0; i < n - 1; i++) {
		(*a)[i] = p[i + 1].y - p[i].y;
		(*b)[i] = p[i].x - p[i + 1].x;
		(*c)[i] = ((p[i + 1].x) * (p[i].y)) - ((p[i + 1].y) * (p[i].x));
	}
	(*a)[n - 1] = p[0].y - p[n-1].y;
	(*b)[n - 1] = p[n - 1].x - p[0].x;
	(*c)[n - 1] = p[0].x * p[n - 1].y - p[0].y * p[n-1].x;

}


void findNewStraight(double** c, Point* p, int n, double h) {

	for (int i = 0; i < n - 1; i++) {
		(*c)[i] += h * sqrt(pow(p[i + 1].x - p[i].x, 2) + pow(p[i + 1].y - p[i].y, 2));
	}
	(*c)[n - 1] += h * sqrt(pow(p[0].x - p[n - 1].x, 2) + pow(p[0].y - p[n - 1].y, 2));

}


void getNewPolygon(double** a, double** b, double** c, Point** p1, Point** p2, int n, int h) {
	findStraight(&*a, &*b, &*c, *p1, n);

	// for (int i = 0; i < n; i++) {
	// 	printf("straight:  %.0lfx + %.0lfy + %.0lf\n", (*a)[i], (*b)[i], (*c)[i]);
	// }

	findNewStraight(&*c, *p1, n, h);

	//for (int i = 0; i < n; i++) {
	//	printf("new straight:  %.2lfx + %.2lfy + %.2lf\n", (*a)[i], (*b)[i], (*c)[i]);
	//}

	*p2 = (Point*)malloc(n * sizeof(Point));

	for (int i = 0; i < n - 1; i++) {
		(*p2)[i].x = ((*c)[i] * (*b)[i + 1] - (*c)[i + 1] * (*b)[i]) / ((*b)[i] * (*a)[i + 1] - (*b)[i + 1] * (*a)[i]);
	}
	(*p2)[n - 1].x = ((*c)[n - 1] * (*b)[0] - (*c)[0] * (*b)[n - 1]) / ((*b)[n - 1] * (*a)[0] - (*b)[0] * (*a)[n - 1]);

	for (int i = 0; i < n; i++) {
		(*p2)[i].y = ((-1) * ((*a)[i] * (*p2)[i].x + (*c)[i])) / (*b)[i];
	}
}


int main(void) {
	int n;
	double h;
	double* A = NULL, * B = NULL, * C = NULL;
	Point* polygon_1 = NULL, * polygon_2 = NULL;
	FILE* input, * output;

	if ((input = fopen("input.txt", "r")) == NULL) {
		printf("failed to open input file");
		return -1;
	}
	if ((output = fopen("output.txt", "w")) == NULL) {
		printf("failed to open output file");
		return -2;
	}

	fscanf(input, "%d", &n);

	fillArray(&polygon_1, input, n);

	printf("enter h: ");
	scanf("%lf", &h);

	getNewPolygon(&A, &B, &C, &polygon_1, &polygon_2, n, h);

	for (int i = 0; i < n; i++) {
		fprintf(output, "%.2lf %.2lf\n", polygon_2[i].x, polygon_2[i].y);
	}

	return 0;
}
