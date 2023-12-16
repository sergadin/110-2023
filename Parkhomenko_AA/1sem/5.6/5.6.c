#include <stdio.h>

int isIntersect(int x1, int y1, int x2, int y2);
// Функция, проверяющая пересечение двух отрезков
int isIntersect(int x1, int y1, int x2, int y2) {
    
    // Если отрезки имеют общую точку или перекрываются, то возвращаем 1
    if ((x1 <= y1 && x2 >= y1) && (x2 >= y2 && x1 <= y2)) {
        return 1;
    }
    return 0;
}

int isCovered(int n, int intervals[][2], int a, int b);
// Функция, проверяющая покрытие объединения отрезков заданным отрезком
int isCovered(int n, int intervals[][2], int a, int b) {
    for (int i = 0; i < n; i++) {
        if (!isIntersect(intervals[i][0], intervals[i][1], a, b)) {
            return 0; // Если хотя бы один отрезок не пересекается с заданным, то возвращаем 0
        }
    }
    return 1; // Если все отрезки пересекаются с заданным, то возвращаем 1
}

int main(void) {
    int a;
    int b;
    int n; // Количество отрезков
    int intervals[n][2];
    printf("Введите количество отрезков: ");
    scanf("%d", &n);

    // Ввод отрезков
    for (int i = 0; i < n; i++) {
        printf("Введите начало и конец отрезка %d: ", i + 1);
        scanf("%d %d", &intervals[i][0], &intervals[i][1]);
    }

    // Заданный отрезок
    printf("Введите начало и конец заданного отрезка: ");
    scanf("%d %d", &a, &b);

    // Проверка покрытия
    if (isCovered(n, intervals, a, b)) {
        printf("Объединение отрезков покрывает заданный отрезок.\n");
    } else {
        printf("Объединение отрезков не покрывает заданный отрезок.\n");
    }

    return 0;
}
