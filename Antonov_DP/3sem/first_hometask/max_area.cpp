#include <iostream>
#include <cmath>
#include "triangle.h"
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <cstring>

typedef enum { MOVE = 0, ROTATE } OPTION;

void draw_tr(triangle &test, triangle &other, std::string &pid_str);

void draw_tr(triangle &test, triangle &other, std::string &pid_str){
        std::string pid_str_other = "kill -STOP ";
	pid_str_other += pid_str;
        system(pid_str_other.c_str());
	std::ofstream out1("triangle1.txt");
	std::ofstream out2("triangle2.txt");
        for (int i = 0; i < 3; i++){
                out1 << test[i][0] << " " << test[i][1] << "\n";
        }
        out1 << test[0][0] << " " << test[0][1] << "\n";

        out1.close();

        for (int i = 0; i < 3; i++){
                out2 << other[i][0] << " " << other[i][1] << "\n";
        }
        out2 << other[0][0] << " " << other[0][1] << "\n";

        out2.close();
	
        pid_str_other = "kill -CONT ";
        pid_str_other += pid_str;
        system(pid_str_other.c_str());

	usleep(5000);

	return;
}

static int compRR(double a, double b, double eps);
static void move_horiz(triangle &tr, double x);
static double max_value_parab(double x1, double y1, double x2, double y2, double x3, double y3, double eps);
static void max_value(void (*move)(triangle &, double), triangle &test, triangle &other, OPTION opt, std::string &pid_str);
static void move_vert(triangle &tr, double y);
static void rotate(triangle &tr, double a);
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MAX3(a, b, c) MAX(MAX((a), (b)), (c))

static int compRR(double a, double b, double eps)
{
        if (fabs(a - b) < eps * MAX3(a, b, 1))
	{
		return 0;
	}
	if (a > b)
	{
		return 1;
	}
	return -1;
}

static double max_value_parab(double x1, double y1, double x2, double y2, double x3, double y3, double eps)
{
	double a, b, c;
	if (compRR(y1, y3, eps) == 0) 
	{
		if (y1 > y2)
		{
			return y1;
		}
		return y2;
	}
	if ((compRR(y1, y2, eps) != 1) && (compRR(y1, y3, eps) != 1))
	{
		return y1;
	}
	if ((compRR(y3, y2, eps) != 1) && (compRR(y3, y1, eps) != 1))
        {
                return y3;
        }
	a = ((y1 - y2) * (x1 - x3) - (y1 - y3) * (x1 - x2)) / ((x1 - x2) * (x1 - x3) * (x2 - x3));
	b = (y1 - y2) - a * (x1 + x2);
	c = y1 - (a * x1 * x1) - (b * x1);
	return ((4 * a * c) - (b * b)) / (4 * a);
}

static void move_horiz(triangle &tr, double x){
	tr.move(x, 0);
	return;
}

static void move_vert(triangle &tr, double y){
        tr.move(0, y);
	return;
}

static void rotate(triangle &tr, double a){
	double *centre = tr.get_centre();
	tr.rotate(centre, a);
	delete[] centre;
	return;
}

static void max_value(void (*move)(triangle &, double ), triangle &test, triangle &other, OPTION opt, std::string &pid_str)
{
	double a, b;
	if (opt == MOVE){
		a = -1 * std::min((test.get_s() / other.get_p()), (other.get_s() / other.get_p()));
		b = -1 * a;
	}
	else{
		a = 0;
		b = 2 * std::acos(-1);
	}
	double f_prev, f_curr, a1_h = a, b1_h = b, a2_h = 0, a1_v = a, b1_v = b, a2_v = 0, f_mid, result, max_par, d = 0;
	double eps = 0.0001;
	int n = 10;
	move(other, a);
	if (opt == MOVE){ move_vert(other, a);}
	while(compRR(a1_h, b1_h, eps) != 0)
	{
		d = (b1_h - a1_h) / n;
		f_curr = test.Area_intersection(other);
		result = f_curr;
		a2_h = a1_h;
		a2_v = a1_v;

		for (int i = 0 ; i < n; i++)
		{
			if (opt == MOVE){
				for (int j = 0; j < n; j++){
					f_prev = f_curr; 
                        		move_vert(other, (d / 2));
                        		f_mid = test.Area_intersection(other);
                        		move_vert(other, (d / 2));
                        		f_curr = test.Area_intersection(other);
                        		max_par = max_value_parab(0, f_prev, (d / 2), f_mid, d, f_curr, eps);
                        		if (max_par > (result))
                        		{       
                        		        result = max_par;
                        		      	a2_v = a1_v + (d * j);
						a2_h = a1_h + (d * i);
                        		}
					draw_tr(test, other, pid_str);
				}
				move_vert(other, (a1_v - b1_v));
				move(other, d);
			}
			else{
				f_prev = f_curr;
				move(other, (d / 2));
				f_mid = test.Area_intersection(other);
				move(other, (d / 2));
				f_curr = test.Area_intersection(other);
				max_par = max_value_parab(0, f_prev, (d / 2), f_mid, d, f_curr, eps);
				if (max_par > (result + 0.1))
				{
					result = max_par;
					a2_h = a1_h + (d * i);
				}
			}
			draw_tr(test, other, pid_str);
		}
		move(other, a2_h - b1_h);
		a1_h = a2_h;
		b1_h = a2_h + d;
		if (opt == MOVE){
			move_vert(other, a2_v - a1_v);
                	a1_v = a2_v;
                	b1_v = a2_v + d;
		}
	}
	return;
}

double Max_Area_inter(triangle &test, triangle &other)
{
    double* centre = test.get_centre();
    double* centre1 = other.get_centre();
    double x = centre[0] - centre1[0];
    double y = centre[1] - centre1[1];
    double z = 0.1;
	pid_t parent = getpid();
        pid_t pid = fork();
	parent += 2;
	std::string pid_str = std::to_string(parent);
        if (pid > 0)
        {
	    system("gnuplot -persist mygnuplot.gnu");
	    delete[] centre;
	    delete[] centre1;
	    test.~triangle();
	    other.~triangle();
            exit(0);
        }

	draw_tr(test, other, pid_str);

    while (std::abs(centre[0] - centre1[0]) > 0.0001)
    {
        other.move(x * z, y * z);
        centre1[0] += (x * z);
        centre1[1] += (y * z);
	
	draw_tr(test, other, pid_str);
    }

    double area = test.Area_intersection(other);
    double area_prev = 0;
    int i = 0;
    while ((std::fabs(area - area_prev) > 0.001) && (std::fabs(area - other.get_s()) > 0.001) && (std::fabs(area - test.get_s()) > 0.001) && (i < 15)){
	    max_value(rotate, test, other, ROTATE, pid_str);
	    max_value(move_horiz, test, other, MOVE, pid_str);
	    area_prev = area;
	    area = test.Area_intersection(other);
	    i++;
    }
    delete[] centre;
    delete[] centre1;
    std::cout << "Max area of intersection = " << area << "\n";
    std::string pid_str_other = "kill ";
    pid_str_other += pid_str;
    system(pid_str_other.c_str());
    return 0;
}
