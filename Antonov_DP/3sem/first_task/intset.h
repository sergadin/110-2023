#include <iostream>

class intset{
	int *set_;
	int left_;
	int right_;
public:
	intset(int left, int right);
	intset(const intset &other);
	~intset();
	void add(const int elem);
	void del(const int elem);
	bool check();
	int len();
	int max();
	int min();
	int left();
	int right();
	intset &operator=(const intset &other);
	friend intset operator*(const intset &other1, const intset &other2);
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
