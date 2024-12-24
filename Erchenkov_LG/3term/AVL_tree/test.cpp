#include "AVL.hpp"
#include <iostream>
#include <random>


int gen_integer_random_value() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 1000);

    return dist(gen);
}

std::string gen_random_str(size_t length) {
    const std::string characters = 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789";
    
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, characters.size() - 1); 

    std::string random_string;
    for (int i = 0; i < length; ++i) {
        random_string += characters[distribution(generator)];
    }

    return random_string;
}

int main(void) {
    using namespace Tree;

    AVL<char> tree;

    tree.insert("1", 'q');
    tree.insert("2", 'w');
    tree.insert("3", 'e');
    tree.insert("4", 'r');
    tree.insert("5", 't');
    tree.insert("6", 'y');

    tree.print();

    std::string s = tree.search('x');
    std::string ss = tree.search('y');

    if (s != "")
        std::cout << "Find: " << s << std::endl;
    if (ss != "")
        std::cout << "Find: " << ss << std::endl;


    tree.remove('w');

    tree.print();


    std::cout << std::endl;
    std::cout << "-----------------------------------" << std::endl;


    AVL<int> random_tree;

    const unsigned TREESZ = 100; 

    for (int i = 0; i < TREESZ; i++) {
        std::string s = gen_random_str(3);
        int x = gen_integer_random_value();
        random_tree.insert(s, x);
    }

    random_tree.print();

    std::cout << std::endl;

    int elem = gen_integer_random_value();
    int not_random_elem = 2;
    std::cout << "Searching " << elem << " in a random AVL<int> tree.." << std::endl;
    std::cout << "Also searching " << not_random_elem << std::endl;
    std::string s1 = random_tree.search(elem);
    std::string s2 = random_tree.search(not_random_elem); 


    if (s1 != "")
        std::cout << "Find " << elem << ": " << s1 << std::endl;
    if (s2 != "")
        std::cout << "Find " << elem << ": " << s2 << std::endl;

    std::cout << std::endl;

    std::cout << "-----------------------------" << std::endl;

    AVL<std::string> random_stree;
    const unsigned STREESZ = 10;
    for (int i = 0; i < TREESZ; i++) {
        std::string s = gen_random_str(3);
        std::string x = gen_random_str(5);
        random_stree.insert(s, x);
    }

    try {
        AVL<double> dtree;
        dtree.fileInput("doubleInp.txt");
        std::cout << std::endl;
        std::cout << "Trying to open doubleInp.txt..." << std::endl;

        dtree.insert("not", 4.39);
        dtree.print();
    }
    catch(Err &err) {
        std::cout << err.errMessage() << std::endl;
    }
    catch(...) {
        std::cout << "something went wrong" << std::endl;
    }

}
    /*
    random_stree.print();
    std::string elem = gen_random_str(5);
    std::cout << "Searching " << elem << " in a random AVL<str> tree.." << std::endl;
    std::string s1 = random_stree.search(elem); 
    if (s1 != "")
        std::cout << "Find " << elem << ": " << s1;

    return 0;
    */

