#include <iostream>
#include <set>
#include <string>
#include <fstream>
#include <iterator>
#include "btree.h"

class OrderedStringSet {
private:
    BTree btree;

public:
    void addString(std::string str) {
        btree.insert(str);
    }

    void removeString(std::string str) {
        btree.remove(str);
    }

    bool findString(std::string str) const {
        if (btree.search(str) != NULL) return true;
        else return false;
    }

    void iterateFrom(string start) const {
        btree.iterateFrom(start);
        std::cout << "\n";
    }

    void iterateTo(std::string stop) const {
        btree.iterateTo(stop);
        std::cout << "\n";
    }

    void iterateFromTo(std::string start, std::string stop) const {
        if(start > stop)
            std::cout << "Неправильно заданы начальный и конечный элементы."
        btree.iterateFromTo(start, stop);
        std::cout << "\n";
    }

};