#include "inverse_matrix.h"

int solution(float matrix[MAX][MAX], float inverse[MAX][MAX], int n) {
    float temp[MAX][MAX];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            inverse[i][j] = (i == j) ? 1 : 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            temp[i][j] = matrix[i][j];

    for (int i = 0; i < n; i++) {
        float pivot = temp[i][i];
        if (pivot == 0) {
            return -1;
        }

        for (int j = 0; j < n; j++) {
            temp[i][j] /= pivot;
            inverse[i][j] /= pivot;
        }

        for (int k = 0; k < n; k++) {
            if (k != i) {
                float factor = temp[k][i];
                for (int j = 0; j < n; j++) {
                    temp[k][j] -= factor * temp[i][j];
                    inverse[k][j] -= factor * inverse[i][j];
                }
            }
        }
    }
    return 0;
}


