#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "BasicTree.h"




int main()
{
    srand((time(0)));
    
    Map<int> map; // создание дерева
    int KeyLength = 5; // длина ключа
    int Keys = 10; // количество ключей
    
    std::cout << "Генерация рандомых ключей и значений к ним" << std::endl; // генерируем ключи и значения
    for(int i = 0; i < Keys; i++){
        
        std::string key = GenRandomString(KeyLength);
        int value = GenRandomString();
        
        std::cout << "Ключ - " << key << "; Значение - " << value << "  \n";
        
        map.add(key, value);
    }
    
    std::cout << std::endl << "Вывод сгенерированных ключей и значений:\n"; // вывод ключей + значения
    map.OrderedList();
    std::cout << "Количество ключей - " << map.Keys() << std::endl;
    std::cout <<  std::endl;
    
    map.add("qqQQQQQQ", 999); // добавим ключ и значение 
    std::cout << "Вывод сгенерированных ключей и значений после добавления:\n"; // выводим новый список
    map.OrderedList();
    std::cout << "Количество ключей - " << map.Keys() << std::endl;
    std::cout <<  std::endl;
    
    try{                                                                       // поиск ключа и вывод значения
        std::cout << "Значение искомого ключа - " << map.search("qqQQQQQQ") << std::endl;
    }
    catch(int err){
        if(err == 0){
            std::cout << "Данный ключ не найден\n" << std::endl;
        }
    }
    
    try{                                                                      // поиск ключа, которого не существует
        std::cout << "Значение искомого ключа - " << map.search("AAAAAA") << std::endl;
    }
    catch(int err){
        if(err == 0){
            std::cout << "Данный ключ не найден\n" << std::endl;
        }
    }
    
    
    map.remove("qqQQQQQQ");       // удаление раннее добавленного ключа
    std::cout << "Вывод сгенерированных ключей и значений после удаления:\n";
    map.OrderedList();
    std::cout << "Количество ключей - " << map.Keys() << std::endl;
    std::cout <<  std::endl;
    

    return 0;
}