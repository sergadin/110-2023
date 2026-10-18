#include <stdio.h>
#include <iostream>
class Error{
  private:
  int code_;
  std::string reason_;
  public:
  Error(int code, std::string reason){
    code_ = code;
    reason_ = reason;
  }
  std::string get_reason(){
    return reason_;
  }
};

class Polinom{
  private:
  int Deg_ = -1;
  double *pol_ = nullptr;
  public:
  explicit Polinom();
  Polinom(int Deg){
    if(Deg<0){
      throw Error(-1, std::string("Wrong degree\n"));
    }
    Deg_ = Deg;
    pol_ = new double[Deg_+1];
    if(pol_ == nullptr){
      throw Error(-2, std::string("Memory error\n"));
    }
    for(int i = 0; i < Deg_+1; i++){
      pol_[i] = 0;
    }
  }
  Polinom(const Polinom &p);
  ~Polinom(){
    delete[] pol_;
    Deg_ = 0;
  }
  
  double PolVal(double x);
  double GetCoef(int deg);
  void PutCoef(int deg, double coef);
  
  Polinom operator+(const Polinom &other);
  Polinom &operator+=(const Polinom &other);
  Polinom &operator=(const Polinom &other);
  
  void printPol(){
    for (int i = 0; i < Deg_+1; i++){
      std::cout << pol_[i] << " ";
    }
    std::cout << "\n";
  }
  
};


