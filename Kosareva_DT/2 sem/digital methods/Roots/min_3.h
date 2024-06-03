typedef double (*R_Rfun)(double);

void min_dots(R_Rfun f, double *a, double *b, int n, double eps);
double min_search(R_Rfun f, double a, double b, double eps, int *err);
double max(double a, double b, double c);
