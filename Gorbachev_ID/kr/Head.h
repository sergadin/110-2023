#include <iostream>

class Polynom_Exception
{
private:
	int code_;
	std::string message_;
public:
	Polynom_Exception(int code, const std::string& message) : code_(code), message_(message) {}
	const std::string& message() const { return message_; }
	int code() const { return code_; }
};

class Polynom 
{
private:
	int deg_;
	double *pol_;
public:
	Polynom() = delete;
	Polynom(int deg);
	Polynom(const Polynom& other);
	~Polynom();

	double coefficient(const int& n);
	double calculation(const double &x);
	void change(const double &a, const int &n);
	Polynom &operator=(const Polynom& other);
	friend Polynom operator+(const Polynom& other1, const Polynom& other2);
};

Polynom::Polynom(int deg)
{
	if (deg < 0)
	{
		deg_ = 0;
	}
	deg_ = deg;
	pol_ = new double[deg_ + 1];
	for (int i = 0; i < deg_ + 1; i++)
	{
		pol_[i] = 0;
	}
}

Polynom::Polynom(const Polynom& other)
{
	pol_ = new double[0];
	*this = other;
}

Polynom::~Polynom()
{
	delete[] pol_;
}

double Polynom::coefficient(const int& n)
{
	if ((n > deg_) || (n < 0))
	{
		throw Polynom_Exception(-1, "Incorrect value");
	}
	return pol_[n];
}

double Polynom::calculation(const double& x)
{
	double temp = 1, res = 0;
	for (int i = 0; i < deg_ + 1; i++)
	{
		res += pol_[i] * temp;
		temp *= x;
	}
	return res;
}

void Polynom::change(const double& a, const int& n)
{
	if ((n > deg_) || (n < 0))
	{
		throw Polynom_Exception(-1, "Incorrect value");
	}
	pol_[n] = a;
}


Polynom& Polynom::operator=(const Polynom& other)
{
	if (this == &other) { return *this; }
	delete[] pol_;
	deg_ = other.deg_;
	pol_ = new double[deg_ + 1];
	for (int i = 0; i < deg_ + 1; i++)
	{
		pol_[i] = other.pol_[i];
	}
	return *this;
}

Polynom operator+(const Polynom& other1, const Polynom& other2)
{
	Polynom sum(std::max(other1.deg_, other2.deg_));
	for (int i = 0; i < sum.deg_; i++)
	{
		if (i <= other1.deg_)
		{
			sum.pol_[i] += other1.pol_[i];
		}
		if (i <= other2.deg_)
		{
			sum.pol_[i] += other2.pol_[i];
		}
	}
	return sum;
}

