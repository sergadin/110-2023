#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "gauss.h"

/*	Параметры: **matr - указатель на матрицу указателей на массивы: в них записана матрица n*2n, где к исходной матрице справа
 *                                                                                                   приписана единичная порядка n
 *          n - порядок матрицы
 *         *err - указатель на код ошибки.
 * Функция ищет обратную матрицу приведения новой матрицы методом Гаусса к ступенчатому виду
 * левой половины (исходной матрицы). Полученная в правой части матрица - результат.
 */

// define N 3 Размерность матрицы

void swapRows(double matrix[N][N + 1], int row1, int row2) {
    // Функция для обмена двух строк матрицы
    for (int i = 0; i < N + 1; i++) {
        double temp = matrix[row1][i];
        matrix[row1][i] = matrix[row2][i];
        matrix[row2][i] = temp;
    }
}

void printMatrix(double matrix[N][N + 1]) {
    // Функция для печати матрицы
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N + 1; j++) {
            printf("%.2f\t", matrix[i][j]);
        }
        printf("\n");
    }
}

void gaussElimination(double matrix[N][N + 1]) {
    // Прямой проход метода Гаусса
    for (int i = 0; i < N; i++) {
        // Поиск максимального элемента в столбце i
        double maxEl = matrix[i][i];
        int maxRow = i;
        for (int k = i + 1; k < N; k++) {
            if (matrix[k][i] > maxEl) {
                maxEl = matrix[k][i];
                maxRow = k;
            }
        }

        // Меняем текущую строку с строкой, содержащей максимальный элемент
        swapRows(matrix, i, maxRow);

        // Приводим к единице главную диагональ
        double divEl = matrix[i][i];
        for (int k = i; k < N + 1; k++) {
            matrix[i][k] /= divEl;
        }

        // Обнуляем элементы в столбце i под главной диагональю
        for (int k = i + 1; k < N; k++) {
            double mul = matrix[k][i];
            for (int j = i; j < N + 1; j++) {
                matrix[k][j] -= mul * matrix[i][j];
            }
        }
    }

    // Обратный проход для вычисления корней
    double x[N];
    for (int i = N - 1; i >= 0; i--) {
        x[i] = matrix[i][N];
        for (int j = i + 1; j < N; j++) {
            x[i] -= matrix[i][j] * x[j];
        }
    }

    // Выводим решение
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
swap rows - мена строк матрицы
print Matrix - печать матрицы
gauss elimination - реализация метода исключения Гаусса для решения СЛУ
*/







int Inverse_matr(double** matr, int n, Error* err, double eps) {
    double dif, head_el;//частное от деления одной строки матрицы на другую, главный элемент строки.
    int ch_zero = 0; //счетчик нулевых элементов в последней строке для проверки матрицы на вырожденность.
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