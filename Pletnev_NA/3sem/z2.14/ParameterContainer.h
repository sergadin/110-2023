#ifndef PARAMETERCONTAINER_H
#define PARAMETERCONTAINER_H

#include "Error.h"

//Структура для хранения параметров

struct ParameterValue 
{
    enum class Type { INT, DOUBLE, STRING, INT_ARRAY, DOUBLE_ARRAY };
    Type type;
    std::variant<int, double, std::string, std::vector<int>, std::vector<double>> value;
};


// Узел бинарного дерева поиска
struct Node 
{
    std::string key;             // Ключ параметра
    ParameterValue value;        // Значение параметра
    std::unique_ptr<Node> left;  // Левый потомок
    std::unique_ptr<Node> right; // Правый потомок

    // Конструктор узла
    Node() : key(""), value{} {}
    Node(const std::string& k, const ParameterValue& v) : key(k), value(v) {}

    // Конструктор перемещения (для повышения производительности)
    Node(std::string&& k, ParameterValue&& v) : key(std::move(k)), value(std::move(v)) {}
};

class ParameterContainer 
{

private:

    std::unique_ptr<Node> root_; // Корень дерева

    // Рекурсивное удаление узла
    void clearTree(std::unique_ptr<Node>& node); 

    std::string trim(const std::string& str) const; // Удаление пробелов с начала и конца строки
    std::vector<int> parseIntArray(const std::string& valueStr) const; // Разбор массива целых чисел из строки
    std::vector<double> parseDoubleArray(const std::string& valueStr) const; // Разбор массива вещественных чисел из строки
    void insert(const std::string& key, const ParameterValue& value); // Вставка узла в дерево
    std::unique_ptr<Node> insertNodeIterative(std::unique_ptr<Node> parent, const std::string& key, const ParameterValue& value);
    Node* findNode(Node* node, const std::string& key) const; // Рекурсивный поиск узла по ключу

public:

    // Конструктор: инициализирует пустое дерево
    ParameterContainer() : root_(nullptr) {};

    // Загрузка параметров из файла. Выбрасывает исключение при ошибке.
    void loadFromFile(const std::string& filename);

    // Получение параметров. Выбрасывает исключение, если ключ не найден или несоответствие типов.
    int GetInt(const std::string& key) const;
    double GetDouble(const std::string& key) const;
    const std::vector<int>& GetIntArray(const std::string& key) const;
    const std::vector<double>& GetDoubleArray(const std::string& key) const;
    const std::string& GetString(const std::string& key) const;

     // Дестрструктор: удаляет дерево начиная с корня
    ~ParameterContainer() { clearTree(root_); }
    
};

#endif