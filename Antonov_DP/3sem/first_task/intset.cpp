#include <iostream>
#include "intset.h"

intset::intset(int left, int right){
	if (left > right){
		throw Intset_Exception(-1, "left > right");
	}
	left_ = left;
	right_ = right;
	set_ = new int[right - left + 1];
	for (int i = left; i < right + 1; i++){
		set_[i] = left - 1;
	}
}

intset::intset(const intset &other){
	left_ = other.left_;
	right_ = other.right_;
	set_ = new int[right_ - left_ + 1];
	for (int i = left_; i < right_ + 1; i++)
	{
		set_[i] = other.set_[i];
	}
}

intset::~intset(){
	left_ = 0;
	right_ = 0;
	delete[] set_;
}

void intset::add(const int elem){
	if ((elem > right_) || (elem < right_)){
		throw Intset_Exception(-2, "elem not in range of set");
	}
	if (set_[elem - left_] != (left_ - 1)){
		return;
	}
	set_[elem - left_] = elem;
}

void intset::del(const int elem){
	if ((elem > right_) || (elem < right_)){
                throw Intset_Exception(-2, "elem not in range of set");
        }
	if (set_[elem - left_] == (left_ - 1)){
		set_[elem - left_] = (left_ - 1);
        }
}

bool intset::check(){
	for (int i = left_; i < right_ + 1; i++)
	{
		if (set_[i] != (left_ - 1)){
			return true;
		}
	}
	return false;
}

int intset::len(){
	int len = 0;
	for (int i = left_; i < right_ + 1; i++)
        {
                if (set_[i] != (left_ - 1)){
                        len ++;
                }
        }
	return len;
}

int intset::max(){
	if (!(this->check())){
		throw Intset_Exception(-3, "set is empty");
	}
	for (int i = right_; i > left_ - 1; i--)
        {
                if (set_[i] != (left_ - 1)){
                        return set_[i];
                }
        }
	return 0;
}

int intset::min(){
        if (!(this->check())){
                throw Intset_Exception(-3, "set is empty");
        }
        for (int i = left_; i < right_ + 1; i++)
        {
                if (set_[i] != (left_ - 1)){
                        return set_[i];
                }
        }
        return 0;
}

int intset::left(){
        return left_;
}

int intset::right(){
        return right_;
}

intset &intset::operator=(const intset &other){
	if (this == &other){
		exit(-1);
	}
	intset temp(other.left_, other.right_);
        temp.left_ = other.left_;
        temp.right_ = other.right_;
        temp.set_ = new int[right_ - left_ + 1];
        for (int i = temp.left_; i < temp.right_ + 1; i++)
        {
                temp.set_[i] = other.set_[i];
        }
	return &temp;
}

intset operator*(const intset &other1, const intset &other2){
	intset temp(other.left_, other.right_);
	if ((other1.right_ < other2.left_) || (other1.left_ > other2.right_))
	{
		throw Int_Exception(-4, "not interect");
	}
	if(other1.left_ > other2.left_){
		temp.left = other1.left_;
	}
	else{
		temp.left = other2.left_;
	}
	if(other1.right_ > other2.right_){
                temp.left = other2.right_;
        }
        else{
                temp.left = other1.right_;
        }
	for (int i = temp.left_; i < temp.right_; i++){
		if (other1.set_[i] == other2.set_[i]){
			temp.set_[i] = other1.set_[i];
		}
		else{
			temp.set_[i] = temp.left_ - 1;
		}
	}
	return temp;
;

bool operator==(const intset &other1, const intset &other2){
	if (other1.left_ != other2.left_){
		return false;
	}
	if (other1.right_ != other2.right_){
                return false;
        }
	for (int i = other1.left_; i < other1.right_; i++){
                if (other1.set_[i] != other2.set_[i]){
                        return false
                }
        }
	return true;
}

