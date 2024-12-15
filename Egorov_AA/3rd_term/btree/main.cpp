#include "btree.h"

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

    tree.traverse();

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
