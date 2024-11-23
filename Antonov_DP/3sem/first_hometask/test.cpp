#include "triangle.h"

int main(){
	double points1[] = {1, 2, 3, 2, 5, 7};
	double points2[] = {-1, 4, 3, 2, 6, 7};

	triangle tr1(points1), tr2(points2);
	Max_Area_inter(tr1, tr2);
}
