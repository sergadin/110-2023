#include <iostream>


class restaurant{
	clock **int_;
	size_t len_;
public:
	restaurant() = delete;
	restaurant(int len){
		len_ = len;
		clocks_ = new int*[len_];
		for (int i = 0; i < len_; i++){
			clocks_ = new int[0];
		}
	}
	~restaurant(){
		for (int i = 0; i < len_; i++){
                        delete[] clocks_;
                }
		delete[] clocks_;
	}
}

class Restaurant_Exception {
	int code_;
	std::string message_;
public:
	Restaurant_Exception(int code, const std::string& message) : code_(code), message_(message) {}
	const std::string& message() const { return message_; }
	int code() const { return code_; }
};
