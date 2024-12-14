#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Узел B-дерева
class BTreeNode {
public:
    vector<string*> keys;   // Ключи (указатели на строки)
    vector<BTreeNode*> children; // Дочерние узлы
    bool isLeaf;            // Лист или нет
    int t;                  // Минимальная степень

    BTreeNode(int t, bool isLeaf);
    void insertNonFull(string* key);
    void splitChild(int i, BTreeNode* y);
    void traverse();
    BTreeNode* search(string* key);
};

// Конструктор узла
BTreeNode::BTreeNode(int t, bool isLeaf) {
    this->t = t;
    this->isLeaf = isLeaf;
}

// Метод обхода
void BTreeNode::traverse() {
    int i;
    for (i = 0; i < keys.size(); i++) {
        if (!isLeaf)
            children[i]->traverse();
        cout << *keys[i] << " ";
    }
    if (!isLeaf)
        children[i]->traverse();
}

// Метод поиска
BTreeNode* BTreeNode::search(string* key) {
    int i = 0;
    while (i < keys.size() && *key > *keys[i])
        i++;
    if (i < keys.size() && *keys[i] == *key)
        return this;
    if (isLeaf)
        return nullptr;
    return children[i]->search(key);
}

// Вставка в неполный узел
void BTreeNode::insertNonFull(string* key) {
    int i = keys.size() - 1;
    if (isLeaf) {
        keys.push_back(nullptr);
        while (i >= 0 && *key < *keys[i]) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = key;
    } else {
        while (i >= 0 && *key < *keys[i])
            i--;
        if (children[i + 1]->keys.size() == 2 * t - 1) {
            splitChild(i + 1, children[i + 1]);
            if (*key > *keys[i + 1])
                i++;
        }
        children[i + 1]->insertNonFull(key);
    }
}

// Разделение дочернего узла
void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->t, y->isLeaf);
    z->keys.insert(z->keys.end(), y->keys.begin() + t, y->keys.end());
    y->keys.resize(t - 1);
    if (!y->isLeaf) {
        z->children.insert(z->children.end(), y->children.begin() + t, y->children.end());
        y->children.resize(t);
    }
    children.insert(children.begin() + i + 1, z);
    keys.insert(keys.begin() + i, y->keys[t - 1]);
}

// B-дерево
class BTree {
public:
    BTreeNode* root;
    int t;

    BTree(int t) { root = nullptr; this->t = t; }
    void traverse() { if (root) root->traverse(); }
    BTreeNode* search(string* key) { return (root ? root->search(key) : nullptr); }
    void insert(string* key);
};

// Вставка в дерево
void BTree::insert(string* key) {
    if (!root) {
        root = new BTreeNode(t, true);
        root->keys.push_back(key);
    } else {
        if (root->keys.size() == 2 * t - 1) {
            BTreeNode* s = new BTreeNode(t, false);
            s->children.push_back(root);
            s->splitChild(0, root);
            int i = (*key > *s->keys[0]) ? 1 : 0;
            s->children[i]->insertNonFull(key);
            root = s;
        } else {
            root->insertNonFull(key);
        }
    }
}
