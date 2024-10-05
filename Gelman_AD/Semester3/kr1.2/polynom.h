#include <iostream>

class Polynom
{
	int degree_;
	double* pol_;
public:
	Polynom() = delete;
	Polynom(int degree);
	Polynom(const Polynom& other);
	~Polynom();
	void change(const double& a, const int& n);
	double coefficient(const int& n);
	double calculation(const double& x);
	Polynom& operator=(const Polynom& other);
	friend Polynom operator+(const Polynom& other1, const Polynom& other2);
};

// Errors
class Polynom_Exception
{
	int code_;
	std::string message_;
public:
	Polynom_Exception(int code, const std::string& message) : code_(code), message_(message) {}
	const std::string& message() const { return message_; }
	int code() const { return code_; }
};

// Polynom constructor
Polynom::Polynom(int degree)
{
	if (degree < 0)
	{
		degree_ = 0;
	}

	degree_ = degree;
	pol_ = new double[degree_ + 1];

	for (int i = 0; i < degree_ + 1; i++)
	{
		pol_[i] = 0;
	}
}

// Copying
Polynom::Polynom(const Polynom& other)
{
	pol_ = new double[0];
	*this = other;
}

// Destructor
Polynom::~Polynom()
{
	delete[] pol_;
}

// Changing coefficients 
// a - what coefficient we want; n - degree of this coefficient
void Polynom::change(const double& a, const int& n)
{
	if ((n > degree_) || (n < 0))
	{
		throw Polynom_Exception(-1, "Incorrect value");
	}
	pol_[n] = a;
}

// Polynom coefficient
double Polynom::coefficient(const int& n)
{
	if ((n > degree_) || (n < 0))
	{
		throw Polynom_Exception(-1, "No such degree");
	}
	return pol_[n];
}

// y = f(x)
double Polynom::calculation(const double& x)
{
	double temporary = 1, result = 0;
	for (int i = 0; i < degree_ + 1; i++)
	{
		result += pol_[i] * temporary;
		temporary *= x;
	}
	return result;
}

// Equivalent polynoms
Polynom& Polynom::operator=(const Polynom& other)
{
	if (this == &other) { return *this; }
	delete[] pol_;
	degree_ = other.degree_;
	pol_ = new double[degree_ + 1];
	for (int i = 0; i < degree_ + 1; i++)
	{
		pol_[i] = other.pol_[i];
	}
	return *this;
}

// The sum of two polynoms
Polynom operator+(const Polynom& other1, const Polynom& other2)
{
	Polynom sum(std::max(other1.degree_, other2.degree_));
	for (int i = 0; i < sum.degree_; i++)
	{
		if (i <= other1.degree_)
		{
			sum.pol_[i] += other1.pol_[i];
		}
		if (i <= other2.degree_)
		{
			sum.pol_[i] += other2.pol_[i];
		}
	}
	return sum;
}