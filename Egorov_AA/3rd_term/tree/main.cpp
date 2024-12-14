#include <iostream>
#include <vector>
#include <string>
using namespace std;

// BTreeNode class
class BTreeNode {
public:
    vector<string*> keys; // Keys (pointers to strings)
    vector<BTreeNode*> children; // Child pointers
    bool leaf; // True if this node is a leaf
    int t; // Minimum degree

    BTreeNode(int t, bool leaf);

    void traverse();

    BTreeNode* search(const string& k);

    void insertNonFull(string* k);

    void splitChild(int i, BTreeNode* y);

    int findKey(const string& k);

    void remove(const string& k);

    void removeFromLeaf(int idx);

    void removeFromNonLeaf(int idx);

    string* getPred(int idx);

    string* getSucc(int idx);

    void fill(int idx);

    void borrowFromPrev(int idx);

    void borrowFromNext(int idx);

    void merge(int idx);

    friend class BTree;
};

// BTree class
class BTree {
private:
    BTreeNode* root; // Pointer to root node
    int t; // Minimum degree
public:
    BTree(int t) : root(nullptr), t(t) {}

    void traverse() {
        if (root) root->traverse();
    }

    BTreeNode* search(const string& k) {
        return root ? root->search(k) : nullptr;
    }

    void insert(string* k);

    void remove(const string& k);
};

// Constructor for BTreeNode
BTreeNode::BTreeNode(int t, bool leaf) : t(t), leaf(leaf) {}

// Traverse the tree
void BTreeNode::traverse() {
    int i;
    for (i = 0; i < keys.size(); i++) {
        if (!leaf) children[i]->traverse();
        cout << *(keys[i]) << " ";
    }
    if (!leaf) children[i]->traverse();
}

// Search for a key in the tree
BTreeNode* BTreeNode::search(const string& k) {
    int i = 0;
    while (i < keys.size() && k > *(keys[i]))
        i++;
    if (i < keys.size() && *(keys[i]) == k)
        return this;
    if (leaf) return nullptr;
    return children[i]->search(k);
}

//Вставка нового ключа в дерево
void BTree::insert(string* k) {
    if (!root) {
        root = new BTreeNode(t, true);
        root->keys.push_back(k);
    }
    else {
        if (root->keys.size() == 2 * t - 1) {
            BTreeNode* s = new BTreeNode(t, false);
            s->children.push_back(root);
            s->splitChild(0, root);
            int i = (s->keys[0] && *k > *(s->keys[0])) ? 1 : 0;
            s->children[i]->insertNonFull(k);
            root = s;
        }
        else {
            root->insertNonFull(k);
        }
    }
}

// Insert a key into a non-full node
void BTreeNode::insertNonFull(string* k) {
    int i = keys.size() - 1;
    if (leaf) {
        keys.insert(keys.begin() + (i + 1), k);
        while (i >= 0 && *keys[i] > *k) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
    }
    else {
        while (i >= 0 && *keys[i] > *k)
            i--;
        i++;
        if (children[i]->keys.size() == 2 * t - 1) {
            splitChild(i, children[i]);
            if (*keys[i] < *k)
                i++;
        }
        children[i]->insertNonFull(k);
    }
}

// Split a child node
void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->t, y->leaf);
    for (int j = 0; j < t - 1; j++)
        z->keys.push_back(y->keys[j + t]);
    if (!y->leaf) {
        for (int j = 0; j < t; j++)
            z->children.push_back(y->children[j + t]);
    }
    y->keys.resize(t - 1);
    children.insert(children.begin() + (i + 1), z);
    keys.insert(keys.begin() + i, y->keys[t - 1]);
    y->keys.pop_back();
}

// Remove a key from the tree
void BTree::remove(const string& k) {
    if (!root) {
        cout << "The tree is empty\n";
        return;
    }
    root->remove(k);
    if (root->keys.empty()) {
        BTreeNode* tmp = root;
        root = root->leaf ? nullptr : root->children[0];
        delete tmp;
    }
}

// More remove and helper methods can be added here...

int main() {
    BTree t(3); // A B-tree with minimum degree 3
    string s1 = "hello";
    string s2 = "world";
    string s3 = "tree";
    string s4 = "b-tree";
    string s5 = "data";

    t.insert(&s1);
    t.insert(&s2);
    t.insert(&s3);
    t.insert(&s4);
    t.insert(&s5);

    cout << "Traversal of the constructed B-tree is:\n";
    t.traverse();
    cout << endl;

    return 0;
}
