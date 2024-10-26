#include <iostream>
#include <vector>
#include <string>
#include <list>




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
      std::string key;
      T val;
      bool ntEmpty;
      
      HashEl() : ntEmpty(false){}
      HashEl(const std::string& k, const T& v) : key(k), val(v), ntEmpty(true) {} 
    };
    
    std::vector<HashEl> table; //Вектор элементов структуры
    int curSize; //Количество хранящихся ключей
    int tblSize; //Максимальное количество ключей (количество выделенной памяти)
    
    int hash(const std::string& k) const {
      std::hash<std::string> hashFun;
      return hashFun(k) % tblSize;
    }
    
    void rehash(); //Перезапись Хэш-таблицы - увеличение памяти
    
    public:
      HashTbl(int newCap = 10) : tblSize(newCap), curSize(0) {
        table.resize(tblSize);
      }
      
      void add(const std::string& key, const T& value); //Функция добавления точки
      
      T get(const std::string& key) const; //Функция получения точки
      
      void remove(const std::string& key); //Функция удаления ключа
      int size() const { //Функция получения количества ключей
        return curSize;
      }
      
      class Iterator { //Итератор
        private: 
          const HashTbl& table;
          int ind;
         
         public:
          Iterator(const HashTbl& t, int i) : table(t), ind(i) {}
          
          bool operator!=(const Iterator& other) const {
            return ind!=other.ind;
          }
          
          void operator++() {
            do{
              ind++;
            }while (ind < table.tblSize && !(table.table[ind].ntEmpty));
          }
          
          std::pair<std::string, T> operator*() const {
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
};
