#include "ParameterContainer.h"

int main() 
{

    
    ParameterContainer pc1;
    pc1.loadFromFile("test1.txt");

    try 
    {
        std::cout << "String: " << pc1.GetString("myString") << std::endl; //Проверка несуществующего ключа

    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    ParameterContainer pc2;
    pc2.loadFromFile("test2.txt");

    try 
    {
        std::cout << "String2: " << pc2.GetString("myString2") << std::endl; //Проверка несуществующего ключа

    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    ParameterContainer pc3;
    pc3.loadFromFile("test3.txt");

    try 
    {
        std::cout << "Int: " << pc3.GetInt("myInt") << std::endl; //Проверка неверного значения

    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }


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

    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }


    return 0;
}