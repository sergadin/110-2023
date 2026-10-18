#include "interpolation.h"

void interpolate(point* points, int num_points, double* interp_points, int num_interp, double* interp_values);

void interpolate(point* points, int num_points, double* interp_points, int num_interp, double* interp_values) {
    int i, j;
    for ( j = 0; j < num_interp; j++) {

        for (i = 1; i < num_points; ++i) {
            if (points[i].x >= interp_points[j])
                break;
        }

        double x_left = points[i - 1].x;
        double y_left = points[i - 1].y;
        double x_right = points[i].x;
        double y_right = points[i].y;
        double x_target = interp_points[j];

        double x_next, y_next;

        if (i < num_points - 1) {
            x_next = points[i + 1].x;
            y_next = points[i + 1].y;
        } else {
            x_next = points[i - 1].x;
            y_next = points[i - 1].y;
        }

        double coeff_L0 = ((x_target - x_right) * (x_target - x_next)) / ((x_left - x_right) * (x_left - x_next));
        double coeff_L1 = ((x_target - x_left) * (x_target - x_next)) / ((x_right - x_left) * (x_right - x_next));
        double coeff_L2 = ((x_target - x_left) * (x_target - x_right)) / ((x_next - x_left) * (x_next - x_right));

        double result = y_left * coeff_L0 + y_right * coeff_L1 + y_next * coeff_L2;

        interp_values[j] = result;
    }
}
