typedef double (*R_Rfun)(double);
typedef enum {OK, LIMIT, SAME_SIGN, NO_FUNCTION} error;

double root(R_Rfun f, double a, double b, double eps, int *count, error *err);
