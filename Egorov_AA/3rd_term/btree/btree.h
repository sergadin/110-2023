#include <vector>
#include <iostream>
#include <string>
#include <queue>
#include <algorithm>


class BNode {
    std::string* keys;       // Массив длины 2*n_order, состоящий из строк
    BNode** children;        // Массив указателей на потомков
    int key_number;          // Количество элементов в узле
    int t;
    bool leaf;

public:

    void insertNonFull(std::string k);  // Вставка в неполный узел
    void splitChild(int i, BNode* y);   // 
    void traverse();
    void iterateFrom(std::string k);
    void iterateTo(std::string k);
    void iterateFromTo(std::string start, std::string stop);

    int findKey(std::string k);
    void remove(std::string k);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    std::string getPred(int idx);
    std::string getSucc(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);


    void clear();

    BNode(int t1, bool leaf1) {
        t = t1;
        leaf = leaf1;
        keys = new std::string[2 * t - 1];
        children = new BNode * [2 * t];
        key_number = 0;
    }
    
    BNode* search(std::string k);
     
    friend class BTree;
};


class BTree {
private:
    BNode* root;
    int t;



public:
    BTree(int temp);
    
    void clear();

    BNode* search(std::string k) {
        return (root == NULL) ? NULL : root->search(k);
    }

    void traverse();

    void iterateFrom(std::string k);

    void iterateTo(std::string k);
    
    void iterateFromTo(std::string start, std::string stop);
    
    void insert(std::string k);

    void remove(std::string k);

};
