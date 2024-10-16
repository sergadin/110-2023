#include "polinom.h"
using namespace std;

int main(void){
  try{
    Polinom p1(5), p2(5), p3(3);
    
    p1.PutCoef(0, 4); p1.PutCoef(1,5); p1.PutCoef(2, 1); p1.PutCoef(5, 15);
    p2.PutCoef(1,6); p2.PutCoef(3, 14); p2.PutCoef(4, -4.6); p2.PutCoef(5, 21);
    p3.PutCoef(0,3); p3.PutCoef(2, 12);
    printf("Hello!\n");
    Polinom p4(p3);
    printf("Polinom 1: ");
    p1.printPol();
    printf("Polinom 2: ");
    p2.printPol();
    printf("New polinom 1: ");
    p1 = p3+p1;
    p1.printPol();
    printf("Another new polinom 1: ");
    p1 = p1+ p3;
    p1.printPol();
    p2.PutCoef(8, 9);
  }catch(Error &err){
    cout << "EXEPTION: " << err.get_reason() << "\n";
  }catch(...){
    cout << "Idk what is wrong. It's not my problem\n";
  }
  return 0;
}
