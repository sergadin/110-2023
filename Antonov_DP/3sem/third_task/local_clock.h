#include <iostream>


class local_clock{
	int *local_clock_;
	size_t len_;
public:
	local_clock() = delete;
	local_clock(size_t len){
		len_ = len;
		local_clock_ = new int[len];
		for (size_t i = 0; i < len_; i++){
			local_clock_[i] = 0;
		}
	}
	~local_clock(){ delete[] local_clock_; }
	local_clock(const local_clock &other){
		len_ = other.len_;
		local_clock_ = new int[len_];
		for(size_t i = 0; i < len_; i++){
                        local_clock_[i] = other.local_clock_[i];
                }
	}
	local_clock &operator=(const local_clock &other){
		delete[] local_clock_;
		len_ = other.len_;
		local_clock_ = new int[len_];
		for(size_t i = 0; i < len_; i++){
			local_clock_[i] = other.local_clock_[i];
		}
		return *this;
	}

	// поднимает счётчик k-ой координаты на один во втором поле сообщение сообщение выводимое в поток stream
	void iteration(size_t &k, std::string a = "process completed", std::ostream &stream = std::cout);

	// меняет значение в зависимости от метки, во втором поле сообщение выводимое в поток stream
	void get_message(const local_clock &other, std::string a = "process completed", std::ostream &stream = std::cout);
	friend bool operator<(const local_clock &other1, const local_clock &other2);

	// получить значение локального времени
	int *get_vector();
};


class local_clock_Exception {
  int code_;
  std::string message_;
public:
  local_clock_Exception(int code, const std::string& message) : code_(code), message_(message) {}
  const std::string& message() const { return message_; }
  int code() const { return code_; }
};
