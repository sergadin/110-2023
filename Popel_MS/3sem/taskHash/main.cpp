#include "hashTable.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>

static void LoadFile(const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw HashEr(-2, std::string("Openning problems\n"));
  }
  std::string key;
  V val;
  auto type; //как ввести тип
  ///
  file.close();
}

static HashTbl<V> GenRndTbl(int sz) {
  HashTbl<V> table;
  for (int i = 0; i < sz; ++i){
    table.add("key" + std::to_string(i), V(i));
  }
  return table;
}

class ExampleClass{
  public:
    int number;
    
    ExampleClass(int n) : number(n) {}
};

int main(void){
  auto randSet = HashTbl<int>::GenRndTbl(15);
  return 0;
}
