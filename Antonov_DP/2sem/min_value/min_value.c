#include <stdio.h>
#include <math.h>
#include "integration.h"

static int compRR(double a, double b, double eps);

static int compRR(double a, double b, double eps)
{
        if((a > 100000) || (b > 100000))
        {
                if (fabs(a - b) < eps * (a + b)) { return 0; }
                if (a > b) { return 1; }
                return -1;
        }
        if (fabs(a - b) < eps) { return 0; }
        if (a > b) { return 1; }
        return -1;
}

static double min_value_parab(double x1, double y1, double x2, double y2, double x3, double y3, double eps);

static double min_value_parab(double x1, double y1, double x2, double y2, double x3, double y3, double eps)
{
	if (compRR(y1, y3, eps) != 0) { return y2; }

}


double min_value(RRFun f, double a, double b, double eps, ERR *err)
{
}
