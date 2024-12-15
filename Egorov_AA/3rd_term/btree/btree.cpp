#include <vector>
#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include "btree.h"


BTree::BTree(int temp) {  // Конструктор
    root = NULL;
    t = temp;
}


// Функция, возвращающая индекс первого ключа, который больше либо равен k
int BNode::findKey(std::string k) {
    int idx = 0;
    while (idx < key_number && keys[idx] < k)
        ++idx;
    return idx;
}

// Удаление ключа k в поддереве, корнем котороая явлется этот узел
void BNode::remove(std::string k) {
    int idx = findKey(k);

    if (idx < key_number && keys[idx] == k)        // Если k в этом узле

    {
        if (leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    }
    else
    {
        // Если узел - лист, то ключа в дереве нет
        if (leaf)
        {
            return;
        }

        bool flag = ((idx == key_number) ? true : false);

        if (children[idx]->key_number < t)
            fill(idx);

        if (flag && idx > key_number)
            children[idx - 1]->remove(k);
        else
            children[idx]->remove(k);
    }
    return;
}

// Функция для удаления ключа, расположенного на позиции idx в узле-листе
void BNode::removeFromLeaf(int idx) {
    for (int i = idx + 1; i < key_number; ++i)
        keys[i - 1] = keys[i];

    key_number--;

    return;
}

// Функция для удаления ключа, расположенного на позиции idx в узле, который не является листом
void BNode::removeFromNonLeaf(int idx) {

    std::string k = keys[idx];


    if (children[idx]->key_number >= t)
    {
        std::string pred = getPred(idx);
        keys[idx] = pred;
        children[idx]->remove(pred);
    }

    else if (children[idx + 1]->key_number >= t)
    {
        std::string succ = getSucc(idx);
        keys[idx] = succ;
        children[idx + 1]->remove(succ);
    }

    else
    {
        merge(idx);
        children[idx]->remove(k);
    }
    return;
}

// Функция для получения предшественника ключа, находящегося на позиции idx
std::string BNode::getPred(int idx) {

    BNode* cur = children[idx];
    while (!cur->leaf)
        cur = cur->children[cur->key_number];

    return cur->keys[cur->key_number - 1];
}

// Функция для получения преемника ключа, находящегося на позиции idx
std::string BNode::getSucc(int idx) {

    BNode* cur = children[idx + 1];
    while (!cur->leaf)
        cur = cur->children[0];

    return cur->keys[0];
}

// Функция для заполнения дочернего узла, расположенного на позиции idx,
void BNode::fill(int idx) {

    if (idx != 0 && children[idx - 1]->key_number >= t)
        borrowFromPrev(idx);

    else if (idx != key_number && children[idx + 1]->key_number >= t)
        borrowFromNext(idx);

    else
    {
        if (idx != key_number)
            merge(idx);
        else
            merge(idx - 1);
    }
    return;
}

// Функция для заимствования ключа из узла children[idx-1] и его размещения в узле children[idx]
void BNode::borrowFromPrev(int idx) {

    BNode* child = children[idx];
    BNode* sibling = children[idx - 1];

    for (int i = child->key_number - 1; i >= 0; --i)
        child->keys[i + 1] = child->keys[i];

    if (!child->leaf)
    {
        for (int i = child->key_number; i >= 0; --i)
            child->children[i + 1] = child->children[i];
    }

    child->keys[0] = keys[idx - 1];

    if (!child->leaf)
        child->children[0] = sibling->children[sibling->key_number];

    keys[idx - 1] = sibling->keys[sibling->key_number - 1];

    child->key_number += 1;
    sibling->key_number -= 1;

    return;
}

// Функция для заимствования ключа из узла children[idx+1] и его размещения в узле children[idx]
void BNode::borrowFromNext(int idx) {

    BNode* child = children[idx];
    BNode* sibling = children[idx + 1];

    child->keys[(child->key_number)] = keys[idx];

    if (!(child->leaf))
        child->children[(child->key_number) + 1] = sibling->children[0];

    keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->key_number; ++i)
        sibling->keys[i - 1] = sibling->keys[i];

    if (!sibling->leaf)
    {
        for (int i = 1; i <= sibling->key_number; ++i)
            sibling->children[i - 1] = sibling->children[i];
    }

    child->key_number += 1;
    sibling->key_number -= 1;

    return;
}

