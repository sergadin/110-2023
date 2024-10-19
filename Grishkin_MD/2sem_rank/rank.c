#include "rank.h"

int solution(float matrix[MAX][MAX], int n, int m) {
    int rank = 0;
    int i, j, k;

    for (i = 0; i < n; i++) {
        for (j = i; j < n; j++) {
            if (matrix[j][i] != 0) {
                for (k = 0; k < m; k++) {
                    float temp = matrix[i][k];
                    matrix[i][k] = matrix[j][k];
                    matrix[j][k] = temp;
                }
                break;
            }
        }

        if (matrix[i][i] != 0) {
            rank++;
            for (j = i + 1; j < n; j++) {
                float factor = matrix[j][i] / matrix[i][i];
                for (k = i; k < m; k++) {
                    matrix[j][k] -= factor * matrix[i][k];
                }
            }
        }
    }

    return rank;
}




