#include "polinom.h"

using namespace std;
static double power(double x, int deg){
  double num = 1;
  if(deg<0){
    throw Error(-3, string("wrong deg\n"));
  }
  if (deg == 0){
  return 1;
  }
  for(int i = 0; i < deg; i++){
    num*=x;
  }
  return num;
}

Polinom::Polinom(const Polinom &p){
  if(Deg_ !=-1){
  delete[] pol_;
  }
  Deg_ = p.Deg_;
  pol_ = new double[Deg_+1];
  if(pol_ == nullptr){
      throw Error(-2, std::string("Memory error\n"));
    }
  for (int i = 0; i < Deg_+1; i++){
    pol_[i] = p.pol_[i];
  }
}
double Polinom::PolVal(double x){
  double val = 0;
  for(int i = 0; i < Deg_+1; i++){
    val+=(power(x,i)*pol_[i]);
  }
  return val;
}
double Polinom::GetCoef(int deg){
if(deg < 0){
  throw Error(-3, string("wrong deg\n"));
}
if(deg > Deg_){
  throw Error(-1, string("Wrong degree\n"));
}
  return (pol_[deg]);
}
void Polinom::PutCoef(int deg, double coef){
  if(deg < 0){
  throw Error(-3, string("wrong deg\n"));
}
if(deg > Deg_){
  throw Error(-1, string("Wrong degree\n"));
}
  pol_[deg] = coef;
}

Polinom& Polinom::operator=(const Polinom &other){
  if(pol_ == other.pol_){
    return *this;
  }
  Deg_ = other.Deg_;
  delete[] pol_;
  pol_ = new double[Deg_+1];
  for (int i = 0; i < Deg_+1; i++){
    pol_[i] = other.pol_[i];
  }
  return *this;
}

Polinom& Polinom::operator+=(const Polinom &other){
  Polinom pol(1);
  if(other.Deg_ > Deg_){
  pol = other;
    for(int i = 0; i < Deg_+1; i++){
      pol.pol_[i] += pol_[i];
    }
  }else{
  pol = *this;
    for(int i = 0; i < other.Deg_+1; i++){
      pol.pol_[i] += other.pol_[i];
    }
    
  }
  *this = pol;
  return *this;
}
  
Polinom Polinom::operator+(const Polinom &other){
  Polinom tmp = *this;
  tmp+= other;
  return tmp;
  }


