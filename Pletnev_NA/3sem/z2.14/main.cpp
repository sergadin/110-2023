#include "ParameterContainer.h"

int main() 
{
    ParameterContainer pc;
    pc.loadFromFile("test.txt");

    try 
    {
        std::cout << "Int: " << pc.GetInt("myInt") << std::endl;

        std::cout << "Double: " << pc.GetDouble("myDouble") << std::endl;

        auto intArray = pc.GetIntArray("myArrayInt");
        std::cout << "IntArray: ";
        for (int x : intArray) std::cout << x << " ";
        std::cout << std::endl;

        auto doubleArray = pc.GetDoubleArray("myArrayDouble");
        std::cout << "DoubleArray: ";
        for (double x : doubleArray) std::cout << x << " ";
        std::cout << std::endl;

        std::cout << "String: " << pc.GetString("myString") << std::endl;

        std::cout << "myR1: " << pc.GetInt("myR1") << std::endl;
        std::cout << "myR2: " << pc.GetString("myR2") << std::endl;

        std::cout << "String2: " << pc.GetString("myString2") << std::endl; //Проверка несуществующего ключа
        std::cout << "Int: " << pc.GetDouble("myInt") << std::endl; //Проверка неверного значения

    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}