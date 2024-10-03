#include <iostream>
#include "intset.h"

intset::intset(int left, int right) {
	if (left > right) {
		throw Intset_Exception(-1, "left > right");
	}
	left_ = left;
	right_ = right;
	set_ = new int[right - left + 1];
	for (int i = 0; i < right - left + 1; i++) {
		set_[i] = left - 1;
	}
}

intset::intset(const intset& other) {
	left_ = other.left_;
	right_ = other.right_;
	set_ = new int[right_ - left_ + 1];
	for (int i = 0; i < right_ - left_ + 1; i++)
	{
		set_[i] = other.set_[i];
	}
}

intset::~intset() {
	left_ = 0;
	right_ = 0;
	delete[] set_;
}

void intset::add(const int elem) {
	if ((elem > right_) || (elem < left_)) {
		throw Intset_Exception(-1, "elem not in range of set");
	}
	set_[elem - left_] = elem;
}

void intset::del(const int elem) {
	if ((elem > right_) || (elem < left_)) {
		throw Intset_Exception(-1, "elem not in range of set");
	}
	set_[elem - left_] = (left_ - 1);
}

bool intset::check() {
	for (int i = 0; i < right_ - left_ + 1; i++)
	{
		if (set_[i] != (left_ - 1)) {
			return true;
		}
	}
	return false;
}

int intset::len() {
	int len = 0;
	for (int i = 0; i < right_ - left_ + 1; i++)
	{
		if (set_[i] != (left_ - 1)) {
			len++;
		}
	}
	return len;
}

int intset::max() {
	if (!(this->check())) {
		return right_ + 1;
	}
	for (int i = right_ - left_; i > -1; i--)
	{
		if (set_[i] != (left_ - 1)) {
			return set_[i];
		}
	}
	return 0;
}

int intset::min() {
	if (!(this->check())) {
		return left_ - 1;;
	}
	for (int i = 0; i < right_ - left_ + 1; i++)
	{
		if (set_[i] != (left_ - 1)) {
			return set_[i];
		}
	}
	return 0;
}

int intset::left() {
	return left_;
}

int intset::right() {
	return right_;
}

intset& intset::operator=(const intset& other) {
	if (this == &other) {
		return *this;
	}
	left_ = other.left_;
	right_ = other.right_;
	set_ = new int[right_ - left_ + 1];
	for (int i = 0; i < right_ - left_ + 1; i++)
	{
		set_[i] = other.set_[i];
	}
	return *this;
}

intset operator*(const intset &other1, const intset &other2) {
	intset temp(other1.left_, other1.right_);
	if ((other1.right_ < other2.left_) || (other1.left_ > other2.right_))
	{
		throw Intset_Exception(-1, "not intersect");
	}
	if (other1.left_ < other2.left_) {
		temp.left_ = other2.left_;
	}
	if (other1.right_ > other2.right_) {
		temp.right_ = other2.right_;
	}
	for (int i = 0; i < temp.right_ - temp.left_ + 1; i++) {
		if (other1.set_[i + (temp.left_ - other1.left_)] == other2.set_[i + (temp.left_ - other2.left_)]) {
			temp.set_[i] = other1.set_[i + (temp.left_ - other1.left_)];
		}
		else {
			temp.set_[i] = temp.left_ - 1;
		}
	}
	return temp;
}

intset operator*=(intset &ours, const intset &other){
	int left, right;
	if (ours.left_ < other.left_){left = other.left_;}
	else {left = ours.left_;}
	if (ours.right_ > other.right_){right = other.right_;}
        else {right = ours.right_;}
	for(int i = 0; i < (right - left + 1); i++){
		if(ours.set_[i + (left - ours.left_)] != other.set_[i + (left - other.left_)]){
			ours.set_[i + (left - ours.left_)] = ours.left_ - 1;
		}
	}
	return ours;
}

bool operator==(const intset& other1, const intset& other2) {
	if ((other1.left_ != other2.left_) || (other1.right_ != other2.right_)) {
		return false;
	}
	for (int i = 0; i < other1.right_ - other1.left_ + 1; i++) {
		if (other1.set_[i] != other2.set_[i]) {
			return false;
		}
	}
	return true;
}
