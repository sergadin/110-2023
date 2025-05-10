#include <iostream>
#include <cstring>

#ifndef student_h
#define student_h


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
		info_ = (char *)"";
		strcpy(info_, info);
	}
	~student();
	void print(){
		std::cout << "name: " << name_ << "\n";
		std::cout << "group: " << group_ << "\n";
		std::cout << "rating: " << rating_ << "\n";
		std::cout << "info: " << info_ << "\n";
	}
};

#endif
