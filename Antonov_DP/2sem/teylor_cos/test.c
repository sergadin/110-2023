#include <stdio.h>
#include <math.h>
#include "teylor_cos.h"

typedef struct testcase {
	double x;
	double eps;
	double answer;
} testcase;

int main(void)
{
	struct testcase tests[] = {
		{M_PI / 4, 0.00001, cos(M_PI / 4)},
		{5 * (M_PI / 3) + 1000000 * M_PI, 0.00001, cos(M_PI / 3)},
		{M_PI / 2, 0.00001, cos(M_PI / 2)}
	};
	double answ;
	for (int i = 0; i < 3; i++){
		answ = teylor_cos(tests[i].x, tests[i].eps);
		if ((fabs(answ - tests[i].answer) < tests[i].eps))
		{
			printf("test correct \n");
		}
		printf("%lf %lf \n", answ, tests[i].answer);
	}
	return 0;
}
