typedef double (*R_Rfun)(double);
typedef enum {OK, E_LIMIT} ERROR;

double integral(R_Rfun f, double a, double b, double eps, ERROR *err);
double rect(R_Rfun f, double a, double b, int n);
int are_equal(double a, double b, double eps);
