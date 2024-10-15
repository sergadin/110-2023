#include "interpolation.h"


int main(void) {
    double eps = 0.001;

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

    return 0;
}
