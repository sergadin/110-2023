#include "interpolation.h"

void write_points(FILE* out1, FILE* out2, point* p, int n, double* i_p, int m, double* res);

void write_points(FILE* out1, FILE* out2, point* p, int n, double* i_p, int m, double* res){
	for (int i = 0; i < n; i++){
		fprintf(out1, "%lf\t%lf\n", p[i].x, p[i].y);
	}
	for (int i = 0; i < m; i++){
		fprintf(out2, "%lf\t%lf\n", i_p[i], res[i]);
	}
}


int main(void) {
    double eps = 0.001;
    char filename1[32], filename2[32];
    FILE* out1;
    FILE* out2;

    sprintf(filename1, "out1.txt");
    sprintf(filename2, "out2.txt" );
    out1 = fopen(filename1, "w");
    out2 = fopen(filename2, "w");

    if (out1 == NULL || out2 == NULL) {
        perror("Error opening file");
        return -1;
    }

    point points[5] = {
        {1, 1},
        {2, 4},
        {3, 9},
        {4, 16},
        {5, 25},
    };

    double interp_points[4] = {0.5, 1.5 , 2.5 , 1.1};
    double interp_values[4];

    interpolate(points, 5 , interp_points, 4, interp_values);

    double expected_values[4] = {0.25, 2.25, 6.25, 1.21};

    for (int i = 0; i < 4; i++) {
        printf("The interpolated value at the point %f: %f\n", interp_points[i], interp_values[i]);

        if (fabs(interp_values[i] - expected_values[i]) < eps) {
            printf("The value match the expected value\n");
        } else {
            printf("The value does not match the expected value\n");
        }
    }
    write_points(out1, out2, points, 5, interp_points, 4, interp_values);

    return 0;
}
