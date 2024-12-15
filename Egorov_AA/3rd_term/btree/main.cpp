#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include "btree.h"

int main() {
    BTree tree;
    tree.insert("asdgsad");
    tree.insert("atkreu,j");
    tree.insert("cisiroh");
    tree.insert("apoejb");
    tree.insert("[apfo3ew");
    tree.insert("q-kovjbji64");
    tree.insert("gjqw89a");

    std::cout << "Contains 'q-kovjbji64': " << tree.contains("q-kovjbji64") << std::endl;
    std::cout << "Contains 'abcdefg': " << tree.contains("abc") << std::endl;

    BTree::Iterator it = tree.iteratorFrom("asdgsad");
    while (it.hasNext()) {
        std::cout << it.next() << " ";
    }
    std::cout << std::endl;

    tree.remove("cisiroh");
    std::cout << "Contains 'cisiroh' after removal: " << tree.contains("cisiroh") << std::endl;

    return 0;
}
