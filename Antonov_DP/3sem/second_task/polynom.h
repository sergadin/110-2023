#include <iostream>

class polynom {
	double *pol_;
	int ord_;
public:
	polynom(int ord = 0);
	~polynom();
	polynom(const polynom& other);
	polynom &operator=(const polynom& other);
	int deg();
	double calc(const double &x);
	double coef_deg(const int &n);
	void change(const double &a, const int &n);
	friend polynom operator+(const polynom& other1, const polynom& other2);
};

class Polynom_Exception {
  int code_;
  std::string message_;
public:
  Polynom_Exception(int code, const std::string& message) : code_(code), message_(message) {}
  const std::string& message() const { return message_; }
  int code() const { return code_; }
};
