#include <iostream>
#include <string>
#include <memory>
#include <iterator>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

template <typename T>
class NodeOfTree{ // класс вершины дерева
public:
    
    std::string key; // ключ
    T value; // значение 
    std::shared_ptr<NodeOfTree<T>> left; // левый потомок
    std::shared_ptr<NodeOfTree<T>> right; // правый потомок
    
    NodeOfTree(const std::string& k, const T& v) : key(k), value(v), left(nullptr), right(nullptr) {} // конструктор
    
};


template <typename T>
class Map{ // класс дерева
private:

    std::shared_ptr<NodeOfTree<T>> root; // корень дерева
    
    // добавление вершины 
    void add(std::shared_ptr<NodeOfTree<T>>& node, const std::string& key, const T& value){
        
        if(!node){
            node = std::make_shared<NodeOfTree<T>>(key, value);
        }
        
        if(key < node -> key){
            add(node -> left, key, value);
        }
        
        else if(key > node -> key){
            add(node -> right, key, value);
        }
        
        else{
            node -> value = value;
        }
    }
    
    // поиск узла по ключу
    std::shared_ptr<NodeOfTree<T>> search(std::shared_ptr<NodeOfTree<T>>& node, const std::string& key){
        
        if(!node){
            return node;
        }
        
        if(key < node -> key){
            return search(node -> left, key);
        }
        
        if(key > node -> key){
            return search(node -> right, key);
        }
        
        else{ // случай (node -> key == key)
            return node;
        }
    }
    
    // удаление узла
    void remove(std::shared_ptr<NodeOfTree<T>>& node, const std::string& key){
        
        if(!node){
            return;
        }
        
        if(key < node -> key){
            remove (node -> left, key);
        }
        else if(key > node -> key){
            remove (node -> right, key);
        }
        
        else{ // нашли нужный ключ
            
            if(!node -> left){  // отсутствие левой ветки
                node = node -> right;
            }
            
            else if(!node -> right){ // отсутствие правой втеки
                node = node -> left;
            }
            
            else{ // случай, когда вершина дерева имеет 2 ветви
                std::shared_ptr<NodeOfTree<T>> Min = SearchingMinNode(node -> right);
                node -> key = Min -> key;
                node -> value = Min -> value;
                remove(node->right, Min -> key);
            }
        
        }
        
    }
    
    // Поиск минимального приемника для удаления узла с двумя ветвями
    std::shared_ptr<NodeOfTree<T>> SearchingMinNode(std::shared_ptr<NodeOfTree<T>> node){
       while(node && node -> left){
           node = node -> left;
       }
       
       return node;
    }
    
    // упорядоченный список ключей
    void OrderedList(std::shared_ptr<NodeOfTree<T>>& node){
        
        if(node){
            OrderedList(node -> left);
            std::cout << "Ключ - " << node -> key << "; Значение - " << node -> value << std::endl;
            OrderedList(node -> right);
        }
        
    }
    
    // подсчет количества ключей
    int Keys(std::shared_ptr<NodeOfTree<T>>& node){
        if(!node){
            return 0;
        }
        return Keys(node -> left) + Keys(node -> right) + 1;
    }
    
    
public:

    Map() : root(nullptr){}
    
    void add(const std::string& key, const T& value){ //добавление вершины 
        add(root, key, value);
    }
    
    T search(const std::string& key){ // поиск значения по ключу
        std::shared_ptr<NodeOfTree<T>> node = search(root, key);
        
        if(node){
            return node -> value; // Возвращение значения ключа
        }
        else{
            throw 0; // Если ключ не найден
        }
    }
    
    void remove(const std::string& key){ // удаление ключа
        remove(root, key);
    }
    
    int Keys(){ // количество ключей
        return Keys(root);    
    }
    
    void OrderedList(){ // список всех ключей
        OrderedList(root);
    }
    
};





std::string GenRandomString(int length){ // Функция, генерирующая рандомный ключ
    static const char alphabet[]{
        "abcdefghijklmnopqrstuvwxyz"
    };
    
    std::string key;
    
    for(int i = 0; i < length; i++){
        key = key + alphabet[rand() % (sizeof(alphabet) - 1)];
    }
    
    return key;
}

int GenRandomString(){ // Функция, генерирующая рандомное значение
    return rand() % 100;
}
