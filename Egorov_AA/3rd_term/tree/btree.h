#include <iostream>
#include <vector>
using namespace std;

class BTreeNode {
public:
    vector<int> keys;        // Ключи в узле
    vector<BTreeNode*> children; // Указатели на дочерние узлы
    bool isLeaf;             // Является ли узел листом
    int t;                   // Минимальная степень

    BTreeNode(int _t, bool _isLeaf);
    void traverse();
    BTreeNode* search(int k);
    void insertNonFull(int k);
    void splitChild(int i, BTreeNode* y);
    void remove(int k);

private:
    int findKey(int k);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    int getPredecessor(int idx);
    int getSuccessor(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);

    friend class BTree;
};

class BTree {
    BTreeNode* root;
    int t;

public:
    BTree(int _t) {
        root = nullptr;
        t = _t;
    }

    void traverse() {
        if (root != nullptr) root->traverse();
        cout << endl;
    }

    BTreeNode* search(int k) {
        return (root == nullptr) ? nullptr : root->search(k);
    }

    void insert(int k);
    void remove(int k);
};
