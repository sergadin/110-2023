#include <iostream>
#include <vector>
#include "btree.h"
using namespace std;

// Конструктор узла B-дерева
BTreeNode::BTreeNode(int _t, bool _isLeaf) {
    t = _t;
    isLeaf = _isLeaf;
}

// Поиск ключа
shared_ptr<BTreeNode> BTreeNode::search(int k) {
    int i = 0;
    while (i < keys.size() && k > keys[i]) i++;

    if (i < keys.size() && keys[i] == k) return shared_from_this();
    if (isLeaf) return nullptr;

    return children[i]->search(k);
}

// Обход дерева
void BTreeNode::traverse() {
    for (int i = 0; i < keys.size(); i++) {
        if (!isLeaf) children[i]->traverse();
        cout << keys[i] << " ";
    }
    if (!isLeaf) children[keys.size()]->traverse();
}

// Вставка ключа в неполный узел
void BTreeNode::insertNonFull(int k) {
    int i = keys.size() - 1;

    if (isLeaf) {
        keys.push_back(0);
        while (i >= 0 && k < keys[i]) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
    }
    else {
        while (i >= 0 && k < keys[i]) i--;
        if (children[i + 1]->keys.size() == 2 * t - 1) {
            splitChild(i + 1, children[i + 1]);
            if (k > keys[i + 1]) i++;
        }
        children[i + 1]->insertNonFull(k);
    }
}

// Разделение дочернего узла
void BTreeNode::splitChild(int i, shared_ptr<BTreeNode> y) {
    auto z = make_shared<BTreeNode>(y->t, y->isLeaf);
    z->keys.assign(y->keys.begin() + t, y->keys.end());
    y->keys.resize(t - 1);

    if (!y->isLeaf) {
        z->children.assign(y->children.begin() + t, y->children.end());
        y->children.resize(t);
    }

    children.insert(children.begin() + i + 1, z);
    keys.insert(keys.begin() + i, y->keys[t - 1]);
}

// Вставка ключа в дерево
void BTree::insert(int k) {
    if (!root) {
        root = make_shared<BTreeNode>(t, true);
        root->keys.push_back(k);
    }
    else {
        if (root->keys.size() == 2 * t - 1) {
            auto s = make_shared<BTreeNode>(t, false);
            s->children.push_back(root);
            s->splitChild(0, root);

            int i = (s->keys[0] < k) ? 1 : 0;
            s->children[i]->insertNonFull(k);
            root = s;
        }
        else {
            root->insertNonFull(k);
        }
    }
}

// Удаление ключа из узла
void BTree::remove(int k) {
    if (!root) {
        cout << "Tree is empty!\n";
        return;
    }

    root->remove(k);

    if (root->keys.empty()) {
        root = root->isLeaf ? nullptr : root->children[0];
    }
}

void BTreeNode::remove(int k) {
    int idx = findKey(k);

    if (idx < keys.size() && keys[idx] == k) {
        isLeaf ? removeFromLeaf(idx) : removeFromNonLeaf(idx);
    }
    else {
        if (isLeaf) return;
        bool lastChild = (idx == keys.size());

        if (children[idx]->keys.size() < t) fill(idx);
        if (lastChild && idx > keys.size()) {
            children[idx - 1]->remove(k);
        }
        else {
            children[idx]->remove(k);
        }
    }
}

int BTreeNode::findKey(int k) {
    int idx = 0;
    while (idx < keys.size() && keys[idx] < k) idx++;
    return idx;
}

void BTreeNode::removeFromLeaf(int idx) {
    keys.erase(keys.begin() + idx);
}

void BTreeNode::removeFromNonLeaf(int idx) {
    int k = keys[idx];

    if (children[idx]->keys.size() >= t) {
        int pred = getPredecessor(idx);
        keys[idx] = pred;
        children[idx]->remove(pred);
    }
    else if (children[idx + 1]->keys.size() >= t) {
        int succ = getSuccessor(idx);
        keys[idx] = succ;
        children[idx + 1]->remove(succ);
    }
    else {
        merge(idx);
        children[idx]->remove(k);
    }
}

int BTreeNode::getPredecessor(int idx) {
    auto cur = children[idx];
    while (!cur->isLeaf) cur = cur->children.back();
    return cur->keys.back();
}

int BTreeNode::getSuccessor(int idx) {
    auto cur = children[idx + 1];
    while (!cur->isLeaf) cur = cur->children.front();
    return cur->keys.front();
}

void BTreeNode::fill(int idx) {
    if (idx > 0 && children[idx - 1]->keys.size() >= t)
        borrowFromPrev(idx);
    else if (idx < keys.size() && children[idx + 1]->keys.size() >= t)
        borrowFromNext(idx);
    else {
        merge(idx);
    }
}

void BTreeNode::borrowFromPrev(int idx) {
    auto child = children[idx];
    auto sibling = children[idx - 1];

    child->keys.insert(child->keys.begin(), keys[idx - 1]);
    if (!child->isLeaf) child->children.insert(child->children.begin(), sibling->children.back());

    keys[idx - 1] = sibling->keys.back();
    sibling->keys.pop_back();
    if (!sibling->isLeaf) sibling->children.pop_back();
}

void BTreeNode::borrowFromNext(int idx) {
    auto child = children[idx];
    auto sibling = children[idx + 1];

    child->keys.push_back(keys[idx]);
    if (!child->isLeaf) child->children.push_back(sibling->children.front());

    keys[idx] = sibling->keys.front();
    sibling->keys.erase(sibling->keys.begin());
    if (!sibling->isLeaf) sibling->children.erase(sibling->children.begin());
}

void BTreeNode::merge(int idx) {
    auto child = children[idx];
    auto sibling = children[idx + 1];

    child->keys.push_back(keys[idx]);
    child->keys.insert(child->keys.end(), sibling->keys.begin(), sibling->keys.end());

    if (!child->isLeaf) child->children.insert(child->children.end(), sibling->children.begin(), sibling->children.end());

    keys.erase(keys.begin() + idx);
    children.erase(children.begin() + idx + 1);
}
