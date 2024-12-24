#pragma once
#include <algorithm>
#include <iostream>
#include <fstream>

class Err {
        private:
        int code_;
        std::string message_;

        public:
        Err(int code, std::string message): code_(code), message_(message) {}
        int errCode() {
                return code_;
        }

        std::string errMessage() {
                return message_;
        }
};

namespace Tree {
        template <typename T>
        class Node  {
        public:
                std::string str_value;
                T key;
                int height;
                Node* left;
                Node* right;

                Node() // default constructor
                        : str_value("")
                        , key{}
                        , left(nullptr)
                        , right(nullptr)
                        , height(0)
                {}

                Node(const std::string& s, T key) // key-value constructor
                        : str_value(s)
                        , key(key)
                        , left(nullptr)
                        , right(nullptr)
                        , height(1) 
                {}
        };

        template <typename T> 
        class AVL {
                private:
                Node<T>* root;

                void clear(Node<T>* node) {
                        if (node != nullptr)
                        {
                                clear(node->left);
                                clear(node->right);
                                delete node;
                        }
                }

                int height(Node<T>* node) {
                        if (node == nullptr)
                                return 0;
                        return node->height;
                }
                // check if tree is balanced
                int balance_factor(Node<T>* node) {
                        if (node == nullptr) 
                                return 0;
                        return height(node->left) - height(node->right);

                }

                Node<T>* rightRotate(Node<T>* p) {
                        Node<T>* q = p->left;
                        Node<T>* tmp = q->right;

                        q->right = p;
                        p->left = tmp;

                        p->height = std::max(height(p->left), height(p->right)) + 1;
                        q->height = std::max(height(q->left), height(q->right)) + 1;

                        return q;
                }

                Node<T>* leftRotate(Node<T>* p) {
                        Node<T>* q = p->right;
                        Node<T>* tmp = q->left;

                        q->left = p;
                        p->right = tmp;

                        p->height = std::max(height(p->left), height(p->right)) + 1;
                        q->height = std::max(height(q->left), height(q->right)) + 1;

                        return q;
                }

                Node<T>* insert(Node<T>* node, const std::string &s, T key) {
                        if (node == nullptr)
                            return new Node<T>(s, key);

                        if (key < node->key)
                            node->left = insert(node->left, s, key);
                        else if (key > node->key)
                            node->right = insert(node->right, s, key);
                        else
                            return node;

                        node->height = 1 + std::max(height(node->left), height(node->right));

                        // check if our tree is balanced
                        int balance = balance_factor(node);

                        // we have 4 cases
                        if (balance > 1 && key < node->left->key)
                            return rightRotate(node);

                        if (balance < -1 && key > node->right->key)
                            return leftRotate(node);

                        if (balance > 1 && key > node->left->key) {
                            node->left = leftRotate(node->left);
                            return rightRotate(node);
                        }

                        if (balance < -1 && key < node->right->key) {
                            node->right = rightRotate(node->right);
                            return leftRotate(node);
                        }

                        return node;

                }

                // finding node with minimum key value
                Node<T>* minimumNode(Node<T>* node) {
                        Node<T>* cur = node;
                        while (cur->left != nullptr) // go to the left branch 'till you can
                                cur = cur->left;
                        return cur;

                }
                Node<T>* deleteNode(Node<T> *root, T key) {
                        if (root == nullptr)
                                return root;

                        if (key < root->key)
                            root->left = deleteNode(root->left, key);

                        else if (key > root->key)
                            root->right = deleteNode(root->right, key);

                        else {
                            if ((root->left == nullptr) || (root->right == nullptr)) {
                                Node<T>* tmp = root->left ? root->left : root->right;
                                if (tmp == nullptr) {
                                    tmp = root;
                                    root = nullptr;
                                }
                                else
                                    *root = *tmp;
                                delete tmp;
                            }
                            else {
                                Node<T>* tmp = minimumNode(root->right);
                                root->key = tmp->key;
                                root->str_value = tmp->str_value;
                                root->right = deleteNode(root->right, tmp->key);
                            }
                        }

                        if (root == nullptr)
                            return root;

                        root->height = 1 + std::max(height(root->left), height(root->right));

                        // check if our tree is balance
                        int balance = balance_factor(root);


                        // we have 4 cases
                        if (balance > 1 && balance_factor(root->left) >= 0)
                            return rightRotate(root);

                        if (balance > 1 && balance_factor(root->left) < 0) {
                            root->left = leftRotate(root->left);
                            return rightRotate(root);
                        }

                        if (balance < -1 && balance_factor(root->right) <= 0)
                            return leftRotate(root);

                        if (balance < -1 && balance_factor(root->right) > 0) {
                            root->right = rightRotate(root->right);
                            return leftRotate(root);
                        }

                        return root;
                }

                std::string search(Node<T>* root, T key) {
                        if (root == nullptr)
                                return "";
                        if (root->key == key)
                                return root->str_value;
                        if (key < root->key)
                                return search(root->left, key);
                        return search(root->right, key);

                }

                void print_order(Node<T>* root) {
                        if (root != nullptr) {
                                print_order(root->left);
                                std::cout << "(" << root->str_value << ": " << root->key << ")" << " ";
                                print_order(root->right);
                        }
                }

                public:
                AVL() : root(nullptr) {}

                ~AVL() {
                        clear(root);
                }

                void insert(const std::string& s, T key) {
                        root = insert(root, s, key);
                }
                void remove(T key) {
                        root = deleteNode(root, key);
                }
                std::string search(T key) {
                        return search(root, key);
                }
                void print() {
                        print_order(root);
                        std::cout << std::endl;
                }

                void fileInput(const std::string& filename) {
                        std::ifstream input_file(filename);
                        if (!input_file.is_open()) {
                                throw Err(-1, std::string("Cannot open file!\n"));
                        }

                        std::string s;
                        std::string type;
                        T val;

                        std::getline(input_file, type);
                        if (type.empty()){
                        input_file.close();
                        throw Err(-2, std::string("Cannot identify type\n"));
                        }
                        if (type == "std::string") {
                                while (input_file >> s >> val) {
                                        this->insert(s, val);
                        }

                        }
                        else if (type == "double") {
                                while (input_file >> s >> val) {
                                        this->insert(s, val);
                                }
                        }
                        else if (type == "int") {
                                while (input_file >> s >> val) {
                                this->insert (s, val);
                                }
                        }
                        else if (type == "char") {
                                while (input_file >> s >> val) {
                                        this->insert(s, val);
                                }
                        }
                        else {
                                input_file.close();
                                throw Err(-2, std::string("Cannot identify type\n"));
                        }

                        input_file.close();
                }
        };
}
