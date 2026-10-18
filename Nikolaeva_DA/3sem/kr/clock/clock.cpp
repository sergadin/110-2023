#include "clock.h"
#include <iostream>

using namespace std;

Vector::Vector() {
	N_ = 0;
	Nsize_ = 0;
	vect_ = nullptr;
}

Vector::Vector(int N, int size) {
	if ((N <= 0) || (size < 0) || (N <= size)) {
		throw Error(-1, string("wrong size"));
	}
	N_ = N;
	Nsize_ = size;
	vect_ = new int[N];
	for (int i = 0; i < N; i++) {
		vect_[i] = 0;
	}
}

Vector::Vector(const Vector& vct) { 
	N_ = vct.N_;
	Nsize_ = vct.Nsize_;
	vect_ = new int[N_];
	for (int i = 0; i < N_; i++) {
		vect_[i] = vct.vect_[i];
	}
}

Vector::~Vector() {
	if (vect_ != nullptr) {
		delete[] vect_;
	}
	N_ = 0;
	Nsize_ = 0;
}

void Vector::updateLocation() {
	vect_[Nsize_]++;
}

void Vector::updateIncrement(const Vector& vct) {
	if (N_ != vct.N_) {
		throw Error(-2, std::string("wrong process' number"));
	}
	vect_[Nsize_]++;
	for (int i = 0; i < N_; i++) {
		if (vect_[i] < vct.vect_[i]) {
			vect_[i] = vct.vect_[i];
		}
	}
}

Vector& Vector::operator=(const Vector& vct) {
	if (this == &vct) { 
		return *this;
	}
	if (N_ != vct.N_) {
		throw Error(-2, std::string("wrong process' number"));
	}
	delete[] vect_;
	N_ = vct.N_;
	Nsize_ = vct.Nsize_;
	vect_ = new int[N_];
	for (int i = 0; i < N_; i++) {
		vect_[i] = vct.vect_[i];
	}
	return *this;
}

bool Vector::operator<(const Vector& vct) { 
	if (N_ != vct.N_) {
		throw Error(-2, std::string("wrong process' number"));
	}
	bool lessThan = false;
	for (int i = 0; i < N_; i++) {
		if (vect_[i] > vct.vect_[i]) {
			return false;
		} else if (vect_[i] < vct.vect_[i]) {
			lessThan = true;
		}
	}
	return lessThan;
}

void Vector::printVector() {
	for (int i = 0; i < N_; i++) {
		cout << vect_[i] << " ";
	}
	cout << "\n";
}

Error::Error(int code, std::string message) {
	code_ = code;
	message_ = message;
}

std::string Error::get_mes() {
	return message_;
}
