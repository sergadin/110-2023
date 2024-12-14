#include <iostream>
#include "btree.h"

int main() {
    BTree tree(3);

    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(6);
    tree.insert(12);
    tree.insert(30);
    tree.insert(7);
    tree.insert(17);

    cout << "Traversal of the tree: ";
    tree.traverse();
    tree.remove(6);
    cout << "After deleting 6: ";
    tree.traverse();

    return 0;
}
