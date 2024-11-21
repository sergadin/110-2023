#include <iostream>
#include "triangle.h"
#include <cmath>

point segment::intersection(const segment& other) const{
	double t1, t2;
	point x1;
	point x2;
	x1 = points_[0];
	x2 = other.points_[0];
	double a1 = points_[1][0] - points_[0][0];
	double b1 = points_[1][1] - points_[0][1];
	double a2 = other.points_[1][0] - other.points_[0][0];
	double b2 = other.points_[1][1] - other.points_[0][1];
	if (std::fabs(b1 * a2 - a1 * b2) < 0.001) {
		point res(0, 0, false);
		return res;
	}
	t2 = (b1 * (x1[0] - x2[0]) - a1 * (x1[1] - x2[1])) / (b1 * a2 - a1 * b2);
	if ((t2 > 1) || (t2 < 0)) {
		point res(0, 0, false);
		return res;
	}
	if (fabs(a1) < 0.001) {
		t1 = (x2[1] + b2 * t2 - x1[1]) / b1;
	}
	else {t1 = (x2[0] + a2 * t2 - x1[0]) / a1;}
	if ((t1 > 1) || (t1 < 0)) {
		point res(0, 0, false);
		return res;
	}
	point res(x2[0] + a2 * t2, x2[1] + b2 * t2);
	return res;
}

triangle::triangle(double* points) {
	points_ = new point[3];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			points_[i][j] = points[(2 * i) + j];
		}
	}
	a_ = std::sqrt(std::pow(points_[0][0] - points_[1][0], 2) + std::pow(points_[0][1] - points_[1][1], 2));
	b_ = std::sqrt(std::pow(points_[1][0] - points_[2][0], 2) + std::pow(points_[1][1] - points_[2][1], 2));
	c_ = std::sqrt(std::pow(points_[2][0] - points_[0][0], 2) + std::pow(points_[2][1] - points_[0][1], 2));
	p_ = (a_ + b_ + c_) / 2;
	S_ = std::sqrt(p_ * (p_ - a_) * (p_ - b_) * (p_ - c_));
}

triangle::triangle(point points[3]) {
	points_ = new point [3];
	for (int i = 0; i < 3; i++) {
		points_[i] = points[i];
	}
	a_ = std::sqrt(std::pow(points_[0][0] - points_[1][0], 2) + std::pow(points_[0][1] - points_[1][1], 2));
	b_ = std::sqrt(std::pow(points_[1][0] - points_[2][0], 2) + std::pow(points_[1][1] - points_[2][1], 2));
	c_ = std::sqrt(std::pow(points_[2][0] - points_[0][0], 2) + std::pow(points_[2][1] - points_[0][1], 2));
	p_ = (a_ + b_ + c_) / 2;
	S_ = std::sqrt(p_ * (p_ - a_) * (p_ - b_) * (p_ - c_));
}

triangle::~triangle() {
	delete[] points_;
}

triangle& triangle::operator=(const triangle& other) {
	if (this == &other) { return *this; }
	delete[] points_;
	points_ = new point [3];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			points_[i][j] = other.points_[i][j];
		}
	}
	a_ = other.a_;
	b_ = other.b_;
	c_ = other.c_;
	S_ = other.S_;
	p_ = other.p_;
	return *this;
}

triangle::triangle(const triangle& other) {
	points_ = new point [3];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			points_[i][j] = 0;
		}
	}
	*this = other;
}

double triangle::get_s()const {
	return S_;
}

double triangle:: get_p()const{
	return p_;
}

void triangle::move(const double& x, const double& y) {
	for (int i = 0; i < 3; i++) {
		points_[i][0] += x;
		points_[i][1] += y;
	}
	return;
}

double* triangle::get_centre() const{
	double x1 = (points_[0][0] - points_[1][0]) / a_;
	double y1 = (points_[0][1] - points_[1][1]) / a_;
	double x2 = (points_[2][0] - points_[1][0]) / b_;
	double y2 = (points_[2][1] - points_[1][1]) / b_;
	double r = S_ / p_;
	double x3 = x1 + x2;
	double y3 = y1 + y2;
	double t = std::abs(( - 1) * y1 * (points_[1][0] + x3) + x1 * (points_[1][1] + y3) + y1 * (points_[1][0]) - x1 * (points_[1][1])) / (std::sqrt(y1 * y1 + x1 * x1));
	double* centre;
	centre = new double[2];
	centre[0] = points_[1][0] + x3 * (r / t);
	centre[1] = points_[1][1] + y3 * (r / t);
	return centre;
}

