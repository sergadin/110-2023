#include <stdio.h>
#include <stdlib.h>

typedef struct {
	double left;
    double right;
} interval;

int isCovered(interval* segments , int numSegments, double a, double  b);
void sort(interval* segments, int numSegments);

int isCovered(interval* segments , int numSegments, double a, double b)
{
    int cur_a = a;
    for (int i = 0; i < numSegments; i++){
        if (segments[i].left > cur_a){
            return 0;
        }
        if (segments[i].right <= cur_a || segments[i].left >= b)
            continue;

        cur_a = segments[i].right;
        if (cur_a >= b){
            return 1;
        }
    }
    return 0;
}

void sort(interval* segments, int numSegments)
{
    int max_i;
    interval temp_segment;
    double max;

    for (int i = 0; i < numSegments; i++){
        max = segments[0].left;
        max_i = 0;
        for (int j = 0; j < numSegments - i; j++){
            if (segments[j].left > max){
                max_i = j;
                max = segments[j].left;
            }
        }
        temp_segment = segments[numSegments - i - 1];
        segments[numSegments - i - 1] = segments[max_i];
        segments[max_i] = temp_segment;
        }
}



int main(void)
{
    FILE *file;
    int numSegments, covered;
    double a, b;
    interval* segments;

    file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file\n");
        return 1;
    }

    if ((fscanf(file, "%d", &numSegments) != 1) || (numSegments < 1)) {
        printf("Invalid number of segments");
        fclose(file);
        return -1;
    }

    segments = malloc (numSegments * sizeof(interval));
    if (segments == NULL) {
        printf("Memory allocation error\n");
        fclose(file);
        return -1;
    }
    for (int i = 0; i < numSegments; i++){
        fscanf(file ,"%lf %lf", &segments[i].left, &segments[i].right);
        if(segments[i].left > segments[i].right){
            printf("not a interval in file\n");
            return -1;
        }
    }
    sort(segments, numSegments);

    printf("Enter a: ");
    if (scanf("%lf", &a) != 1) {
        printf("Invalid a");
        fclose(file);
        free(segments);
        return -1;
    }

    printf("Enter b: ");
    if (scanf("%lf", &b) != 1) {
        printf("Invalid b");
        fclose(file);
        free(segments);
        return -1;
    }

    if (a > b) {
        printf("a > b, error");
        fclose(file);
        free(segments);
        return -1;
    }
    isCovered(segments, numSegments, a, b);
    covered = isCovered(segments, numSegments, a, b);

   // for(int i = 0; i < numSegments; i++){
    //   printf("%lf %lf ", segments[i].left, segments[i].right);
    //}

    if (covered) {
        printf("The segment is covered\n");
    } else {
        printf("The segment is not covered\n");
    }

    free(segments);
    fclose(file);

    return 0;
}
