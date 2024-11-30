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
protected:
	// прямоугольник, стороны которого параллельны осям координат, 
	// задаётся по двум диаметрально противоположным точкам.
	point a_;
	point b_;
public:
	rectangle(point a = 0, point b = 0){
		a_ = a;
		b_ = b;
	}
	operator=(const rectangle &other){
		a_ = other.a_;
		b_ = other.b_;
	}
	rectangle(const rectangle &other){
		a_ = other.a_;
		b_ = other.b_;
	}
	point &get_a() const{
		return a_;
	}
	point &get_b() const{
                return b_;
        }
}

class TreeNode : public rectangle{
	TreeNode *small_;
public:
	TreeNode(double a, double b, n = 10) : rectangle(a, b){
		small_ = new TreeNode[n * n];
		double d_a(b_[0] - a_[0]), d_b(b_[1] - a_[1]);
		for (int i = 0; i < n ; i++){
			for (int j = 0){
				small_
			}
		}
	}
}






