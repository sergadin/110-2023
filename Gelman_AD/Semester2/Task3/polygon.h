#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* A set of functions from R to R */
typedef double (*RRFun)(double);

//Errors
typedef enum 
{
    OK, // No errors
    WRONG_ORDER, // b < a - the borders of the segment
    ITERATION_LIMIT_EXCEEDED, // Iteration limit exceeded
}Error;


/* Counting the value of the integrand sum with the polygon method
 * The segment [a; b] is divided into an even number of subsegments.
 * The area of the rectangle with one side [a; b] and another side [f(a); f(b)] is calculated
 * The sum of this areas is equal to the integrand
 * Conclusion:
 * If the program works without any errors, the error code OK and the integral's value are printed
 * If the order of the borders of the segment is wrong, the error code WRONG_ORDER is printed
 * If the Iteration limit exceeded, the error code ITERATION_LIMIT_EXCEEDED is printed
 */

double Integrate(RRFun f, double a, double b, double epsilon, Error *error_code);