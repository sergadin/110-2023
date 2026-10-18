#include "inverse_matrix.h"

void printMatrix(float matrix[MAX][MAX], int n);

void printMatrix(float matrix[MAX][MAX], int n) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
}
int main(void) {
    int n = 2;
    float eps = 0.001;
    float matrix[MAX][MAX] = {{1, 2}, {2, 1}};
    float inverse[MAX][MAX];
    float expected[MAX][MAX] = {{-0.3333, 0.6666}, {0.6666, -0.3333}};

    if (solution(matrix, inverse, n) == 0) {
        printf("Inverse matrix:\n");
        printMatrix(inverse, n);
    } else {
        printf("The matrix has no inverse.\n");
        return -1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fabs(expected[i][j] - inverse[i][j]) < eps) {
                printf("Test passed for element (%d, %d)\n", i, j);
            } else {
                printf("Test not passed for element (%d, %d)\n", i, j);
            }
        }
    }

    return 0;
}

