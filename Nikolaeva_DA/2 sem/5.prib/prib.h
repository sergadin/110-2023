#ifndef PRIB_H
#define PRIB_H

typedef struct {
    double x, y;
} point;

typedef enum {
    OK,                 // код выполнен без ошибок, посчитаны базовые точки
    ERR_INTER_POINTS,   // точки интерполяции совпали
} error;

double lagrange_polynomial(point* xy_points, int qv, double x);

void interpolate(point* xy_points, int qv, point* int_points, int qv_i, double* inter_y, error* err);

#endif // PRIB_H
