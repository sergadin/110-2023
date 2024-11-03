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
double gen_rnd_val_double(); //генератор случайных значений (double)
HashTbl<int> gen_rnd_set_int(int sz); //генератор случайных множеств (целочисленный)
HashTbl<double> gen_rnd_set_double(int sz); //генератор случайных множеств (double)
HashTbl<std::string> gen_rnd_set_string(int sz); //генератор случайных множеств (строки)

int gen_rnd_val_int(){
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(1, 100);
  
  return dist(gen);
}

std::string gen_rnd_key(){
  const std::string chars = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890";
  const int k_sz = (gen_rnd_val_int() % 15) + 1;
  
  std::random_device rd; //генератор случайных чисел
  std::mt19937 gen(rd()); //инициализация генератора случайных чисел
  std::uniform_int_distribution<> dist(0, chars.size() - 1);//равномерное распределение значений
  
  //std::string key(k_sz, ' ');
  std::string key;
  key.resize(k_sz);
  for (int i = 0; i < k_sz; ++i){
    key[i] = chars[dist(gen)];
  }
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

int main(void){
try{
  HashTbl<int> h1;
  // Проверка добавления и получения значений
  h1.add("ключ1", 10);
  h1.add("ключ2", 20);
  h1.add("ключ3", 30);
  
  assert(h1.get("ключ1") == 10);
  std::cout << "Тест 1 пройден." << std::endl;
  assert(h1.get("ключ2") == 20);
  std::cout << "Тест 2 пройден." << std::endl;
  assert(h1.get("ключ3") == 30);
  std::cout << "Тест 3 пройден." << std::endl;
  // Проверка размера хэш-таблицы
  assert(h1.size() == 3);
  std::cout << "Тест 4 пройден." << std::endl;

  // Проверка удаления элементов
  h1.remove("ключ2");
  assert(h1.size() == 2);
  std::cout << "Тест 5 пройден." << std::endl;
  assert(h1.get("ключ1") == 10);
  std::cout << "Тест 6 пройден." << std::endl;
  assert(h1.get("ключ3") == 30);
  std::cout << "Тест 7 пройден." << std::endl;

  // Проверка rehash
  h1.add("ключ4", 40);
  h1.add("ключ5", 50);
  h1.add("ключ6", 60);
  assert(h1.size() == 5);
  std::cout << "Тест 8 пройден." << std::endl;

  // Проверка итератора
  std::cout << "Проверка итератора:\n";
  for (auto it = h1.begin(); it != h1.end(); ++it) {
    if(!(*it).first.empty()){
      std::cout << "Ключ: " << (*it).first << ", значение: " << (*it).second << std::endl;
    }
  }
  std::cout << "Тест 9 пройден." << std::endl;
}catch(HashEr &err){
  std::cout << "Тест 1-9 не пройден. Ошибка: - " << err.getMes() << std::endl;
}catch(...){
  std::cout << "Тест 1-9 не пройден." << std::endl;
}
  try{
    HashTbl<double> t_dbl;
    t_dbl.readFile("hashDouble.txt");
    printf("\n");
    std::cout << "Файл \"hashDouble.txt\" успешно открыт\n";
    t_dbl.add("str4", 2.7);
    assert(fabs(t_dbl.get("str4") - 2.7) < eps);
    std::cout << "Тест 10 пройден." << std::endl;
    t_dbl.remove("str3");
    std::cout << "Проверка итератора:\n";
    for (auto it = t_dbl.begin(); it != t_dbl.end(); ++it) {
      if(!(*it).first.empty()){
        std::cout << "Ключ: " << (*it).first << ", значение: " << (*it).second << std::endl;
      }
    }
    std::cout << "Тест 11 пройден." << std::endl;
  }catch(HashEr &err){
    std::cout << "Тест 10-11 не пройден. Ошибка: - " << err.getMes() << std::endl;
  }catch(...){
    std::cout << "Тест 10-11 не пройден." << std::endl;
  }
  
  try{
    HashTbl<int> t_dbl;
    t_dbl.readFile("strangeHash.txt");
    printf("\n");
    std::cout << "Файл \"strangeHash.txt\" успешно открыт\n";
  }catch(HashEr &err){
    std::cout << "Тест 12 пройден." << err.getMes() << std::endl;
  }catch(...){
    std::cout << "Тест 12 не пройден." << std::endl;
  }
  
  try{ // Добавление строк
    HashTbl<std::string> h2;
    printf("\n");
    h2.add("ключ1", "значение1");
    h2.add("ключ2", "значение2");
    h2.add("ключ3", "значение3");

    // Проверка получения значений
    assert(h2.get("ключ1") == "значение1");
    std::cout << "Тест 13 пройден." << std::endl;
    assert(h2.get("ключ2") == "значение2");
    std::cout << "Тест 14 пройден." << std::endl;
    assert(h2.get("ключ3") == "значение3");
    std::cout << "Тест 15 пройден." << std::endl;

    // Проверка размера
    assert(h2.size() == 3);
    std::cout << "Тест 16 пройден." << std::endl;

    // Проверка удаления
    h2.remove("ключ2");
    assert(h2.size() == 2);
    std::cout << "Тест 17 пройден." << std::endl;
    assert(h2.get("ключ1") == "значение1");
    std::cout << "Тест 18 пройден." << std::endl;
    assert(h2.get("ключ3") == "значение3");
    std::cout << "Тест 19 пройден." << std::endl;

    // Проверка итератора
    std::cout << "Проверка итератора:\n";
    for (auto it = h2.begin(); it != h2.end(); ++it) {
      if(!(*it).first.empty()){
        std::cout << "Ключ: " << (*it).first << ", значение: " << (*it).second << std::endl;
      }
    }
    std::cout << "Тест 20 пройден." << std::endl;
  }catch(HashEr &err){
    std::cout << "Тесты 13-20 не пройден. Ошибка: - " << err.getMes() << std::endl;
  }catch(...){
    std::cout << "Тесты 13-20 не пройден." << std::endl;
  }
  try {
    HashTbl<std::string> h2;
    h2.get("key3");
    printf("\n");
    std::cout << "Тест 21 не пройден." << std::endl;
    }catch(HashEr &er){
      if (er.getCode() != -3){
          std::cout << "Тест 21 не пройден." << std::endl;
      }else{
        std::cout << "Тест 21 пройден." << std::endl;
      }
  } 
  
  try{
    HashTbl<int> int_hash_table = gen_rnd_set_int(10);
    printf("\n");
    std::cout << "Создано случайное множество.\n";
    int_hash_table.add("key2", 24);
    std::cout << "Проверка итератора:\n";
    for (auto it = int_hash_table.begin(); it != int_hash_table.end(); ++it) {
      if(!(*it).first.empty()){
      std::cout << "Ключ: " << (*it).first << ", значение: " << (*it).second << std::endl;
    }
  }
  std::cout << "Тест 22 пройден." << std::endl;
  }catch(HashEr &err){
    std::cout << "Тест 22 не пройден. Ошибка: - " << err.getMes() << std::endl;
  }catch(...){
    std::cout << "Тест 22 не пройден." << std::endl;
  }
  
    try{
    HashTbl<std::string> str_hash_table = gen_rnd_set_string(10);
    printf("\n");
    std::cout << "Создано случайное множество.\n";
    str_hash_table.add("key2", "str");
    std::cout << "Проверка итератора:\n";
    for (auto it = str_hash_table.begin(); it != str_hash_table.end(); ++it) {
      if(!(*it).first.empty()){
      std::cout << "Ключ: " << (*it).first << ", значение: " << (*it).second << std::endl;
    }
  }
  std::cout << "Тест 23 пройден." << std::endl;
  }catch(HashEr &err){
    std::cout << "Тест 23 не пройден. Ошибка: - " << err.getMes() << std::endl;
  }catch(...){
    std::cout << "Тест 23 не пройден." << std::endl;
  }
  return 0;
}
