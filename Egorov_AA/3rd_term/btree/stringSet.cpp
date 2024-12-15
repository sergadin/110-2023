#include <iostream>
#include <set>
#include <string>
#include <fstream>
#include <iterator>
#include "btree.h"
#include "stringSet.h"


void OrderedStringSet::addString(std::string str) {
    btree.insert(str);
}

void OrderedStringSet::removeString(std::string str) {
    btree.remove(str);
}

bool OrderedStringSet::findString(std::string str) const {
    if (btree.search(str) != NULL) return true;
    else return false;
}

void OrderedStringSet::iterateFrom(std::string start) const {
    btree.iterateFrom(start);
    std::cout << "\n";
}

void OrderedStringSet::iterateTo(std::string stop) const {
    btree.iterateTo(stop);
    std::cout << "\n";
}

void OrderedStringSet::iterateFromTo(std::string start, std::string stop) const {
    if(start > stop)
        std::cout << "Неправильно заданы начальный и конечный элементы.";
    btree.iterateFromTo(start, stop);
    std::cout << "\n";
}

