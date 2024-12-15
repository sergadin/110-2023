#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include "btree.h"


void BTree::insert(const std::string& value) {
    if (root->keys.size() == 2 * T - 1) {
        BTreeNode* newRoot = new BTreeNode(false);
        newRoot->children.push_back(root);
        splitChild(newRoot, 0);
        root = newRoot;
    }
    insertNonFull(root, new std::string(value));
    ++size;
}


bool BTree::remove(const std::string& value){
    if (!contains(value)) {
        return false;
    }
    removeFromNode(root, value);
    if (!root->isLeaf && root->keys.empty()) {
        BTreeNode* oldRoot = root;
        root = root->children[0];
        delete oldRoot;
    }
    --size;
    return true;
}


bool BTree::contains(const std::string& value) {
    return search(root, value) != nullptr;
}


size_t BTree::count() const {
    return size;
}


void BTree::splitChild(BTreeNode* parent, int idx) {
    BTreeNode* child = parent->children[idx];
    BTreeNode* newChild = new BTreeNode(child->isLeaf);

    parent->keys.insert(parent->keys.begin() + idx, child->keys[T - 1]);
    parent->children.insert(parent->children.begin() + idx + 1, newChild);

    newChild->keys.assign(child->keys.begin() + T, child->keys.end());
    child->keys.resize(T - 1);

    if (!child->isLeaf) {
        newChild->children.assign(child->children.begin() + T, child->children.end());
        child->children.resize(T);
    }
}


void BTree::insertNonFull(BTreeNode* node, std::string* value) {
    if (node->isLeaf) {
        auto pos = std::lower_bound(node->keys.begin(), node->keys.end(), value, comparePointers);
        node->keys.insert(pos, value);
    }
    else {
        auto pos = std::upper_bound(node->keys.begin(), node->keys.end(), value, comparePointers) - node->keys.begin();
        if (node->children[pos]->keys.size() == 2 * T - 1) {
            splitChild(node, pos);
            if (*value > *node->keys[pos]) {
                ++pos;
            }
        }
        insertNonFull(node->children[pos], value);
    }
}


void BTree::removeFromNode(BTreeNode* node, const std::string& value) {
    int idx = findKey(node, value);

    if (idx < int(node->keys.size()) && *node->keys[idx] == value) {
        if (node->isLeaf) {
            delete node->keys[idx];
            node->keys.erase(node->keys.begin() + idx);
        }
        else {
            if (node->children[idx]->keys.size() >= T) {
                std::string* pred = getPredecessor(node, idx);
                *node->keys[idx] = *pred;
                removeFromNode(node->children[idx], *pred);
            }
            else if (node->children[idx + 1]->keys.size() >= T) {
                std::string* succ = getSuccessor(node, idx);
                *node->keys[idx] = *succ;
                removeFromNode(node->children[idx + 1], *succ);
            }
            else {
                merge(node, idx);
                removeFromNode(node->children[idx], value);
            }
        }
    }
    else {
        if (node->isLeaf) {
            return;
        }

        bool flag = (idx == int(node->keys.size()));

        if (node->children[idx]->keys.size() < T) {
            fill(node, idx);
        }

        if (flag && idx > int(node->keys.size())) {
            removeFromNode(node->children[idx - 1], value);
        }
        else {
            removeFromNode(node->children[idx], value);
        }
    }
}


int BTree::findKey(BTreeNode* node, const std::string& value) {
    int idx = 0;
    while (idx < int(node->keys.size()) && *node->keys[idx] < value) {
        ++idx;
    }
    return idx;
}


std::string* BTree::getPredecessor(BTreeNode* node, int idx) {
    BTreeNode* cur = node->children[idx];
    while (!cur->isLeaf) {
        cur = cur->children[cur->keys.size()];
    }
    return cur->keys.back();
}


std::string* BTree::getSuccessor(BTreeNode* node, int idx) {
    BTreeNode* cur = node->children[idx + 1];
    while (!cur->isLeaf) {
        cur = cur->children[0];
    }
    return cur->keys[0];
}


void BTree::merge(BTreeNode* node, int idx) {
    BTreeNode* child = node->children[idx];
    BTreeNode* sibling = node->children[idx + 1];

    child->keys.push_back(node->keys[idx]);
    child->keys.insert(child->keys.end(), sibling->keys.begin(), sibling->keys.end());

    if (!child->isLeaf) {
        child->children.insert(child->children.end(), sibling->children.begin(), sibling->children.end());
    }

    node->keys.erase(node->keys.begin() + idx);
    node->children.erase(node->children.begin() + idx + 1);

    delete sibling;
}


void BTree::fill(BTreeNode* node, int idx) {
    if (idx != 0 && node->children[idx - 1]->keys.size() >= T) {
        borrowFromPrev(node, idx);
    }
    else if (idx != int(node->keys.size()) && node->children[idx + 1]->keys.size() >= T) {
        borrowFromNext(node, idx);
    }
    else {
        if (idx != int(node->keys.size())) {
            merge(node, idx);
        }
        else {
            merge(node, idx - 1);
        }
    }
}


void BTree::borrowFromPrev(BTreeNode* node, int idx) {
    BTreeNode* child = node->children[idx];
    BTreeNode* sibling = node->children[idx - 1];

    child->keys.insert(child->keys.begin(), node->keys[idx - 1]);

    if (!child->isLeaf) {
        child->children.insert(child->children.begin(), sibling->children.back());
        sibling->children.pop_back();
    }

    node->keys[idx - 1] = sibling->keys.back();
    sibling->keys.pop_back();
}


void BTree::borrowFromNext(BTreeNode* node, int idx) {
    BTreeNode* child = node->children[idx];
    BTreeNode* sibling = node->children[idx + 1];

    child->keys.push_back(node->keys[idx]);

    if (!child->isLeaf) {
        child->children.push_back(sibling->children[0]);
        sibling->children.erase(sibling->children.begin());
    }

    node->keys[idx] = sibling->keys[0];
    sibling->keys.erase(sibling->keys.begin());
}


std::string* BTree::search(BTreeNode* node, const std::string& value) {
    auto it = std::lower_bound(node->keys.begin(), node->keys.end(), &value, comparePointers);
    int idx = it - node->keys.begin();
    if (it != node->keys.end() && **it == value) {
        return *it;
    }
    if (node->isLeaf) {
        return nullptr;
    }
    else {
        return search(node->children[idx], value);
    }
}


void BTree::clear(BTreeNode* node) {
    if (node == nullptr) return;
    for (auto child : node->children) {
        clear(child);
    }
    for (auto key : node->keys) {
        delete key;
    }
    delete node;
}

