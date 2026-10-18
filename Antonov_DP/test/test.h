#include <iostream>
using namespace std;

class vector{
	double *arr_;
	int len_;
public:
	// создаёт вектор с параметрами длинна должна быть больше нуля, если нет длины или массива, то создаётся одномерный вектор с нулём
	vector(double *a = 0, int len = 0);
	// конструктор копирования
	vector(const vector &other);
	// деструктор
	~vector();
	// задаёт конфигурацию созданного вектора, работа с параметрами такая же как и в конструкторе
	set_vector(double *a = 0, int len = 0);
	// выдаёт указатель на массив равный вектору
	double *get_vector();
	// выдаёт длину вектора
	int get_len();
	// выводит вектор на экран
	show_vector();
	// оператор присваивания
	vector &operator=(const vector &other);
	// складывает векторы и результатом является покоординатная сумма векторов
	// нужно складывать векторы одной длины, в ином случаи выдаёт исключительную ситуацию different_len
	friend vector &operator+(const vector &other1, const vector &other2);
	// вычетает векторы первый из второго покоординатно и результатом является вектор
	// нужно вычетать векторы одной длины, в ином случаи выдаёт исключительную ситуацию different_len
	friend vector &operator-(const vector &other1, const vector &other2);
	// умножает покоординатно вектор на число (double) число должно быть обязательно слева иначе не заработает
	friend vector &operator*(const double &n, const vector &other);
	// вычисляет скалярное произведение векторов
	// нужно скалярно умножать векторы одной длины, в ином случаи выдаёт исключительную ситуацию different_len
	double scal(const vector &other1, const vector &other2);
}

class MyException:
	public exception
{
}
