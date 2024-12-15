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
    OrderedStringSet() {
    	
    }

    void addString(std::string str);

    void removeString(std::string str);

    bool findString(std::string str) const;

    void iterateFrom(std::string start) const;

    void iterateTo(std::string stop) const;

    void iterateFromTo(std::string start, std::string stop) const;

};
