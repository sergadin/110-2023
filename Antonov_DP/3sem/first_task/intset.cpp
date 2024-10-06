
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
		set_[i] = 0;
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
	set_[elem - left_] = 1;
}

void intset::del(const int elem) {
	if ((elem > right_) || (elem < left_)) {
		throw Intset_Exception(-1, "elem not in range of set");
	}
	set_[elem - left_] = 0;
}

bool intset::is_empty() const {
	for (int i = 0; i < right_ - left_ + 1; i++)
	{
		if (set_[i] != 0) {
			return false;
		}
	}
	return true;
}

int intset::len() const{
	int len = 0;
	for (int i = 0; i < right_ - left_ + 1; i++)
	{
		len += set_[i];
	}
	return len;
}

int intset::max() const{
	if (this->is_empty()) {
		return (right_ + 1);
	}
	for (int i = right_ - left_; i > -1; i--)
	{
		if (set_[i]) {
			return (left_ + i);
		}
	}
	return 0;
}

int intset::min() const{
	if (this->is_empty()) {
		return (left_ - 1);
	}
	for (int i = 0; i < right_ - left_ + 1; i++)
	{
		if (set_[i]) {
			return (i + left_);
		}
	}
	return 0;
}

int intset::left() const{
	return left_;
}

int intset::right() const{
	return right_;
}

intset& intset::operator=(const intset& other) {
	if (this == &other) {
		return *this;
	}
	delete[] set_;
	left_ = other.left_;
	right_ = other.right_;
	set_ = new int[right_ - left_ + 1];
	for (int i = 0; i < right_ - left_ + 1; i++)
	{
		set_[i] = other.set_[i];
	}
	return *this;
}

intset operator*(const intset& other1, const intset& other2) {
	if ((other1.right_ < other2.left_) || (other1.left_ > other2.right_))
	{
		intset temp(std::min(other1.left_, other2.left_), std::max(other1.right_, other2.right_));
			return temp;
	}
	intset temp(std::max(other1.left_, other2.left_), std::min(other1.right_, other2.right_));
	for (int i = 0; i < temp.right_ - temp.left_ + 1; i++) {
		if ((other1.set_[i + (temp.left_ - other1.left_)]) && (other2.set_[i + (temp.left_ - other2.left_)])) {
			temp.set_[i] = 1;
		}
		else {
			temp.set_[i] = 0;
		}
	}
	return temp;
}

intset operator*=(intset& ours, const intset& other) {
	ours = ours * other;
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
