#include <iostream>

class point {
	double* point_;
	bool real_;
public:
	point(double a = 0, double b = 0, bool real = true) {
		point_ = new double[2];
		point_[0] = a;
		point_[1] = b;
		real_ = real;
	}
	~point() {
		delete[] point_;
	}
	point(const point& other) {
		point_ = new double[2];
		point_[0] = other.point_[0];
		point_[1] = other.point_[1];
		real_ = other.real_;
	}
	point &operator=(const point& other) {
		if (this == &other) { return *this; }
		delete[] point_;
		point_ = new double[2];
		point_[0] = other.point_[0];
		point_[1] = other.point_[1];
		real_ = other.real_;
		return *this;
	}
	double* get() const{
		double* result;
		result = new double[2];
		result[0] = point_[0];
		result[1] = point_[1];
		return result;
	}
	double &operator[](int n) {
		return point_[n];
	}
	bool real() const {
		return real_;
	}
};

class rectangle{
	// задаётся по двум диаметрально противоположным точкам
	point a_;
	point b_;
public:
	rectangle(point a, point b){
		a_ = a;
		b_ = b;
	}
}
