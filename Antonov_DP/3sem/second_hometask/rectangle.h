#include <iostream>
#include <cmath>

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
	bool compare(point &other){
		if ((std::fabs(point_[0] - other.point_[0]) < 0.0001) && (std::fabs(point_[1] - other.point_[1]) < 0.0001)){
			return true;
		}
		return false;
	}
};

class rectangle{
protected:
	// прямоугольник, стороны которого параллельны осям координат, 
	// задаётся по двум диаметрально противоположным точкам.
	point a_;
	point b_;
public:
	rectangle(){
		point a(0, 0), b(0, 0);
		a_ = a;
		b_ = b;
	}
	rectangle(point a, point b){
		a_ = a;
		b_ = b;
	}
	rectangle(const rectangle &other){
		a_ = other.a_;
		b_ = other.b_;
	}
	point get_a() const{
		return a_;
	}
	point get_b() const{
                return b_;
        }
	void set_a(point a){
		a_ = a;
	}
	void set_b(point b){
                b_ = b;
        }
};

class TreeNode : public rectangle{
	TreeNode *small_;
	point *points_;
	int level_;
	int len_;
public:
	TreeNode() : rectangle(){
                points_ = new point[0];
                small_ = 0;
                level_ = 0;
                len_ = 0;
        }

	//создаёт ветку дерева в виде прямоугольника
	TreeNode(point a, point b) : rectangle(a, b){
		points_ = new point[0];
		small_ = 0;
		level_ = 0;
		len_ = 0;
	}
	~TreeNode(){
		delete[] points_;
		if (small_ != 0){ delete[] small_; }
	}

	// установить уровень
	void set_level(int n){
		level_ = n;
	}

	// добавить точку в множество
	int add_point(point &p);

	//превращает конец дерева в ветвь
	void change();

	//удаляет точку по координате точки
	int delete_point(point &p);

	//проверяет есть ли точка в множестве, выдаёт true если да, и false, если нет
	bool point_in_set(point &p);

	//выдаёт длину множества
	int len();

	//даёт указатель на массив точек, находящихся в окрестности с данной точкой p
	point *neighbours(point &p);

	//выдаёт длину множества точек, находящихся в окрестности с данной точкой p
	int get_len_neighbours(point &p);

	//выдаёт n-ую точку множества
	point operator[](int n);
};

class Rectangle_Exception {
  int code_;
  std::string message_;
public:
  Rectangle_Exception(int code, const std::string& message) : code_(code), message_(message) {}
  const std::string& message() const { return message_; }
  int code() const { return code_; }
};
