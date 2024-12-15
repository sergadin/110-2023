#include "btree.h"

int main() {
    BTree t(3);
    t.insert("abcdefg"); // 1
    t.insert("basdbasb"); // 2
    t.insert("eabtsdbdsf"); // 5
    t.insert("shjnmsnf"); // 7
    t.insert("lotugj"); // 6
    t.insert("dhm77m"); // 4
    t.insert("lotugj"); // 6
    t.insert("dghn5ey"); // 3

    t.traverse();

    t.remove("lotugj");

    std::cout << "\n";
    t.traverse();

}