// Функция для слияния дочернего узла children[idx] с узлом children[idx+1]
void BNode::merge(int idx) {
    BNode* child = children[idx];
    BNode* sibling = children[idx + 1];

    child->keys[t - 1] = keys[idx];

    for (int i = 0; i < sibling->key_number; ++i)
        child->keys[i + t] = sibling->keys[i];

    if (!child->leaf)
    {
        for (int i = 0; i <= sibling->key_number; ++i)
            child->children[i + t] = sibling->children[i];
    }

    for (int i = idx + 1; i < key_number; ++i)
        keys[i - 1] = keys[i];

    for (int i = idx + 2; i <= key_number; ++i)
        children[i - 1] = children[i];

    child->key_number += sibling->key_number + 1;
    key_number--;

    delete(sibling);
    return;
}

// Функция для поиска ключа в поддереве, корнем которого является данный узел
BNode* BNode::search(std::string k) {
    int i = 0;                                    // Находим первый ключ, который больше или равен k
    while (i < key_number && k > keys[i])
        i++;

    if (keys[i] == k)                             // Если найденный ключ равен k, возвращаем данный узел
        return this;

    if (leaf == true)                             // Если ключ не найден и данный узел является листом
        return NULL;

    return children[i]->search(k);                // Переходим к соответствующему дочернему узлу
}

// Вспомогательная функция для вставки нового ключа в поддерево, 
// корнем которого является этот незаполненный узел. 
void BNode::insertNonFull(std::string k) {

    int i = key_number - 1;

    if (leaf == true) {
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }

        keys[i + 1] = k;
        key_number++;
    }
    else {
        while (i >= 0 && keys[i] > k)
            i--;

        if (children[i + 1]->key_number == 2 * t - 1) {
            splitChild(i + 1, children[i + 1]);

            if (keys[i + 1] < k)
                i++;
        }
        children[i + 1]->insertNonFull(k);
    }
}

// Вспомогательная функция для разделения дочернего узла y этого узла. 
// i - индекс y в массиве children[].
void BNode::splitChild(int i, BNode* y) {
    BNode* z = new BNode(y->t, y->leaf);
    z->key_number = t - 1;

    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    if (y->leaf == false) {
        for (int j = 0; j < t; j++)
            z->children[j] = y->children[j + t];
    }

    y->key_number = t - 1;
    for (int j = key_number; j >= i + 1; j--)
        children[j + 1] = children[j];

    children[i + 1] = z;

    for (int j = key_number - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = y->keys[t - 1];
    key_number++;
}


void BTree::insert(std::string k) {
    if (root == NULL) {
        root = new BNode(t, true);
        root->keys[0] = k;
        root->key_number = 1;
    }
    else {
        if (search(k) != NULL) {
            return;
        }
        if (root->key_number == 2 * t - 1) {
            BNode* s = new BNode(t, false);

            s->children[0] = root;
            s->splitChild(0, root);

            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->children[i]->insertNonFull(k);

            root = s;
        }
        else
            root->insertNonFull(k);
    }
}

// Основная функция для удаления ключа из дерева B-дерева
void BTree::remove(std::string k) {
    if (!root)
    {
        std::cout << "The tree is empty\n";
        return;
    }

    root->remove(k);

    if (root->key_number == 0)      // Если у корня больше нет ключей, делаем его первым дочерним узлом (если он существует)
    {                               // в противном случае корень становится NULL
        BNode* tmp = root;
        if (root->leaf)
            root = NULL;
        else
            root = root->children[0];

        delete tmp;
    }
    return;
}


void BNode::clear() {
    if (!leaf) {
        for (int i = 0; i <= key_number; i++) {
            if (children[i]) {
                children[i]->clear();
                delete children[i];
            }
        }
    }
    delete[] keys;
    delete[] children;
}


void BTree::clear() {
    if (root) {
        root->clear();
        delete root;
        root = nullptr;
    }
}

// Функция для обхода всех узлов поддерева, корнем которого является этот узел
void BNode::traverse() {
    int i;
    for (i = 0; i < key_number; i++) {
        if (leaf == false)
            children[i]->traverse();
        std::cout << keys[i] << "\n";
    }

    if (leaf == false)
        children[i]->traverse();
}

void BTree::traverse() {
    if (root != NULL)
        root->traverse();
}
