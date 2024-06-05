#include <vector>

typedef double (*R_Rfun)(double);
typedef struct {
	double x;
	double y;
} dot;

double square(dot A, dot B, dot C, double x);
void Y(R_Rfun f, const std::vector<double> &x, std::vector<double> &y);
void interp(const std::vector<double> &x1, const std::vector<double> &y1, const std::vector<double> &x2, std::vector<double> &y2);
