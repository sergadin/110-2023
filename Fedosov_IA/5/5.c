#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
    double x, y;
} Point;

// Глобальная переменная для опорной точки при сортировке
Point pivot;

// Функция для определения ориентации троек точек (p, q, r)
int orientation(Point p, Point q, Point r)
{
    double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0)
    {
        return 0; // коллинеарные точки
    }
    else if (val > 0)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

// Функция для сравнения точек по полярному углу относительно pivot
int compare(const void *vp1, const void *vp2)
{
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;
    int o = orientation(pivot, *p1, *p2);

    if (o == 0)
    {
        if (p1->x + p1->y >= p2->x + p2->y)
        {
            return -1;
        }
        else
        {
            return 1;
        }
        // сортировка по сумме координат в случае коллинеарности
    }

    if (o == -1)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

// Функция для построения выпуклой оболочки методом Грэхема
void convexHull(Point points[], int n)
{
    if (n < 3)
        return; // выпуклая оболочка не может содержать менее трех точек

    // Найти точку с наименьшей y-координатой (и самой левой в случае равенства y)
    double ymin = points[0].y;
    int min = 0;
    for (int i = 1; i < n; i++)
    {
        double y = points[i].y;
        if ((y < ymin) || (ymin == y && points[i].x < points[min].x))
            ymin = points[i].y, min = i;
    }

    // Поменять местами points[0] и points[min]
    Point temp = points[0];
    points[0] = points[min];
    points[min] = temp;

    // Инициализация опорной точки для сортировки по полярному углу
    pivot = points[0];

    // Сортировка по полярному углу относительно pivot
    qsort(&points[1], n - 1, sizeof(Point), compare);

    // Инициализация стека для построения выпуклой оболочки
    Point hull[n];
    int hullSize = 0;

    // Добавить первые три точки в стек
    hull[hullSize++] = points[0];
    hull[hullSize++] = points[1];
    hull[hullSize++] = points[2];

    // Обработка остальных точек
    for (int i = 3; i < n; i++)
    {
        // Удалять точки из стека, пока последние две точки и текущая точка образуют "правый поворот"
        while (hullSize > 1 && orientation(hull[hullSize - 2], hull[hullSize - 1], points[i]) != -1)
            hullSize--;

        // Добавить текущую точку в стек
        hull[hullSize++] = points[i];
    }

    // Вывести точки выпуклой оболочки
    printf("Выпуклая оболочка:\n");
    for (int i = 0; i < hullSize; i++)
        printf("(%lf, %lf)\n", hull[i].x, hull[i].y);
}

int main()
{
    FILE *fin = fopen("input.txt", "r");
    if (fin == NULL)
    {
        printf("Не удалось открыть файл.\n");
        return 1;
    }

    int totalPoints;
    fscanf(fin, "%d", &totalPoints);

    int capacity = totalPoints;
    int size = 0;

    // Выделение памяти для массива точек
    Point *points = (Point *)malloc(capacity * sizeof(Point));

    if (points == NULL)
    {
        printf("Ошибка выделения памяти.\n");
        fclose(fin);
        return 1;
    }

    // Считывание точек из файла
    while (fscanf(fin, "%lf %lf", &points[size].x, &points[size].y) == 2)
    {
        size++;

        // Проверка на переполнение массива точек
        if (size == capacity)
        {
            capacity *= 2;
            points = (Point *)realloc(points, capacity * sizeof(Point));

            if (points == NULL)
            {
                printf("Ошибка перевыделения памяти.\n");
                fclose(fin);
                return 1;
            }
        }
    }

    fclose(fin);

    // Построение выпуклой оболочки
    convexHull(points, size);

    free(points);

    return 0;
}
