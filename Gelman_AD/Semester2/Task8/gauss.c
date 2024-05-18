#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "gauss.h"

/*	���������: **matr - ��������� �� ������� ���������� �� �������: � ��� �������� ������� n*2n, ��� � �������� ������� ������
 *                                                                                                   ��������� ��������� ������� n
 *          n - ������� �������
 *         *err - ��������� �� ��� ������.
 * ������� ���� �������� ������� ���������� ����� ������� ������� ������ � ������������ ����
 * ����� �������� (�������� �������). ���������� � ������ ����� ������� - ���������.
 */

// define N 3 ����������� �������

void swapRows(double matrix[N][N + 1], int row1, int row2) {
    // ������� ��� ������ ���� ����� �������
    for (int i = 0; i < N + 1; i++) {
        double temp = matrix[row1][i];
        matrix[row1][i] = matrix[row2][i];
        matrix[row2][i] = temp;
    }
}

void printMatrix(double matrix[N][N + 1]) {
    // ������� ��� ������ �������
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N + 1; j++) {
            printf("%.2f\t", matrix[i][j]);
        }
        printf("\n");
    }
}

void gaussElimination(double matrix[N][N + 1]) {
    // ������ ������ ������ ������
    for (int i = 0; i < N; i++) {
        // ����� ������������� �������� � ������� i
        double maxEl = matrix[i][i];
        int maxRow = i;
        for (int k = i + 1; k < N; k++) {
            if (matrix[k][i] > maxEl) {
                maxEl = matrix[k][i];
                maxRow = k;
            }
        }

        // ������ ������� ������ � �������, ���������� ������������ �������
        swapRows(matrix, i, maxRow);

        // �������� � ������� ������� ���������
        double divEl = matrix[i][i];
        for (int k = i; k < N + 1; k++) {
            matrix[i][k] /= divEl;
        }

        // �������� �������� � ������� i ��� ������� ����������
        for (int k = i + 1; k < N; k++) {
            double mul = matrix[k][i];
            for (int j = i; j < N + 1; j++) {
                matrix[k][j] -= mul * matrix[i][j];
            }
        }
    }

    // �������� ������ ��� ���������� ������
    double x[N];
    for (int i = N - 1; i >= 0; i--) {
        x[i] = matrix[i][N];
        for (int j = i + 1; j < N; j++) {
            x[i] -= matrix[i][j] * x[j];
        }
    }

    // ������� �������
    printf("Solution:\n");
    for (int i = 0; i < N; i++) {
        printf("x%d = %.2f\n", i + 1, x[i]);
    }
}

int main() {
    double matrix[N][N + 1] = { {3, 2, -4, 3}, {2, 3, 3, 15}, {5, -3, 1, 14} };

    printf("Initial matrix:\n");
    printMatrix(matrix);

    gaussElimination(matrix);

    return 0;
}
/*
swap rows - ���� ����� �������
print Matrix - ������ �������
gauss elimination - ���������� ������ ���������� ������ ��� ������� ���
*/







int Inverse_matr(double** matr, int n, Error* err, double eps) {
    double dif, head_el;//������� �� ������� ����� ������ ������� �� ������, ������� ������� ������.
    int ch_zero = 0; //������� ������� ��������� � ��������� ������ ��� �������� ������� �� �������������.
    *err = NA_OK;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j != i) {
                if (fabs(matr[i][i]) < eps) {
                    continue;
                }
                dif = matr[j][i] / matr[i][i];
                for (int l = 0; l < (2 * n); l++) {
                    matr[j][l] -= (dif * matr[i][l]);
                }
            }
        }
    }

    for (int j = 0; j < n; j++) {
        if (fabs(matr[n - 1][j]) < eps) {
            ch_zero++;
        }
    }
    if (ch_zero == n) {
        for (int i = 0; i < n; i++) {
            free(matr[i]);
        }
        free(matr);
        *err = NA_SINGLE_MATR;
        return -1;
    }
    for (int i = 0; i < n; i++) {
        if (fabs(matr[i][i]) < eps) {
            continue;
        }
        head_el = matr[i][i];
        for (int j = 0; j < (2 * n); j++) {
            matr[i][j] /= head_el;
        }
    }
    return 0;
}