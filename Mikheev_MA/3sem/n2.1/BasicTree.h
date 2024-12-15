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
    NodeOfTree* left; // левый потомок
    NodeOfTree* right; // правый потомок
    
    NodeOfTree(const std::string& k, const T& v) : key(k), value(v), left(nullptr), right(nullptr) {} // конструктор
    
};


template <typename T>
class Map{ // класс дерева
private:

    NodeOfTree<T>* root; // корень дерева
    
    // добавление вершины 
    void add(NodeOfTree<T>*& node, const std::string& key, const T& value){
        
        if(!node){
            node = new NodeOfTree<T>(key, value);
            // ??return
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
    NodeOfTree<T>* search(NodeOfTree<T>*& node, const std::string& key){
        
        if(!node){
            return nullptr;
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
    void remove(NodeOfTree<T>*& node, const std::string& key){
        
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
                NodeOfTree<T>* cureent = node;
                node = node -> right;
                delete cureent;
            }
            
            else if(!node -> right){ // отсутствие правой втеки
                NodeOfTree<T>* cureent = node;
                node = node -> left;
                delete cureent;
            }
            
            else{ // случай, когда вершина дерева имеет 2 ветви
                NodeOfTree<T>* cureent = SearchingMinNode(node -> right);
                node -> key = cureent -> key;
                node -> value = cureent -> value;
                remove(node->right, cureent -> key);
            }
        
        }
        
    }
    
    // Поиск минимального приемника для удаления узла с двумя ветвями
    NodeOfTree<T>* SearchingMinNode(NodeOfTree<T>* node){
       while(node && node -> left){
           node = node -> left;
       }
       
       return node;
    }
    
    // упорядоченный список ключей
    void OrderedList(NodeOfTree<T>* node){
        
        if(node){
            OrderedList(node -> left);
            std::cout << "Ключ - " << node -> key << "; Значение - " << node -> value << std::endl;
            OrderedList(node -> right);
        }
        
    }
    
    // подсчет количества ключей
    int Keys(NodeOfTree<T>* node){
        if(!node){
            return 0;
        }
        return Keys(node -> left) + Keys(node -> right) + 1;
    }
    
    
public:

    Map() : root(nullptr){}
    
    ~Map(){  // деструктор
        clear(root);
    }
    
    void clear(NodeOfTree<T>* node){ // Функция удаления
        if(node){
            clear(node -> left);
            clear(node -> right);
            delete node;
        }
    }
    
    void add(const std::string& key, const T& value){ //добавление вершины 
        add(root, key, value);
    }
    
    T search(const std::string& key){ // поиск значения по ключу
        NodeOfTree<T>* node = search(root, key);
        
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
    static const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    
    std::string key;
    
    for(int i = 0; i < length; i++){
        key = key + alphabet[rand() % (sizeof(alphabet) - 1)];
    }
    
    return key;
}

int GenRandomString(){ // Функция, генерирующая рандомное значение
    return rand() % 100;
}
