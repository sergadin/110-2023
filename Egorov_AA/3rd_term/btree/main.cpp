#include "btree.h"
#include "stringSet.h"

int main() {
    fruits = OrderedStringSet;
    fruits.addString("apple");
    fruits.addString("banana");
    fruits.addString("cherry");

    fruits.iterateFrom("banana");

    if (fruits.findString("banana")) {
        std::cout << "Banana found in the set.\n";
    }

    fruits.removeString("banana");
    fruits.iterateFrom("banana");

    return 0;
}
