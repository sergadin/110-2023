#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

template<typename K, typename V>
class Map
{
private:
    struct Node
    {
        K key;
        V value;
        Node* left;
        Node* right;
        Node(K k, V v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };
    Node* root;
    int size;

    // Заполнение дерева
    void insert(Node*& node, K key, V value)
    {
        if (node == nullptr)
        {
            node = new Node(key, value);
            size++;
        }

        else if (key < node->key)
        {
            insert(node->left, key, value);
        }

        else if (key > node->key)
        {
            insert(node->right, key, value);
        }

        else
        {
            node->value = value; // Обновление значения если ключ уже занят
        }
    }

    // Поиск значения
    V search(Node* node, K key)
    {
        if (node == nullptr)
        {
            cerr << "Key not found" << endl;
            exit(1);
        }

        if (key < node->key)
        {
            return search(node->left, key);
        }

        else if (key > node->key)
        {
            return search(node->right, key);
        }

        else
        {
            return node->value;
        }
    }

    // Удаление
    Node* remove(Node* node, K key)
    {
        if (node == nullptr)
        {
            cerr << "Key not found" << endl;
            return nullptr;
        }

        if (key < node->key)
        {
            node->left = remove(node->left, key);
        }

        else if (key > node->key)
        {
            node->right = remove(node->right, key);
        }

        else
        {
            if (node->left == nullptr)
            {
                Node* temp = node->right;
                delete node;
                size--;
                return temp;
            }

            else if (node->right == nullptr)
            {
                Node* temp = node->left;
                delete node;
                size--;
                return temp;
            }
            Node* temp = minValueNode(node->right);
            node->key = temp->key;
            node->value = temp->value;
            node->right = remove(node->right, temp->key);
        }
        return node;
    }

    Node* minValueNode(Node* node)
    {
        Node* current = node;
        while (current && current->left != nullptr)
        {
            current = current->left;
        }
        return current;
    }

    // Перемещение по дереву направо
    void printInOrderRight(Node* current, K key, V value)
    {
        if (current == nullptr)
        {
            return;
        }

        printInOrderRight(current->left, key, value);

        if (current->key > key)
        {
            std::cout << current->key << " : " << current->value << std::endl;
        }

        printInOrderRight(current->right, key, value);
    }

    // Перемещение по дереву налево
    void printInOrderLeft(Node* current, K key, V value)
    {
        if (current == nullptr)
        {
            return;
        }

        printInOrderLeft(current->right, key, value);

        if (current->key < key)
        {
            std::cout << current->key << " : " << current->value << std::endl;
        }

        printInOrderLeft(current->left, key, value);
    }


public:
    Map() : root(nullptr), size(0) {}

    void insert(K key, V value)
    {
        insert(root, key, value);
    }

    V search(K key)
    {
        return search(root, key);
    }

    void remove(K key)
    {
        root = remove(root, key);
    }

    int getSize()
    {
        return size;
    }

    // Рекурсивная функция для обхода дерева и запоминания значений
    void traverse(Node* node) {
        if (node == nullptr) {
            return;
        }

        traverse(node->left);
        std::cout << "Key: " << node->key << ", Value: " << node->value << std::endl;
        traverse(node->right);
    }

    Node* getRoot()
    {
        return root;
    }

    // Запись элементов после
    void printAfter(K key, V value)
    {
        printInOrderRight(root, key, value);
    }

    // Запись элементов до
    void printBefore(K key, V value)
    {
        printInOrderLeft(root, key, value);
    }

    // Очистка памяти
    void cleanUpMemory() {
        cleanUpMemory(root);
        root = nullptr;
    }

    void cleanUpMemory(Node* node) {
        if (node != nullptr) {
            cleanUpMemory(node->left);
            cleanUpMemory(node->right);
            delete node;
        }
    }

};

// Генератор ключей и чисел
std::string generateRandomKey(int length)
{
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    std::string key;
    for (int i = 0; i < length; ++i)
    {
        key += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return key;
}

int generateRandomValue()
{
    return rand() % 100;
}