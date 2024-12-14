#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <Tree.h>

int main()
{
    // Генератор чисел
    srand(static_cast<unsigned>(time(0)));

    Map<string, int> map;
    const int numOfElements = 10;
    const int keyLength = 5;

    for (int i = 0; i < numOfElements; ++i)
    {
        std::string key = generateRandomKey(keyLength);
        int value = generateRandomValue();

        map.insert(key, value);
    }

    std::cout << "Generated keys and values:" << std::endl;
    for (int i = 0; i < numOfElements; ++i)
    {
        std::string key = generateRandomKey(keyLength);
        int value = generateRandomValue();

        std::cout << key << ": " << value << std::endl;
    }

    cout << "Size of map: " << map.getSize() << endl;

    std::cout << "Elements after 'key3':" << std::endl;
    map.printAfter("key3", 7);

    std::cout << "Elements before 'key3':" << std::endl;
    map.printBefore("key3", 7);

    // Обходим дерево и выводим значения
    std::cout << "Values in the binary search tree:" << std::endl;
    map.traverse(map.getRoot());

    map.cleanUpMemory();

    return 0;
}