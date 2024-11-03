#ifndef TBL
#define TBL
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <random>
#include <fstream>


//класс ошибок
class HashEr{
  private:
    int code_;
    std::string mes_;
  public:
    HashEr(int code, std::string mes) : code_(code), mes_(mes) {}
    int getCode() {
      return code_;
    }
    std::string getMes() {
      return mes_; 
    }
};


template<typename T>
class HashTbl {
  private:
    struct HashEl{ //Структура с данными для отображения
      std::string key; //ключ в формате строки
      T val; //соответствующее ключу значение
      bool ntEmpty; //есть или нет значения
      
      HashEl() : key(""), val{}, ntEmpty(false){} //конструктор без элементов
      HashEl(const std::string& k, const T& v) : key(k), val(v), ntEmpty(true) { //конструктор по ключу и значению
        if (k.empty()) {
          throw HashEr(-1, std::string("Key cannot be empty2\n"));
        }
        key = k;
        ntEmpty = true;
      } 
    };
    
    std::vector<HashEl> table; //Вектор элементов структуры
    int curSize; //Количество хранящихся ключей
    int tblSize; //Максимальное количество ключей (количество выделенной памяти)
    void rehash(); //Перезапись Хэш-таблицы - увеличение памяти
    
    public:
      HashTbl(int newCap = 10) : table(newCap), curSize(0), tblSize(newCap){ //конструктор хэш-таблицы
      if(newCap <= 0 ){
        throw HashEr(-2, std::string("Table size must be positive\n"));
      }
        table.resize(newCap);
        for (auto& el : table){
          el.ntEmpty = false;
        }
      }
      
      int hash(const std::string& str) const; //хэш-функция
      void add(const std::string& key, const T& value); //Функция добавления точки      
      T get(const std::string& key) const; //Функция получения точки      
      void remove(const std::string& key); //Функция удаления ключа
      int size() const { //Функция получения количества ключей
        return curSize;
      }
      
      class Iterator { //Итератор
        private: 
          const HashTbl& table;//хэш-таблица
          int ind; //текущая позиция
         
        public:
          Iterator(const HashTbl& t, int i) : table(t), ind(i) {} //конструктор
          
          bool operator!=(const Iterator& other) const { //оператор неравенства
            return ind != other.ind;
          }
          
          Iterator& operator++() { //оператор шага (увеличения индекса на один)
            do{
              ind++;
            }while (ind < table.tblSize && !(table.table[ind].ntEmpty));
            return *this;
          }
          
          std::pair<std::string, T> operator*() const { //оператор-указатель (возвращает уже сам элемент по индексу)
            return {table.table[ind].key, table.table[ind].val};
          }
      };
      
      Iterator begin() const {
        int ind = 0;
        while ((ind < tblSize) && !(table[ind].ntEmpty)) {
          ind++;
        }
        return Iterator(*this, ind);
      }
      Iterator end() const {
        return Iterator(*this, tblSize);
      }
      
      void readFile(const std::string& filename); //чтение множества из файла
};

template <typename T>
int HashTbl<T>::hash(const std::string& str) const{
  int h =  0;
  for (char c : str){
    h = h * 31 + static_cast<unsigned char>(c);
  }
  return h;
}

template<typename T>
void HashTbl<T>::rehash() {
  int counter = 0;
  int oldSize = tblSize;
  tblSize *= 2;
  std::vector<HashEl> oldTable = table;
  table = std::vector<HashEl>(tblSize);
  curSize = 0;
  
  for (auto& el : table){
    el.ntEmpty = false;
  }
  
  for (int i = 0; i < oldSize; i++) {
    if (oldTable[i].ntEmpty && !oldTable[i].key.empty()){
      this->add(oldTable[i].key, oldTable[i].val);
      table[counter].ntEmpty = true;
      counter++;
    }
  }
}

template<typename T>
void HashTbl<T>::add(const std::string& key, const T& value){
  bool whole_circle = 0;
  if (key.empty()) {
    throw HashEr(-1, std::string("Key cannot be empty1\n"));
  }
  if (curSize >= (tblSize / 2)){
    this->rehash();
  }
  int index = (abs(hash(key)) % tblSize);
  while ((table[index].ntEmpty) && !(table[index].key.empty()) && !(((index + 1) >= tblSize) && whole_circle)) {
    if (table[index].key == key){
      table[index].val = value;
      return;
    }
    if (((index + 1) >= tblSize) && !(whole_circle)){
        whole_circle = 1;
  }
    index = (index + 1) % tblSize;
  }
  table[index] = HashEl(key, value);
  table[index].ntEmpty = true;
  curSize++;
}
      
template<typename T>
T HashTbl<T>::get(const std::string& key) const {
  bool whole_circle = 0;
  int index = abs(HashTbl::hash(key)) % tblSize;
  while (table[index].ntEmpty && !(((index + 1) >= tblSize) && whole_circle)){
    if (table[index].key == key){
      return table[index].val;
    }
    if (((index + 1) >= tblSize) && !(whole_circle)){
        whole_circle = 1;
  }
    index = (index + 1) % tblSize;
  }
  throw HashEr(-3, std::string("Key not found\n"));
}

template<typename T>
void HashTbl<T>::remove(const std::string& key) {
  int index = abs(HashTbl::hash(key)) % tblSize;
  int nextIndex = 0;
  bool whole_circle = 0;
  while (table[index].ntEmpty && !(((index + 1) >= tblSize) && whole_circle)) {
    if (table[index].key == key){
      curSize--;
      
      nextIndex = (index + 1) % tblSize;
      bool wh_c = 0;
      while ((hash(table[nextIndex].key)%tblSize == hash(table[index].key)%tblSize) && (table[nextIndex].ntEmpty) && !(((nextIndex + 1) >= tblSize) && wh_c)){
        table[index] = table[nextIndex];
        index = nextIndex;
        if (((nextIndex + 1) >= tblSize) && !(wh_c)){
              wh_c = 1;
        }
        nextIndex = (nextIndex + 1) % tblSize;
      }
      table[index].ntEmpty = false;
      return;
    }
    if (((index + 1) >= tblSize) && !(whole_circle)){
              whole_circle = 1;
        }
    index = (index + 1) % tblSize;
  }
  throw HashEr(-3, std::string("Key not found\n"));
}


template <typename T>
void HashTbl<T>::readFile(const std::string& filename){
  std::ifstream input_file(filename);
  if (!input_file.is_open()){
    throw HashEr(-4, std::string("File openning problems\n"));
  }
  std::string key;
  std::string type;
  T val;
  std::getline(input_file, type);
  if (type.empty()){
    input_file.close();
    throw HashEr(-6, std::string("This is not type\n"));
  }
  if (type == "std::string"){
      while (input_file >> key >> val){
        this->add(key, val);
  }
  }else if (type == "double"){
        while (input_file >> key >> val){
        this->add(key, val);
  }
  }else if (type == "int"){
        while (input_file >> key >> val){
        this->add(key, val);
  }
  }else if (type == "char"){
      while (input_file >> key >> val){
        this->add(key, val);
    }
  }else {
    input_file.close();
    throw HashEr(-5, std::string("This type isn't allowed\n"));
  }
  input_file.close();
}
#endif
