#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

typedef struct
{
	double x;
	double y;
}Point;

double min(double a, double b){
	if (a < b){
		return a;
	}else{
		return b;
	}
}

Point vector(Point a, Point b){
	Point ab;
	ab.x = (b.x-a.x);
	ab.y = (b.y - a.y);
	return ab;
}

double scalar_product(Point a, Point b, Point c, Point d){
	Point v1, v2;
	v1 = vector(a,b);
	v2 = vector(c,d);
	return(v1.x*v2.x + v1.y*v2.y);

}

double oblique_product(Point a, Point b, Point c, Point d){
	Point v1, v2;
	v1 = vector(a,b);
	v2 = vector(c,d);
	return(v1.x*v2.y - v1.y*v2.x);
}

double point_distance(Point a, Point b){
	double x1 = a.x, y1 = a.y, x2 = b.x, y2 = b.y;
	return (sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)));
}

double segment_point_distance(Point a, Point b, Point c){
	double x0 = a.x, y0 = a.y, x1 = b.x, y1 = b.y, x2 = c.x, y2 = c.y;
	double sq, length;
	sq = (x2-x1)*(y0-y1)-(y2-y1)*(x0-x1);
	length = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
	if (scalar_product(b,a,b,c)>0 && scalar_product(c,a,c,b)>0){
		return (fabs(sq/length));
	}
	else{
		return(min(point_distance(a,b), point_distance(a,c)));
	}
}

bool is_cross(Point p1, Point p2, Point m1, Point m2){
	double obl1, obl2, obl3, obl4, on_seg1, on_seg2, on_seg3, on_seg4;
	int on_seg = 0;
	obl1 = oblique_product(p1,p2,p1,m2);
	obl2 = oblique_product(p1,p2,p1,m1);
	obl3 = oblique_product(m1,m2,m1,p1);
	obl4 = oblique_product(m1,m2,m1,p2); 
	on_seg1 = scalar_product(m2,p1,m2,p2);
	on_seg2 = scalar_product(m1,p1,m1,p2);
	on_seg3 = scalar_product(p1,m1,p1,m2);
	on_seg4 = scalar_product(p2,m1,p2,m2);
	
	if ((on_seg1 <=0 && obl1==0) || (on_seg2<=0 && obl2==0) || (on_seg3<=0 && obl3==0) || (on_seg4<=0 && obl4==0)){
		on_seg = 1;
	}
	if ((obl1*obl2<0 && obl3*obl4<0) || on_seg == 1){
		return true;
	}else{
		return false;
	}
	
}

double segment_distance(Point a, Point b, Point c, Point d){
	double l1,l2,l3,l4;
	if (is_cross(a,b,c,d)){
		return 0.;
	}
	l1 = segment_point_distance(a,c,d);
	l2 = segment_point_distance(b,c,d);
	l3 = segment_point_distance(c,a,b);
	l4 = segment_point_distance(d,a,b);
	
	return min(min(l1,l2),min(l3,l4));
}

int main(void){
	FILE *f_in;
	Point *coords = NULL;
	int len1, len2;
	double min_dist = 1000000000,thing = 0.;
	
	f_in = fopen("input.txt", "r");
	if (f_in == NULL){
		printf("Файл не открывается\n");
		return -1;
	}
	
	fscanf(f_in, "%d%d", &len1, &len2);
	
	coords = (Point *)malloc((len1+len2)*sizeof(Point));
	
	if (coords == NULL){
		printf("Оперативная память не выделена\n");
		goto terminate;
	}
	for (int i=0; i<(len1+len2); i++){
		fscanf(f_in, "%lf%lf", &coords[i].x, &coords[i].y);
	}
	
	
	for (int i=0; i<len1; i++){
		for (int j = 0; j<len2; j++){
			min_dist = min(min_dist, segment_distance(coords[i], coords[(i+1)%len1], coords[len1+j], coords[len1+(j+1)%len2]));
			if (min_dist==0.){
				printf("Многоугольники пересекаются\n");
				fclose(f_in);
				free (coords);
				return 0;
			}
		}
	}
	
	printf("Расстояние между многоугольниками: - %lf\n", min_dist);
	free  (coords);
	terminate:
	fclose(f_in);
	return 0;

}