void triangle::rotate(const double* centre, const double &angle) {
	double temp;
	for (int i = 0; i < 3; i++) {
		points_[i][0] -= centre[0];
		points_[i][1] -= centre[1];
		double length = std::sqrt(pow(points_[i][0], 2) + pow(points_[i][1], 2));
		points_[i][1] = points_[i][1] / length;
		points_[i][0] = points_[i][0] / length;
		temp = points_[i][0];
		points_[i][0] = points_[i][0] * std::cos(angle) - points_[i][1] * std::sin(angle);
		points_[i][1] = temp * std::sin(angle) + points_[i][1] * std::cos(angle);
		points_[i][0] *= length;
		points_[i][1] *= length;
		points_[i][0] += centre[0];
		points_[i][1] += centre[1];
	}
	return;
}

bool triangle::contains(point &A) const{
	for (int i = 0; i < 3; i++) {
		double a = points_[(i + 1) % 3][0] - points_[i][0];
		double b = points_[(i + 1) % 3][1] - points_[i][1];
		if (((b * A[0] - a * A[1] - (b * points_[i][0] - a * points_[i][1])) * (b * points_[(i + 2) % 3][0] - a * points_[(i + 2) % 3][1] - (b * points_[i][0] - a * points_[i][1]))) < 0) {
			return false;
		}
	}
	return true;
}

double triangle::Area_intersection(triangle& other) {

	double a = points_[1][0] - points_[0][0];
        double b = points_[1][1] - points_[0][1];
        if (std::fabs(b * points_[2][0] - a * points_[2][1] - (b * points_[0][0] - a * points_[0][1])) < 0.001){
		return 0;
        }

	a = other.points_[1][0] - other.points_[0][0];
        b = other.points_[1][1] - other.points_[0][1];
        if (std::fabs(b * other.points_[2][0] - a * other.points_[2][1] - (b * other.points_[0][0] - a * other.points_[0][1])) < 0.001){
                return 0;
        }

	int len = 0;
	point* vert = new point[6];
	for (int i = 0; i < 3; i++) {
		point temp;
		temp = other[i];
		if (this->contains(other[i])) {
			
			vert[len] = other[i];
			len++;
		}
	}
	for (int i = 0; i < 3; i++) {
		if (other.contains((*this)[i])) {
			vert[len] = (*this)[i];
			len++;
		}
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			point temp;
			temp = this->get_segment(i).intersection(other.get_segment(j));
			if (temp.real()) {
				vert[len] = temp;
				len++;
			}
		}
	}
	

	if (len < 3) {
		delete[] vert;
		return 0;
	}

	point center;
	for (int i = 0; i < len; i++) {
		center[0] += vert[i][0];
		center[1] += vert[i][1];
	}
	center[0] = center[0] / len;
	center[1] = center[1] / len;

	double* length = new double[len];
	for (int i = 0; i < len; i++) {
		vert[i][0] -= center[0];
		vert[i][1] -= center[1];
		length[i] = sqrt(pow(vert[i][0], 2) + pow(vert[i][1], 2));
		vert[i][0] /= length[i];
		vert[i][1] /= length[i];
	}
	double* angles = new double[len];
	for (int i = 0; i < len; i++) {
		if ((std::asin(vert[i][1]) < 0)) {
			angles[i] = (-1) * std::acos(vert[i][0]);
		}
		else { angles[i] = std::acos(vert[i][0]); }
	}

	double temp_angle;
	double temp_length;
	point temp_vert;
	for (int i = 0; i < len; i++) {
		for (int j = i + 1; j < len; j++) {
			if (angles[j] > angles[i]) {
				temp_angle = angles[i];
				angles[i] = angles[j];
				angles[j] = temp_angle;


				temp_length = length[i];
				length[i] = length[j];
				length[j] = temp_length;


				temp_vert = vert[i];
				vert[i] = vert[j];
				vert[j] = temp_vert;
			}
		}
	}
	
	for (int i = 0; i < len; i++) {
		vert[i][0] *= length[i];
		vert[i][1] *= length[i];
	}

	double area = 0;
	for (int i = 1; i < len - 1; i++) {
		point *points = new point[3];
		points[0] = vert[0];
		points[1] = vert[i];
		points[2] = vert[i + 1];
		triangle part_of_area(points);
		area += part_of_area.get_s();
		delete[] points;
	}

	for (int i = 0; i < len; i++) {
                std::cout << vert[i][0] << " " << vert[i][1] << "\n";
        }
	std::cout << "\n";

	delete[] vert;
	delete[] length;
	delete[] angles;
	return area;
}
