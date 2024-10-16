#include <iostream>
#include "test.h"
using namespace std;

vector::vector(double *a = 0, int len = 0){
	if ((a == 0) || (len == 0)){
		len_ = 1;
		new double arr_[1];
		arr_[0] = 0;
	}
	len_ = len;
	new double arr_[len_];
	for (int i = 0; i < len; i++){
		arr_[i] = a[i];
	}
}

vectro::vector(const vector &other){
	len_ = other.len_;
	new arr_[len_];
	for(int i = 0; i < len; i++){
		arr_[i] = other.arr_[i];
	}
	return *this;
}

vector::~vector(){
	delete[] arr_;
	len = 0;
}

vector::set_vector(double *a = 0, int len = 0){
	delete[] arr_;
	if ((a == 0) || (len == 0)){
                len_ = 1;
                new double arr_[1];
                arr_[0] = 0;
        }
	len_ = len;
        new double arr_[len_];
        for (int i = 0; i < len; i++){
                arr_[i] = a[i];
        }
}

double *vector::get_vector(){
	new double arr[len_];
	for (int i = 0; i < len_; i++){
		arr[i] = arr_[i];
	}
	return arr;
}

int vector::get_len(){
	return len_;
}

vector::show_vector(){
	cout << "[";
	for (int i = 0; i < len_ - 1 ;i++){
		cout << arr_[i] << " ,";
	}
	cout << arr_[len - 1] << "]";
}

vector &vector::operator+(const vector &other){
	if(this == &other) return *this;
        delete[] arr_;
        len_ = other.len_;
        new arr_[len_];
        for(int i = 0; i < len; i++){
                arr_[i] = other.arr_[i];
        }
        return *this;
}

vector &operator+(const vector &other1, const vector &other2){
	if (other1.len_ != other2.len_) throw different_len;
	len_ = other1.len;
	new double arr_[len_];
	for (int i = 0; i < len_; i++){
		arr_[i] = other1.arr_[i] + other2.arr_[i];
	}
	return *this;
}

vector &operator-(const vector &other1, const vector &other2){
	if (other1.len_ != other2.len_) throw different_len;
        len_ = other1.len;
        new double arr_[len_];
        for (int i = 0; i < len_; i++){
                arr_[i] = other1.arr_[i] - other2.arr_[i];
        }
        return *this;
}

vector &operator*(const double &n, const vector &other){
	len_ = other.len_;
	new double arr_[len_];
	for(int i = 0; i < len_; i++){
		arr_[i] = n * other.arr_[i];
	}
	return *this;
}

double vector::scal(const vector &other1, const vector &other2){
	if (other1.len_ != other2.len_) throw different_len;
	double temp = 0;
	for (int i = 0; i < other1.len_; i++){
		temp += other1.arr[i] * other2.arr_[i];
	}
	return temp;
}
