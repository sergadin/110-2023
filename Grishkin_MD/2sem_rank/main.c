#include "rank.h"

int main(void) {
    int n = 2, m = 3;
    float eps = 0.001;
    float matrix[MAX][MAX] = {{1, 2, 3}, {2, 4, 6}};
    int expected = 1;

    if (n < 1 || m < 1 || n > MAX || m > MAX) {
        printf("incorrect n or m, must be between 1 and %d\n", MAX);
        return -1;
    }

    int rank = solution(matrix, n, m);
    printf("rank of matrix: %d\n", rank);

    if (fabs(expected - rank) < eps) {
        printf("test passed\n");
    } else {
        printf("test not passed\n");
    }

    return 0;
}
