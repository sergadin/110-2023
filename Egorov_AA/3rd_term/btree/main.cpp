#include "btree.h"
#include "stringSet.h"

int main() {
    int n = 10;    // Количество элементов B - дерева
    std::string s;
    BTree tree(3);

    for (int j = 0; j < n; j++) {
        s = "";
        for (int i = 0; i < 10; i++)
        {
            s += char(70 + rand() % (80 - 70));
        }
        std::cout << s << std::endl;
        tree.insert(s);
    }
    std::cout << "\n\n";



    //tree.insert("abcdefg");
    //t.insert("basdbasb");
    //t.insert("eabtsdbdsf");
    //t.insert("shjnmsnf");
    //t.insert("lotugj");
    //t.insert("dhm77m");
    //t.insert("lotugj");

    //t.remove("lotugj");

    //std::cout << "\n";
    //t.traverse();

}


int main() {
    OrderedStringSet fruits;
    oss.addString("apple");
    oss.addString("banana");
    oss.addString("cherry");

    std::cout << "Size: " << oss.size() << "\n";
    oss.iterateFrom("banana");

    if (oss.findString("banana")) {
        std::cout << "Banana found in the set.\n";
    }

    oss.removeString("banana");
    oss.iterateFrom("banana");

    return 0;
}
