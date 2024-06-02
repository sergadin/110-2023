typedef double (*R_Rfun)(double);

double integral(R_Rfun f, double a, double b, double eps, int *err);
double rect(R_Rfun f, double a, double b, int n);
int compare(double a, double b, double eps);
