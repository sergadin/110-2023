#include <iostream>
#include <set>
#include <string>
#include <fstream>
#include <iterator>

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

    void iterateFrom(const std::string& start) const {
        t

        std::cout << "\n";
    }
};
