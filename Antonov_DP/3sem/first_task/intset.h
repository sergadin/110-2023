#include <iostream>

class intset{
	int *set_;
	int left_;
	int right_;
public:
	intset() = delete;
	// конструктор работает только с двумя входными данными, без входных данных будет ошибка
	intset(int left, int right);
	intset(const intset &other);
	~intset();
	// добавляет элемент, если элемент за пределами множества, то будет исключительная ситуация с -1 Intset_Exception
	void add(const int elem);
	// удаляет элемент, если элемент за пределами множества, то будет исключительная ситуация с -1 Intset_Exception
	void del(const int elem);
	// проверяет пусто ли множество
	bool check();
	// выдаёт длину множества
	int len();
	// выводит максимальное число в множестве, но если множество пусто то выводит right_ + 1
	int max();
	// выводит минимальное число в множестве, но если множество пусто то выводит left_ - 1
	int min();
	// выдаёт левую границу
	int left();
	// выдаёт правую границу
	int right();
	intset &operator=(const intset &other);
	// если отрезки не пересекаются то выдаёт пустое множество с границами left_ левого и right_ правого
	// иначе честное пересечение множество с границами пересечения
	friend intset operator*(const intset &other1, const intset &other2);
	friend intset operator*=(intset &ours, const intset &other2);
	friend bool operator==(const intset &other1, const intset &other2);
};

class Intset_Exception {
  int code_;
  std::string message_;
public:
  Intset_Exception(int code, const std::string& message) : code_(code), message_(message) {}
  const std::string& message() const { return message_; }
  int code() const { return code_; }
};
