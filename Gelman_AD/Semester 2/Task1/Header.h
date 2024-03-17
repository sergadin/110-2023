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

 *	�������������� �������� ������� f � ����� �, ����� �������������� �������� ���������� ������� f � g.
 *	���� �������� ���������� � ������ ����������� �� ������������� �������, ��������������� ����� �������� ��� ��������� ���������� ������� f.
 *	(f(x))->(f(f(x)))
 *	�������� ������� f � ���������� ������� f ������������ �� ��� ���, ���� ���������� g � ������������ f � ������ ����������� �� ������ �������������.
 *	���� ����� �� ���������� �� ������������ ����� ��������(10000), �������� ������ NA_LIMIT.
 *	���� ������� ������� �����������, � ��� ������ ������������ NA_OK.
 *	�����:
 *	��� ������ ������� � = (f...f(f(x))...) �����, ��� g(�)>0, ������������ ��� ������ NA_OK � �������� �.
 *	���� ����� � �� �������, � ���� �������� ���� ������, ������������ ��� ������ NA_LIMIT, � �������� � �������������� � 0. � �� ��������� �� �����.
 */

double THINK_OF_THE_HEADING(RRFun f, double x, Error* ERROR);