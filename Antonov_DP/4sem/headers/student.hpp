#include <iostream>
#include <cstring>


class student {
	char name_[64];
	int group_;
	double rating_;
	char *info_;
public:
	student() = delete;
	student(const char *name, int group, double rating, const char *info = ""){
		strncpy(name_, name, 64);
		group_ = group;
		rating_ = rating;
		info_ = new char[strlen(info)];
		strcpy(info_, info);
	}
	~student(){
		delete[] info_;
	}
	void print(){
		std::cout << "name: " << name_ << "\n";
		std::cout << "group: " << group_ << "\n";
		std::cout << "rating: " << rating_ << "\n";
		std::cout << "info: " << info_ << "\n";
	}
};
