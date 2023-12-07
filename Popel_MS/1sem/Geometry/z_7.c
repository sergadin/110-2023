#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

typedef struct
{
	double x;
	double y;
}Point;

typedef struct
{
	double x;
	Point y;
	Point z;
}Segm;

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

void to_output(Point *coords, int len1, int len2, FILE *f_out1, FILE *f_out2, Point p_st, Point p_end){
	Point first1=coords[0], first2=coords[len1];
	int len_m, count = 0;
	
	if (len1>len2){
		len_m = len1;
	}else{
		len_m = len2;
	}
	
	for (int i = 0; i<len_m; i++){
		if (i<len1 && i<len2){
			fprintf(f_out1, "%lf %lf %lf %lf\n", coords[i].x, coords[i].y, coords[len1+i].x, coords[len1+i].y);
		}else if (i<len1 && i>=len2){
			fprintf(f_out1, "%lf %lf %lf %lf\n", coords[i].x, coords[i].y, first2.x, first2.y);
		}else if (i>=len1 && i<len2){
			fprintf(f_out1, "%lf %lf %lf %lf\n", first1.x, first1.y, coords[len1+i].x, coords[len1+i].y);
		}
	}
	fprintf(f_out1, "%lf %lf %lf %lf\n", first1.x, first1.y, first2.x, first2.y);
	
	fprintf(f_out2, "%lf %lf\n%lf %lf\n", p_st.x, p_st.y, p_end.x, p_end.y);
}

void to_gnuplot(FILE *gnuplt){
	fprintf(gnuplt, "#! /usr/bin/gnuplot -persist\n set xlabel \"X\"\n set ylabel \"Y\"\n set grid\n set yrange [*:*]\n set xrange [*:*]\n set title \"Polygons\"\n");
	fprintf(gnuplt, "plot \"output1.txt\" u 1:2 w l lc rgb \"blue\", \"output1.txt\" u 3:4 w l lc rgb \"green\", \"output2.txt\" u 1:2 w l lc rgb \"red\"");
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

Segm point_distance(Point a, Point b){
	Segm dist;
	double x1 = a.x, y1 = a.y, x2 = b.x, y2 = b.y;
	dist.x = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
	dist.y = a;
	dist.z = b;
	return dist;
}

Segm segment_point_distance(Point a, Point b, Point c){
	Segm dist, dist1, dist2;
	Point h;
	double x0 = a.x, y0 = a.y, x1 = b.x, y1 = b.y, x2 = c.x, y2 = c.y;
	double sq, length, param;
	sq = (x2-x1)*(y0-y1)-(y2-y1)*(x0-x1);
	length = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
	if (scalar_product(b,a,b,c)>0 && scalar_product(c,a,c,b)>0){
		dist.x = fabs(sq/length);
		param = ((y2-y1)*(x1-x0)+(x1-x2)*(y1-y0))/((y2-y1)*(y2-y1)+(x1-x2)*(x1-x2));
		h.x = x0+(y2-y1)*param;
		h.y = y0+(x1-x2)*param;
		dist.y = a;
		dist.z = h;
		return (dist);
	}
	else{
		dist1 = point_distance(a,b);
		dist2 = point_distance(a,c);
		if (dist1.x<dist2.x){
			return dist1;
		}else{
			return dist2;
		}
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

Segm segment_distance(Point a, Point b, Point c, Point d){
	double l1,l2,l3,l4;
	Segm s1, s2, s3, s4;
	if (is_cross(a,b,c,d)){
		s1.x = 0.;
		s1.y = a;
		s1.z = b;
		return s1;
	}
	s1 = segment_point_distance(a,c,d);
	s2 = segment_point_distance(b,c,d);
	s3 = segment_point_distance(c,a,b);
	s4 = segment_point_distance(d,a,b);
	
	l1 = s1.x;
	l2 = s2.x;
	l3 = s3.x;
	l4 = s4.x;
	
	if (min(l1,l2)<min(l3,l4)){
		if (l1<l2){
			return s1;
		}else{
			return s2;
		}
	}else if (l3<l4){
		return s3;
	}else{
		return s4;
	}
}

int main(void){
	FILE *f_in, *f_out1, *f_out2, *gnuplt;
	Point *coords = NULL;
	Point dist_st, dist_end;
	Segm dist1, dist2;
	int len1, len2;
	double min_dist = 1000000000,thing = 0.;
	
	f_in = fopen("input.txt", "r");
	if (f_in == NULL){
		printf("Файл не открывается\n");
		return -1;
	}
	
	f_out1 = fopen("output1.txt", "w");
	if (f_in == NULL){
		printf("Файл не открывается\n");
		fclose(f_in);
		return -1;
	}
	
	f_out2 = fopen("output2.txt", "w");
	if (f_in == NULL){
		printf("Файл не открывается\n");
		fclose(f_in);
		fclose(f_out1);
		return -1;
	}
	
	gnuplt = fopen("gnuplot.gpi", "w");
	if (f_in == NULL){
		printf("Файл не открывается\n");
		fclose(f_in);
		fclose(f_out1);
		fclose(f_out2);
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
	
	dist_st.x = 0;
	dist_st.y = 0;
	dist_end.x= 0;
	dist_end.y = 0;
	
	for (int i=0; i<len1; i++){
		for (int j = 0; j<len2; j++){
			dist1 = segment_distance(coords[i], coords[(i+1)%len1], coords[len1+j], coords[len1+(j+1)%len2]);
			if (min_dist>dist1.x){
				min_dist = dist1.x;
				dist_st = dist1.y;
				dist_end = dist1.z;
			}
			if (min_dist==0.){
				dist_st.x = 0;
				dist_st.y = 0;
				dist_end.x= 0;
				dist_end.y = 0;
				printf("Многоугольники пересекаются\n");
				goto terminate_1;
				return 0;
			}
		}
	}
	
	printf("Расстояние между многоугольниками: - %lf\n", min_dist);
	terminate_1:
	to_output(coords, len1, len2, f_out1, f_out2, dist_st, dist_end);
	to_gnuplot(gnuplt);
	free  (coords);
	terminate:
	fclose(f_in);
	fclose(f_out1);
	fclose(f_out2);
	fclose(gnuplt);
	return 0;

}
