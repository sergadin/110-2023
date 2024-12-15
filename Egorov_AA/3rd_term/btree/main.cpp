#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include "btree.h"

int main() {
    BTree tree;
    tree.insert("hello");
    tree.insert("world");
    tree.insert("b-tree");

    std::cout << "Contains 'hello': " << tree.contains("hello") << std::endl;
    std::cout << "Contains 'test': " << tree.contains("test") << std::endl;

    BTree::Iterator it = tree.iteratorFrom("b-tree");
    while (it.hasNext()) {
        std::cout << it.next() << " ";
    }
    std::cout << std::endl;

    tree.remove("hello");
    std::cout << "Contains 'hello' after removal: " << tree.contains("hello") << std::endl;

    return 0;
}
