#include <string>
#include "intset.h"

using namespace std;
int main(void){
  try{
  Sets s1(-1, 15), s2(10,14), s3(0, 4), s4(0, 2);
  
  s1.put(0);
  s1.put(4);
  s1.put(5);
  s1.put(10);
  s1.put(15);
  s2.put(10);
  s2.put(11);
  s2.put(14);
  s3.put(0);
  s3.put(2);
  s3.put(4);
  cout << "Is s4 empty?\n" << (s4.is_empty()) << endl;
  s4 = s2;
  printf("%d %d - size\n", s4.get_size(), s2.get_size());
  cout << "Is s4 equal to s4?\n" << (s4==s4) << endl;
  cout << "Is s4 equal to s2?\n" << (s4==s2) << endl;
  s2.put(11);
  cout << "Is s4 equal to s2?\n" << (s4==s2) << endl;
  s2.put(13);
  printf("s4 is: ");
  s4.print();
  cout << "Is s4 equal to s2?\n" << (s4==s2) << endl;
  s4 *= s2;
  printf("s4 is: ");
  s4.print();
  cout << "Is s4 equal to s2?\n" << (s4==s2) << endl;
  s4 = s3*s1;
  s4=s4;
  printf("s1 is: ");
  s1.print();
  printf("s2 is: ");
  s2.print();
  printf("s3 is: ");
  s3.print();
  printf("s4 is: ");
  s4.print();
  s4.put(100);
  }catch(Error &err){
    cout << "EXEPTION: " << err.get_mes() << endl;
  }catch(...){
    printf("Something wrong\n");
  }
  return 0;
}

