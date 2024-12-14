#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class BTreeNode : public enable_shared_from_this<BTreeNode> {
public:
    vector<string*> keys;        // Ключи в узле
    vector<shared_ptr<BTreeNode>> children; // Умные указатели на дочерние узлы
    bool isLeaf;             // Является ли узел листом
    int t;                   // Минимальная степень

    BTreeNode(int _t, bool _isLeaf);
    void traverse();
    shared_ptr<BTreeNode> search(const string& k);
    void insertNonFull(string* k);
    void splitChild(int i, shared_ptr<BTreeNode> y);
    void remove(const string& k);

private:
    int findKey(const string& k);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    string* getPredecessor(int idx);
    string* getSuccessor(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);

    friend class BTree;
};


class BTree {
    shared_ptr<BTreeNode> root;
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

    shared_ptr<BTreeNode> search(int k) {
        return (root == nullptr) ? nullptr : root->search(k);
    }

    void insert(string* k);
    void remove(const string& k);
};


