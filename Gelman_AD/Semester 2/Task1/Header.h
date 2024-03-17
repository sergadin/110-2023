#include <math.h>

/* A set of functions from R to R */
typedef double (*RRFun)(double);

/* Main errors*/
typedef enum
{
	NA_OK, /* Finishing coding without any mistakes */
}Error;


/*  Calculating f(x0), ..., f(xn-1):
	Parameters:
	f - real functiom (to the enter comes ONLY functions from R to R)
	x - argument
	ERROR - an error code for testing
	Function gets the y-es from the test function THINK_OF_THE_HEADING and checks wether the test was completed

 *	Подсчитывается значение функции f в точке х, после подсчитывается значение композиции функций f и g.
 *	Если значение композиции с учетом погрешности не удовлетворяет условию, пересчитывается новое значение для очередной композиции функций f.
 *	(f(x))->(f(f(x)))
 *	Вложение функции f в композицию функций f продолжается до тех пор, пока композиция g с композициями f с учетом погрешности не станет положительной.
 *	Если этого не произойдет за определенное число операций(10000), выдастся ошибка NA_LIMIT.
 *	Если функция успешно завершается, в код ошибки записывается NA_OK.
 *	Вывод:
 *	Как только нашелся у = (f...f(f(x))...) такой, что g(у)>0, возвращается код ошибки NA_OK и значение у.
 *	Если такой у не нашелся, а цикл закончил свою работу, возвращается код ошибки NA_LIMIT, а значение у приравнивается к 0. и не выводится на экран.
 */

double THINK_OF_THE_HEADING(RRFun f, double x, Error* ERROR);