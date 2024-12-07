#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <set>

class BTree {
private:
    std::set<std::string> tree;

public:
    // Добавить строку в множество
    void add(const std::string& str) {
        tree.insert(str);
    }

    // Удалить строку из множества
    void remove(const std::string& str) {
        tree.erase(str);
    }

    // Искать строку в множестве
    bool find(const std::string& str) const {
        return tree.find(str) != tree.end();
    }

    // Получить количество элементов в множестве
    size_t size() const {
        return tree.size();
    }

    // Итератор по части множества (от заданной строки)
    void iterateFrom(const std::string& start, bool forward = true) const {
        auto it = tree.find(start);
        if (it == tree.end()) {
            std::cout << "Строка не найдена.\n";
            return;
        }

        std::cout << "Итерация от строки \"" << start << "\":\n";
        if (forward) {
            for (auto iter = it; iter != tree.end(); ++iter) {
                std::cout << *iter << "\n";
            }
        } else {
            for (auto iter = std::make_reverse_iterator(it); iter != tree.rend(); ++iter) {
                std::cout << *iter << "\n";
            }
        }
    }

    // Загрузить строки из файла
    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Не удалось открыть файл: " << filename << "\n";
            return;
        }
        std::string line;
        while (std::getline(file, line)) {
            add(line);
        }
    }

    // Автоматическая генерация множества (тестовая)
    void generateTestData(size_t count) {
        for (size_t i = 0; i < count; ++i) {
            add("String_" + std::to_string(i));
        }
    }

    // Вывести все строки множества
    void printAll() const {
        std::cout << "Содержимое множества:\n";
        for (const auto& str : tree) {
            std::cout << str << "\n";
        }
    }
};

// Пример использования
int main() {
    BTree btree;

    // Загрузка из файла
    btree.loadFromFile("input.txt");

    // Автоматическая генерация данных
    btree.generateTestData(10);

    // Вывод всех элементов
    btree.printAll();

    // Добавить строку
    btree.add("Example_String");
    std::cout << "\nПосле добавления строки:\n";
    btree.printAll();

    // Удалить строку
    btree.remove("String_5");
    std::cout << "\nПосле удаления строки String_5:\n";
    btree.printAll();

    // Найти строку
    std::cout << "\nИщем строку 'Example_String': "
              << (btree.find("Example_String") ? "Найдена" : "Не найдена") << "\n";

    // Итерация от строки
    btree.iterateFrom("String_3");

    return 0;
}
