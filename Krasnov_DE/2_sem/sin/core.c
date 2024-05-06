#include "sin.h"


double my_sin(double x, double eps){
    double sin = x;
	double next_term = x;
	int power = 1;
	int sign = -1;

	while(fabs(next_term) > eps){
        next_term = sign * fabs(next_term) * x * x / ( (power+1) * (power+2) );
        sin = sin+next_term;
        sign = sign * (-1);
        power = power + 2;
	}


	return sin;

}
/*the function receives an input angle (x), the sine of which we must calculate using the Taylor series and the measurement accuracy (eps).
First, the first element of the Taylor series is considered, which is equal to x itself.Next, the cycle counting sin is started using the Taylor series
until the new element of the series is <=eps.
