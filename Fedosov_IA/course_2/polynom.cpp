#include <iostream>
#include <stdexcept>
#include <cmath>

class Polynom {
private:
    double* coefficients;
    size_t degree;

public:

    Polynom(size_t degree = 0, double default_value = 0.0) : degree(degree) {
        coefficients = new double[degree + 1];
        for (size_t i = 0; i <= degree; ++i) {
            coefficients[i] = default_value;
        }
    }


    ~Polynom() {
        delete[] coefficients;
    }


    Polynom(const Polynom& other) : degree(other.degree) {
        coefficients = new double[degree + 1];
        for (size_t i = 0; i <= degree; ++i) {
            coefficients[i] = other.coefficients[i];
        }
    }


    Polynom& operator=(const Polynom& other) {
        if (this != &other) {
            delete[] coefficients;
            degree = other.degree;
            coefficients = new double[degree + 1];
            for (size_t i = 0; i <= degree; ++i) {
                coefficients[i] = other.coefficients[i];
            }
        }
        return *this;
    }


    void setCoefficient(size_t degree, double value) {
        if (degree > this->degree) {
            throw std::out_of_range("Недопустимая степень полинома");
        }
        coefficients[degree] = value;
    }


    double getCoefficient(size_t degree) const {
        if (degree > this->degree) {
            throw std::out_of_range("Недопустимая степень полинома");
        }
        return coefficients[degree];
    }


    double evaluate(double x) const {
        double result = 0.0;
        for (size_t i = 0; i <= degree; ++i) {
            result += coefficients[i] * std::pow(x, i);
        }
        return result;
    }


    Polynom operator+(const Polynom& other) const {
        size_t max_degree = std::max(degree, other.degree);
        Polynom result(max_degree);

        for (size_t i = 0; i <= max_degree; ++i) {
            double coeff1 = (i <= degree) ? coefficients[i] : 0.0;
            double coeff2 = (i <= other.degree) ? other.coefficients[i] : 0.0;
            result.setCoefficient(i, coeff1 + coeff2);
        }

        return result;
    }


    void print() const {
        double EPS = 0.000000001;
        for (size_t i = degree; i < degree + 1; --i) {
            if (abs(coefficients[i]) > EPS) {
                std::cout << (coefficients[i] > 0 && i != degree ? " + " : "")
                          << coefficients[i] << "x^" << i;
            }
        }
        std::cout << std::endl;
    }
};

int main() {
    try {

        Polynom p1(2);  // Полином степени 2
        p1.setCoefficient(0, 1);  // x^0
        p1.setCoefficient(1, 2);  // x^1
        p1.setCoefficient(2, 3);  // x^2

        Polynom p2(1);  // Полином степени 1
        p2.setCoefficient(0, -1);  // x^0
        p2.setCoefficient(1, 1);   // x^1


        Polynom p3 = p1;
        std::cout << "p3 (копия p1): ";
        p3.print();


        p3 = p2;
        std::cout << "p3 (после присваивания p2): ";
        p3.print();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
