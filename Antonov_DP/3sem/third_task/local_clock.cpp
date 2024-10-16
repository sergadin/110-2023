#include <iostream>
#include "local_clock.h"

void local_clock::iteration(size_t &k, std::string a, std::ostream &stream){
	if (k > len_) {
		throw local_clock_Exception(-1, "out of range");
	}
	local_clock_[k] += 1;
	stream << a;
}

void local_clock::get_message(const local_clock &other, std::string a, std::ostream &stream){
	if(len_ != other.len_){
                throw local_clock_Exception(-1, "size are not equal");
        }
	stream << a;
	for (size_t i = 0; i < len_; i++){
		local_clock_[i] = std::max(local_clock_[i], other.local_clock_[i]);
	}
	stream << "acceptor hear" << a;
}

bool operator<(const local_clock &other1, const local_clock &other2){
	if (other1.len_ != other2.len_){
		throw local_clock_Exception(-1, "size are not equal");
	}
        int count = 0;
        for (size_t i = 0; i < other1.len_; i++){
                if (other1.local_clock_[i] > other2.local_clock_[i]){
                	return false;
                }
        	else { count++; }
        }
	if (count > 0){ return true; }
	return false;
}

int *local_clock::get_vector(){
	int *res;
	res = new int[len_];
	for (size_t i = 0; i < len_; i++){
		res[i] = local_clock_[i];
	}
	return res;
}
