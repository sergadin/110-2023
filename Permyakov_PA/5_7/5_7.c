#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
	double x;
	double y;
}point;

typedef struct
{
	point s1;
	point s2;
}edge;

double scalar_product(point v, point u);
point vector(point a, point b);
double volume_product(point v, point u);
double point_distance(point a, point b);
double edge_distance(edge u, edge v);
double polygon_distance(int length1, edge* polygon1, int length2, edge* polygon2);

point vector(point a, point b)
{
    point v;
    v.x = (b.x - a.x);
    v.y = (b.y - a.y);
    return v;
}

double scalar_product(point v, point u)
{
    return (v.x * u.x + v.y * u.y);
}

double volume_product(point v, point u)
{
    return fabs(v.x * u.y - v.y * u.x);
}

double point_distance(point a, point b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

double edge_distance(edge u, edge v)
{
    double* distances;
    double minimum;
    int counter = 0;
    distances = (double*)malloc((8)*sizeof(double));
    if (distances == NULL){
        printf("memory allocation error\n");
        return -1.0;
    }
    point a = u.s1;
    point b = u.s2;
    point c = v.s1;
    point d = v.s2;
    point ab = vector(a, b);
    point cd = vector(c, d);
    point ac = vector(a, c);
    point bd = vector(b, d);
    point ca = vector(c, a);
    point db = vector(d, b);
    point ad = vector(a, d);
    point bc = vector(b, c);
    point cb = vector(c, b);
    point da = vector(d, a);
    distances[0] = point_distance(a, b);
    distances[1] = point_distance(c, d);
    distances[2] = point_distance(a, c);
    distances[3] = point_distance(b, d);
    if (scalar_product(ac, cd) * scalar_product(ad, cd) < 0){
        distances[4] = (volume_product(ac, ad) / distances[1]);
        counter++;
    }
    else {
        distances[4] = 0;
    }
    if (scalar_product(bc, cd) * scalar_product(bd, cd) < 0){
        distances[5] = (volume_product(bc, bd) / distances[1]);
        counter++;
    }
    else {
        distances[5] = 0;
    }
    if (scalar_product(ca, ab) * scalar_product(cb, ab) < 0){
        distances[6] = (volume_product(ca, cb) / distances[0]);
        counter++;
    }
    else {
        distances[6] = 0;
    }
    if (scalar_product(da, ab) * scalar_product(db, ab) < 0){
        distances[7] = (volume_product(da, db) / distances[0]);
        counter++;
    }
    else {
        distances[7] = 0;
    }
    if (counter == 4){
        return 0;
    }
    else {
        for (int i = 0; i < 8; i++){
            if ((distances[i] != 0) && (distances[i] < minimum)){
                minimum = distances[i];
            }
        }
    }
    return minimum;
}

double polygon_distance(int length1, edge* polygon1, int length2, edge* polygon2)
{
    double min = -1;
    double d;
    for (int i = 0; i < length1; i++){
        for (int j = 0; j < length2; j++){
            d = edge_distance(polygon1[i], polygon2[j]);
            if ((d < min) || (min < 0)){
                min = d;
            }
        }
    }
    return min;
}

int main(int argc, char** argv){
    FILE* input;
    char* inputfilename;
    char* outputfilename;
    double res;
    int length1;
    int length2;
    edge* polygon1;
    edge* polygon2;
    if (argc != 2){
        printf("incorrect number of arguments. need one: input filename\n");
        return -1;
    }
    input = fopen(inputfilename, "r");
    if (input == NULL){
        printf("incorrect input file\n");
        fclose(input);
        return -2;
    }
    if ((!fscanf(input, "%d", &length1)) || (length1 < 1)){
        printf("incorrect number of the first polygon's vertexes\n");
        fclose(input);
        return -3;
    }
    if ((!fscanf(input, "%d", &length2)) || (length2 < 1)){
        printf("incorrect number of the second polygon's vertexes\n");
        fclose(input);
        return -4;
    }
    polygon1 = (edge*)malloc((length1) * sizeof(edge));
    polygon2 = (edge*)malloc((length2) * sizeof(edge));
    if ((polygon1 == NULL) || (polygon2 == NULL)){
        printf("memorry allocation error\n");
        fclose(input);
        free(polygon1);
        free(polygon2);
        return -5;
    }
    if (!fscanf(input, "%lf%lf", &polygon1[0].s1.x, &polygon1[0].s1.y)){
        printf("incorrect data - need real number points\n");
        fclose(input);
        free(polygon1);
        free(polygon2);
        return -6;
        }
    polygon1[length1 - 1].s2.x = polygon1[0].s1.x;
    polygon1[length1 - 1].s2.y = polygon1[0].s1.y;
    for (int i = 0; i < (length1 - 1); i++){
        if (!fscanf(input, "%lf%lf", &polygon1[i].s2.x, &polygon1[i].s2.y)){
            printf("incorrect data - need real number points\n");
            fclose(input);
            free(polygon1);
            free(polygon2);
            return -6;
        }
        polygon1[i + 1].s1.x = polygon1[i].s2.x;
        polygon1[i + 1].s1.y = polygon1[i].s2.y;
    }
    if (!fscanf(input, "%lf%lf", &polygon2[0].s1.x, &polygon2[0].s1.y)){
        printf("incorrect data - need real number points\n");
        fclose(input);
        free(polygon1);
        free(polygon2);
        return -6;
        }
    polygon2[length2 - 1].s2.x = polygon2[0].s1.x;
    polygon2[length2 - 1].s2.y = polygon2[0].s1.y;
    for (int i = 0; i < (length2 - 1); i++){
        if (!fscanf(input, "%lf%lf", &polygon2[i].s2.x, &polygon2[i].s2.y)){
            printf("incorrect data - need real number points\n");
            fclose(input);
            free(polygon1);
            free(polygon2);
            return -6;
        }
        polygon2[i + 1].s1.x = polygon2[i].s2.x;
        polygon2[i + 1].s1.y = polygon2[i].s2.y;
    }
    res = polygon_distance(length1, polygon1, length2, polygon2);
    if (res != 0){
        printf("%lf\n", res);
    }
    else {
        printf("0, polygons are intersepting\n");
    }
    return 0;
}