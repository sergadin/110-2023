#include <stdio.h>
#include <stdlib.h>
#include <time.h>


double bubblesort(int *a, int n);
double quicksort(int *a, int first, int last);
double standard(int *a, int n);
int comp(const int *i, const int *j);
int randomise(int *a, int *b, int *c, int n);
int sorted(int *a, int n);
int main(void);

double bubblesort(int *a, int n) {
	int i, j, x;
	clock_t start, end;
	start = clock();
	
	for (i=n-1; i>0; i--) {
		for (j=0; j<i; j++) {
			if (a[j] > a[j+1]) {
				x = a[j];
				a[j] = a[j+1];
				a[j+1] = x;
			}
		}
	}
	
	end = clock();
	
	return (double)(end - start)/CLOCKS_PER_SEC;
}

double quicksort(int *a, int first, int last) {
	int i, j, x, middle;
	clock_t start, end;
	start = clock();
	
	if (first >= last) {
		return 0;
	}
	i = first;
	j = last;
	middle = last;
	while (i < j) {
		if (middle == i) {
			if (a[j] < a[middle]) {
				x = a[j];
				a[j] = a[middle];
				a[middle] = x;
				middle = j;
				i++;
			}
			else {
				j--;
			}
		}
		else {
			if (a[i] > a[middle]) {
				x = a[i];
				a[i] = a[middle];
				a[middle] = x;
				middle = i;
				j--;
			}
			else {
				i++;
			}
		}
		
	}
	quicksort(a, first, middle-1);
	quicksort(a, middle+1, last);
	
	end = clock();
	
	return (double)(end - start)/CLOCKS_PER_SEC;
}


double standard(int *a, int n) {
	clock_t start, end;
	start = clock();
	
	qsort(a, n, sizeof(int), (int(*) (const void *, const void *)) comp);
	
	end = clock();
	
	return (double)(end - start)/CLOCKS_PER_SEC;
}
int comp(const int *i, const int *j) {
    return *i - *j;
}

int randomise(int *a, int *b, int *c, int n) {
	int i;
	for (i=0; i<n; i++) {
		a[i] = rand() % 1000000000;
		b[i] = a[i];
		c[i] = a[i];
	}
	if (sorted(a, n)) {
		randomise(a, b, c, n);
	}
	return 0;
}

int sorted(int *a, int n) {
	int i;
	for (i=0; i<n-1; i++) {
		if (a[i] > a[i+1]) {
			return 0;
		}
	}
	return 1;
}

int main(void) {
	int n, i;
	//double t1;
	double t2, t3;
	int *a = NULL;
	int *b = NULL;
	int *c = NULL;
	scanf("%d", &n);
	
	a = (int *)malloc(n*1024*sizeof(int));
	b = (int *)malloc(n*1024*sizeof(int));
	c = (int *)malloc(n*1024*sizeof(int));
	
	for (i=0; i<11; i++) {
		randomise(a, b, c, n);
		
		//t1 = bubblesort(a, n);
		t2 = quicksort(b, 0, n-1);
		t3 = standard(c, n);
		
		//if (sorted(a, n)) {
		//	printf("Пузырьковая - %lf при длине %d\n", t1, n);
		//}
		//else {
		//	printf("Пузырьковая провалилась при длине %d\n", n);
		//}
		if (sorted(b, n)) {
			printf("Быстрая - %lf при длине %d\n", t2, n);
		}
		else {
			printf("Быстрая провалилась при длине %d\n", n);
		}
		if (sorted(c, n)) {
			printf("Стандартная - %lf при длине %d\n", t3, n);
		}
		else {
			printf("Стандартная провалилась при длине %d\n", n);
		}
		
		n = n*2;
	}
	
	free(a);
	free(b);
	free(c);
	
	return 0;
}
