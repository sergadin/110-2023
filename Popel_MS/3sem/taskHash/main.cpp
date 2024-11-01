#include "hashTable.h"
#include <cstdlib>
#include <ctime>
#include <random>
#include <fstream>
#include <sstream>
#include <cassert>
/*
 static double max(double x, double y, double eps);
 
  static double max(double x, double y, double eps){
    double max_1 = x;
    if(x>y){
      max_1 = x;
    }else{
      max_1 = y;
    }
    if (eps > max_1){
      return eps;
    }
    return max_1;
  }*/
/*class ExampleClass{
  public:
    int number;
    
    ExampleClass(int n) : number(n) {}
};*/
/*template <typename T>
struct TestCase{
  const std::string type;
  std::vector<std::string> key;
  std::vector<T> exp_val;
};
TestCase<int> intTests[] = {
  {"int", {"ключ1", "ключ2", "ключ3"}, {10, 20, 30}}
};

TestCase<std::string> stringTests[] = {
  {"std::string", {"ключ1", "ключ2", "ключ3", "ключ4"}, {"abc", "names", "stack", "keys"}}
};

TestCase<double> doubleTests[] = {
  {"double", {"ключ1", "ключ2"}, {12.4, 0.22}}
};*/
int main(void){
  HashTbl<int> h1;
  //HashTbl<std::string> h2;
  // Проверка добавления и получения значений
  h1.add("ключ1", 10);
  h1.add("ключ2", 20);
  h1.add("ключ3", 30);
  if(h1.get("ключ1") == 10){
    printf("Good!\n");
  }
  /*assert(h1.get("ключ2") == 20);
  assert(h1.get("ключ3") == 30);

  // Проверка размера хэш-таблицы
  assert(h1.size() == 3);

  // Проверка удаления элементов
  h1.remove("ключ2");
  assert(h1.size() == 2);
  assert(h1.get("ключ1") == 10);
  assert(h1.get("ключ3") == 30);

  // Проверка rehash
  h1.add("ключ4", 40);
  h1.add("ключ5", 50);
  h1.add("ключ6", 60);
  assert(h1.size() == 5);

  // Проверка итератора
  std::cout << "Проверка итератора:\n";
  for (auto it = h1.begin(); it != h1.end(); ++it) {
    std::cout << "Ключ: " << (*it).first << ", значение: " << (*it).second << std::endl;
  }

  // Добавление строк
  h2.add("ключ1", "значение1");
  h2.add("ключ2", "значение2");
  h2.add("ключ3", "значение3");

  // Проверка получения значений
  assert(h2.get("ключ1") == "значение1");
  assert(h2.get("ключ2") == "значение2");
  assert(h2.get("ключ3") == "значение3");

  // Проверка размера
  assert(h2.size() == 3);

  // Проверка удаления
  h2.remove("ключ2");
  assert(h2.size() == 2);
  assert(h2.get("ключ1") == "значение1");
  assert(h2.get("ключ3") == "значение3");

  // Проверка итератора
  std::cout << "Проверка итератора:\n";
  for (auto it = h2.begin(); it != h2.end(); ++it) {
    std::cout << "Ключ: " << (*it).first << ", значение: " << (*it).second << std::endl;
  }*/

  return 0;
}
