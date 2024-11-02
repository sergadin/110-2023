#include "hashTable.h"
#include <cstdlib>
#include <ctime>
#include <random>
#include <fstream>
#include <sstream>
#include <cassert>

#define eps 1e-6
int gen_rnd_val_int(); //генератор случайных значений (целочисленный)
std::string gen_rnd_key(); //генератор случайных ключей
double gen_rnd_val_double();
HashTbl<int> gen_rnd_set_int(int sz);
HashTbl<double> gen_rnd_set_double(int sz);
HashTbl<std::string> gen_rnd_set_string(int sz);
void gen_rnd_set(int sz); //генератор случайных множеств

int gen_rnd_val_int(){
  std::random_device rd; //можно обращаться к темплейтному методу и через него все генерировать. T::метод
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(1, 100);
  
  return dist(gen);
}

std::string gen_rnd_key(){
  const std::string chars = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890";
  const int k_sz = gen_rnd_val_int()%15;
  
  std::random_device rd; //генератор случайных чисел
  std::mt19937 gen(rd()); //инициализация генератора случайных чисел
  std::uniform_int_distribution<> dist(0, chars.size() - 1);//равномерное распределение значений
  
  //std::string key(k_sz, ' ');
  std::string key;
  key.resize(k_sz);
  for (int i = 0; i < k_sz; ++i){
    key[i] = chars[dist(gen)];
  }
  //std::cout << "My " << key << std::endl;
  return key;
}

double gen_rnd_val_double() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(1.0, 100.0);

    return dist(gen);
}

HashTbl<int> gen_rnd_set_int(int sz){
  HashTbl<int> table;
  for (int i = 0; i < sz; ++i){
    std::string k = gen_rnd_key();
    int v = gen_rnd_val_int();
    //std::cout << "Key: " << k << " Value: " << v << std::endl;
    if (k.empty()){
      continue;
    }
    table.add(k, v);
  }

  return table;
}

HashTbl<double> gen_rnd_set_double(int sz) {
    HashTbl<double> table;
    for (int i = 0; i < sz; ++i) {
        std::string k = gen_rnd_key();
        double v = gen_rnd_val_double();
        table.add(k, v);
    }
    return table;
}

HashTbl<std::string> gen_rnd_set_string(int sz) {
    HashTbl<std::string> table;
    for (int i = 0; i < sz; ++i) {
        std::string k = gen_rnd_key();
        std::string v = gen_rnd_key();
        table.add(k, v);
    }
    return table;
}

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

int main(void){
try{
  HashTbl<int> h1;
  // Проверка добавления и получения значений
  h1.add("ключ1", 10);
  h1.add("ключ2", 20);
  h1.add("ключ3", 30);
  assert(h1.get("ключ1") == 10);
  printf("Good!\n");
  assert(h1.get("ключ2") == 20);
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
    if(!(*it).first.empty()){
      std::cout << "Ключ: " << (*it).first << ", значение: " << (*it).second << std::endl;
    }
  }
}catch(HashEr &err){
  std::cout << "Error was catched - " << err.getMes() << std::endl;
}catch(...){
  std::cout << "Something wrong" << std::endl;
}
  try{
    HashTbl<double> t_dbl;
    t_dbl.readFile("hashDouble.txt");
    printf("\n");
    t_dbl.add("str4", 2.7);
    assert(fabs(t_dbl.get("str4") - 2.7) < eps);
    t_dbl.remove("str3");
    std::cout << "Проверка итератора:\n";
    for (auto it = t_dbl.begin(); it != t_dbl.end(); ++it) {
      if(!(*it).first.empty()){
      std::cout << "Ключ: " << (*it).first << ", значение: " << (*it).second << std::endl;
    }
    }
  }catch(HashEr &err){
    std::cout << "This is Error " << err.getMes() << std::endl;
  }catch(...){
    std::cout << "Another Error" << std::endl;
  }
  
  try{
    HashTbl<int> t_dbl;
    t_dbl.readFile("strangeHash.txt");
    printf("\n");
    printf("Succesful file openning\n");
  }catch(HashEr &err){
    std::cout << "This is bad Error " << err.getMes() << std::endl;
  }catch(...){
    std::cout << "Another Error" << std::endl;
  }
  
  try{ // Добавление строк
  HashTbl<std::string> h2;
  printf("\n");
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
    if(!(*it).first.empty()){
      std::cout << "Ключ: " << (*it).first << ", значение: " << (*it).second << std::endl;
    }
  }
}catch(HashEr &err){
    std::cout << "This is new Error " << err.getMes() << std::endl;
  }catch(...){
    std::cout << "Not written Error" << std::endl;
  }
  try {
  HashTbl<std::string> h2;
  h2.get("key3");
  printf("\n");
  std::cout << "Test FAILED" << std::endl;
  }catch(HashEr &er){
      if (er.getCode() != -1){
          std::cout << "Test FAILED" << std::endl;
      }else{
        std::cout << "Test passed" << std::endl;
      }
  }
  
  try{
  printf("\n");
    HashTbl<int> int_hash_table = gen_rnd_set_int(10);
    int_hash_table.add("key2", 24);
    std::cout << "Проверка итератора:\n";
    for (auto it = int_hash_table.begin(); it != int_hash_table.end(); ++it) {
      if(!(*it).first.empty()){
      std::cout << "Ключ: " << (*it).first << ", значение: " << (*it).second << std::endl;
    }
  }
  }catch(HashEr &err){
    std::cout << "This is bad Error " << err.getMes() << std::endl;
  }catch(...){
    std::cout << "Another Error" << std::endl;
  }
  
    try{
  printf("\n");
    HashTbl<std::string> str_hash_table = gen_rnd_set_string(10);
    str_hash_table.add("key2", "str");
    std::cout << "Проверка итератора:\n";
    for (auto it = str_hash_table.begin(); it != str_hash_table.end(); ++it) {
      if(!(*it).first.empty()){
      std::cout << "Ключ: " << (*it).first << ", значение: " << (*it).second << std::endl;
    }
  }
  }catch(HashEr &err){
    std::cout << "This is bad Error " << err.getMes() << std::endl;
  }catch(...){
    std::cout << "Another Error" << std::endl;
  }
  return 0;
}
