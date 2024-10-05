#include <iostream>
#include "polynom.h"

polynom::polynom(int ord){
	if (ord < 0){
		ord_ = 0;
	}
	ord_ = ord;
	pol_ = new double[ord_ + 1];
	for(int i = 0; i < ord_ + 1; i++){
		pol_[i] = 0;
	}
}

polynom::~polynom(){
	delete[] pol_;
}

polynom::polynom(const polynom& other){
	pol_ = new double[0];
	*this = other;
}

polynom &polynom::operator=(const polynom& other){
	if (this == &other){ return *this; }
	delete[] pol_;
	ord_ = other.ord_;
	pol_ = new double[ord_ + 1];
	for (int i = 0; i < ord_ + 1; i++){
		pol_[i] = other.pol_[i];
	}
	return *this;
}

double polynom::calc(const double &x){
	double temp = 1, res = 0;
	for (int i = 0; i < ord_ + 1; i++){
		res = pol_[i] * temp;
		temp *= x;
	}
	return res;
}

double polynom::coef_deg(const int &n){
	if((n > ord_) || (n < 0)){
		throw Polynom_Exception(-1, "out of range");
	}
	return pol_[n];
}

void polynom::change(const double &a, const int &n){
	if((n > ord_) || (n < 0)){
                throw Polynom_Exception(-1, "out of range");
        }
	pol_[n] = a;
}

int polynom::deg(){
	return ord_;
}

polynom operator+(const polynom& other1, const polynom& other2){
	polynom res(std::max(other1.ord_, other2.ord_));
	for (int i = 0; i < res.ord_; i++){
		if(i <= other1.ord_){
			res.pol_[i] += other1.pol_[i];
		}
		if(i <= other2.ord_){
                        res.pol_[i] += other2.pol_[i];
                }
	}
	return res;
}
