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

class segment {
	point* points_;
	double length_;
public:
	segment() = delete;
	segment(point& a, point& b) {
		points_ = new point[2];
		points_[0] = a;
		points_[1] = b;
		length_ = std::sqrt(pow(a[0] - b[0], 2) + pow(a[1] - b[1], 2));
	}
	~segment() { delete[] points_; }
	segment(const segment &other) {
		length_ = other.length_;
		points_ = new point[2];
		points_[0] = other.points_[0];
		points_[1] = other.points_[1];
	}
	segment& operator=(const segment& other) {
		if (this == &other) { return *this; }
		delete[] points_;
		length_ = other.length_;
		points_ = new point[2];
		points_[0] = other.points_[0];
		points_[1] = other.points_[1];
	}
	point operator[](int n) {
		point temp(points_[n][0], points_[n][1]);
		return temp;
	}
	point intersection(const segment& other) const;
};

class triangle {
public:
	point* points_;
	double a_, b_, c_;
	// площадь треугольника
	double S_;
	// полу-периметр треугольника
	double p_;
	triangle() = delete;
	triangle(double* points);
	triangle(point points[3]);
	~triangle();
	triangle(const triangle& other);
	triangle& operator=(const triangle& other);
	double get_s() const;
	void move(const double &x, const double &y);
	void rotate(const double *centre, const double &angle);
	double* get_centre() const;
	bool contains(point &A) const;
	segment get_segment(int &n) const {
		point a1(points_[n % 3][0], points_[n % 3][1]), a2(points_[(n + 1) % 3][0], points_[(n + 1) % 3][1]);
		segment result(a1, a2);
		return result;
	}
	point &operator[](int n) {
		return points_[n];
	}
	double Area_intersection(triangle& other);
};
