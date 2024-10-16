#ifndef CLOCK_H
#define CLOCK_H

#include <iostream>

class Vector {
	private:
		int N_; 
		int* vect_;
		int Nsize_; 

	public:
		Vector();
		Vector(int N, int size);
		Vector(const Vector& vct); 
		~Vector();

		void updateLocation();
		void updateIncrement(const Vector& vct); 

		Vector& operator=(const Vector& vct);
		bool operator<(const Vector& vct);
		void printVector();
};

class Error {
	private:
		int code_;
		std::string message_;

	public:
		Error(int code, std::string message);
		std::string get_mes();
};

#endif

