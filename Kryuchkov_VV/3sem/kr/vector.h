#include <stdio.h>
#include <iostream>

class Vector{
  private:
  int N_;
  int *vect_ = nullptr;
  int Nsize_;
  public:
  explicit Vector();
  Vector(int N, int size);
  Vector(const Vector &vct);
  ~Vector(){
    delete[] vect_;
    N_ = 0;
    Nsize_ = 0;
  }
  
  void writeLoc();
  void writeInc(const Vector &vct);
  
  Vector& operator=(const Vector &vct);
  bool operator<(const Vector &vct);
  void printVect();

};

class Error{
  private: 
  int code_;
  std::string message_;
  public:
  Error(int code, std::string message){
    code_ = code;
    message_ = message;
  }
  std::string get_mes(){
    return message_;
  }
};
