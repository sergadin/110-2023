typedef double (*R_Rfun)(double);

void min_dots(R_Rfun f, double *a, double *b, int n, double eps);
int min_search(R_Rfun f, double *a, double *b, double eps);
