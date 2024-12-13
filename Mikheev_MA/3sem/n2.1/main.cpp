#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "BasicTree.h"




int main()
{
    srand((time(0)));
    
    Map<int> map;
    int KeyLength = 5;
    int Keys = 10;
    
    std::cout << "Генерация рандомых ключей и значений к ним" << std::endl; 
    for(int i = 0; i < Keys; i++){
        
        std::string key = GenRandomString(KeyLength);
        int value = GenRandomString();
        
        std::cout << "Ключ - " << key << "; Значение - " << value << "  \n";
        
        map.add(key, value);
    }
    
    std::cout << std::endl << "Вывод сгенерированного дерева:\n";
    map.OrderedList();
    std::cout << "Количество ключей - " << map.Keys() << std::endl;
    std::cout <<  std::endl;
    
    map.add("qqQQQQQQ", 999);
    std::cout << "Вывод сгенерированного дерева после добавления:\n";
    map.OrderedList();
    std::cout << "Количество ключей - " << map.Keys() << std::endl;
    std::cout <<  std::endl;
    
    try{
        std::cout << "Значение искомого ключа - " << map.search("qqQQQQQQ") << std::endl;
    }
    catch(int err){
        if(err == 0){
            std::cout << "Данный ключ не найден\n" << std::endl;
        }
    }
    
    try{
        std::cout << "Значение искомого ключа - " << map.search("AAAAAA") << std::endl;
    }
    catch(int err){
        if(err == 0){
            std::cout << "Данный ключ не найден\n" << std::endl;
        }
    }
    
    
    map.remove("qqQQQQQQ");
    std::cout << "Вывод сгенерированного дерева после удаления:\n";
    map.OrderedList();
    std::cout << "Количество ключей - " << map.Keys() << std::endl;
    std::cout <<  std::endl;
    

    return 0;
}