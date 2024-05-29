#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct info
{
	int condition;
	double expected;
	double real;
};

double function(double x);

struct info* test(double f(double), int n, double* args, double* vals, double eps);

int main(void){
	
	int n;
	scanf("%d", &n);
	double* args = malloc(sizeof(double)*n);
	double* vals = malloc(sizeof(double)*n);
	
	for(int i = 0;i < n; i++) {
		scanf("%lf %lf", &args[i], &vals[i]);
	}
	
	
	struct info* ans = test(&function, n, args, vals, 0.0000001);
	
	for (int i = 0; i < n; i++)
	{	
		if(ans[i].condition == 1) {
			printf("answer is correct\n");
			printf("%lf\n", ans[i].real);
		}
		else {
			printf("answer is incorret\n");
			printf("%lf\n", ans[i].real);
		}
	}
	
	free(ans);
	free(vals);
	free(args);
	
	return 0;	
}

