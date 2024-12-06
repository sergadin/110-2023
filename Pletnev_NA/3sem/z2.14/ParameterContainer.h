#ifndef PARAMETERCONTAINER_H
#define PARAMETERCONTAINER_H

#include "Error.h"

// Структура для хранения значения параметра
struct ParameterValue 
{

    enum Type {INT, DOUBLE, INT_ARRAY, DOUBLE_ARRAY, STRING};
    Type type;

    union {
        int intValue;
        double doubleValue;
        std::vector<int> *intArray; 
        std::vector<double> *doubleArray;
        std::string *stringValue;
    };

    ~ParameterValue() = default;
};


// Узел бинарного дерева поиска
struct Node 
{
    std::string key;
    ParameterValue value;
    Node *left, *right;
    Node(const std::string& k, const ParameterValue& v) : key(k), value(v), left(nullptr), right(nullptr) {}
};

class ParameterContainer 
{
private:

    Node *root;

    // Вспомогательная функция для рекурсивного поиска
    ParameterValue* search(Node* node, const char* key) 
    {
        if (node == nullptr || strcmp(node->key.c_str(), key) == 0) 
        {
            return (node == nullptr) ? nullptr : &(node->value);
        }

        if (strcmp(node->key.c_str(), key) < 0)
        {
            return search(node->right, key);
        }

        return search(node->left, key);
    }

    // Рекурсивная функция для удаления всех узлов дерева
    void clearTree(Node* node) 
    {
        if (node != nullptr) 
        {
            clearTree(node->left);
            clearTree(node->right);
            delete node;
        }
    }

    // Вспомогательная функция для рекурсивного вставки
    void insert(Node* &node, const std::string& key, const ParameterValue& value) 
    {
        if (node == nullptr) 
        {
            node = new Node(key, value);
            return;
        }
        if (key < node->key) insert(node->left, key, value);
        else if (key > node->key) insert(node->right, key, value);
        else 
        {
            throw Error(-101, "Key already exists"); //Обработка дубликатов ключей
        }
    }

public: 
    ParameterContainer() : root(nullptr) {}
    ~ParameterContainer() { clearTree(root); }

    void insert(const std::string& key, const ParameterValue& value) { insert(root, key, value); }

    ParameterValue* get(const char* key) 
    {
        ParameterValue* pv = search(root, key);
        if (pv == nullptr) 
        {
            throw Error(-102, "Key not found"); //Обработка отсутствия ключа
        }
        return pv;
    }

    int GetInt(const char* key) 
    {
        ParameterValue* pv = get(key);
        if (pv->type != ParameterValue::INT) 
        {
            throw Error(-110, "Incorrect parameter type GetInt");
        }
        return pv->intValue;
    }

    double GetDouble(const char* key) 
    {
        ParameterValue* pv = get(key);
        if (pv->type != ParameterValue::DOUBLE) 
        {
            throw Error(-111, "Incorrect parameter type GetDouble");
        }
        return pv->doubleValue;
    }

    const int* ParameterContainer::GetIntArray(const std::string& key) 
    {
        ParameterValue* pv = get(key);
        if (std::holds_alternative<std::vector<int>>(pv->value)) 
        {
            return std::get<std::vector<int>>(pv->value).data(); // Возвращает указатель на начало вектора
        } else {
            throw Error(-112, "Incorrect parameter type GetIntArray");
        }
    }


    const double* ParameterContainer::GetDoubleArray(const std::string& key) 
    {
        ParameterValue* pv = get(key);
        if (std::holds_alternative<std::vector<double>>(pv->value)) 
        {
            return std::get<std::vector<double>>(pv->value).data(); // Возвращает указатель на начало вектора
        } else {
            throw Error(-113, "Incorrect parameter type GetDoubleArray");
        }
    }

    const char* ParameterContainer::GetString(const std::string& key) 
    {
        ParameterValue* pv = get(key);
        if (std::holds_alternative<std::string>(pv->value)) 
        {
            return std::get<std::string>(pv->value).c_str(); // Возвращает c_str() строки
        } else {
            throw Error(-114, "Incorrect parameter type GetString");
        }
    }

};

#endif