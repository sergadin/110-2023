#include "hashTable.h"


    void HashTbl::rehash() {
      int oldCap = tblSize;
      tblSize *= 2;
      std::vector<HashEl> oldTable = table;
      table = std::vector<HashEl>(tblSize);
      curSize = 0;
      
      for (const auto& el : oldTable) {
        if (el.ntEmpty){
          add(el.key, el.val);
        }
      }
    }
    
  void HashTbl::add(const std::string& key, const T& value) {
        if (curSize >= (tblSize / 2)){
          rehash();
        }
        
        int index = HashTbl::hash(key);
        while (table[index].ntEmpty) {
          if (table[index].key == key){
            table[index].val = value;
            return;
          }
          index = (index + 1) % tblSize;
        }
        
        table[index] = HashEl(key, value);
        curSize++;
      }
      
      T HashTbl::get(const std::string& key) const {
        int index = HashTbl::hash(key);
        while (table[index].ntEmpty) {
          if (table[index].key == key){
            return table[index].val;
          }
          index = (index + 1) % tblSize;
        }
        throw HashEr(-1, std::string("Key not found\n"));
      }
      
      void HashTbl::remove(const std::string& key) {
        int index = HashTbl::hash(key);
        while (table[index].ntEmpty) {
          if (table[index].key == key){
            table[index].ntEmpty = false;
            curSize--;
            return;
          }
          index = (index + 1) % tblSize;
        }
      }
