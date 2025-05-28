#include <iostream>
#include <cstring>


class student {
public:
	char name_[64];
	int group_;
	double rating_;
	char *info_;
	student() = delete;
	student(const char *name, int group, double rating, const char *info = ""){
		strncpy(name_, name, 64);
		group_ = group;
		rating_ = rating;
		info_ = new char[strlen(info)];
		info_ = strcpy(info_, info);
	}
	~student(){
		delete[] info_;
	}
	student(const student& other){
                strncpy(name_, other.name_, 64);
                group_ = other.group_;
                rating_ = other.rating_;
                info_ = new char[strlen(other.info_)];
                info_ = strcpy(info_, other.info_);
        }
	student &operator=(const student& other){
		if (this == &other) { return *this; }
		delete[] info_;
		strncpy(name_, other.name_, 64);
                group_ = other.group_;
                rating_ = other.rating_;
                info_ = new char[strlen(other.info_)];
                info_ = strcpy(info_, other.info_);
	}
	void print(){
		std::cout << "name: " << name_ << "\n";
		std::cout << "group: " << group_ << "\n";
		std::cout << "rating: " << rating_ << "\n";
		std::cout << "info: " << info_ << "\n";
	}
};
