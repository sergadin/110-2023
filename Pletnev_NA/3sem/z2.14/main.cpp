#include "ParameterContainer.h"

int main() 
{
    std::cout << "test 1: " << std::endl;
    ParameterContainer pc1;
    pc1.loadFromFile("test1.txt");

    try 
    {
        std::cout << "String: " << pc1.GetString("myString") << std::endl; //Проверка несуществующего ключа

    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }


     try 
    {
        std::cout << "myArrayDouble: " << pc1.GetDouble("myArrayDouble") << std::endl; //Проверка несуществующего ключа

    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << "test 2: " << std::endl;
    ParameterContainer pc2;
    pc2.loadFromFile("test2.txt");

    try 
    {
        std::cout << "String2: " << pc2.GetString("myString2") << std::endl; //Проверка несуществующего ключа

    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    std::cout << "test 3: " << std::endl;
    ParameterContainer pc3;
    pc3.loadFromFile("test3.txt");

    try 
    {
        std::cout << "Int: " << pc3.GetInt("myInt") << std::endl; //Проверка неверного значения
        std::cout << "Int2: " << pc3.GetInt("myInt2") << std::endl; //Проверка неверного значения

    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << "test 4: " << std::endl;
    ParameterContainer pc4;
    pc4.loadFromFile("test4.txt");

    try 
    {
        std::cout << "Int: " << pc4.GetInt("myInt") << std::endl;

        std::cout << "Double: " << pc4.GetDouble("myDouble") << std::endl;

        auto intArray = pc4.GetIntArray("myArrayInt");
        std::cout << "IntArray: ";
        for (int x : intArray) std::cout << x << " ";
        std::cout << std::endl;

        auto doubleArray = pc4.GetDoubleArray("myArrayDouble");
        std::cout << "DoubleArray: ";
        for (double x : doubleArray) std::cout << x << " ";
        std::cout << std::endl;

        std::cout << "String: " << pc4.GetString("myString") << std::endl;

        std::cout << "myR1: " << pc4.GetInt("myR1") << std::endl;
        std::cout << "myR2: " << pc4.GetString("myR2") << std::endl;

        auto doubleArray2 = pc4.GetDoubleArray("myArrayDouble2");
        std::cout << "DoubleArray2: ";
        for (double x : doubleArray2) std::cout << x << " ";
        std::cout << std::endl;

        auto doubleArray3 = pc4.GetDoubleArray("myArrayDouble3");
        std::cout << "DoubleArray3: ";
        for (double x : doubleArray3) std::cout << x << " ";
        std::cout << std::endl;

    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    std::cout << "test 5: " << std::endl;
    ParameterContainer pc5;
    pc5.loadFromFile("test5.txt");

    try 
    {
        std::cout << "myR2: " << pc5.GetString("myR2") << std::endl;

    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}