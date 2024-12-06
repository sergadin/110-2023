#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <string>
#include <vector>

struct Node {
	std::string* data;
	Node* left;
	Node* right;
	int height;
	Node(std::string* d) : data(d), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
	public:
		AVLTree();
		~AVLTree();
		void insert(std::string* data);
		void remove(std::string* data);
		bool search(std::string* data);
		int size();
		std::vector<std::string*> range(std::string* start, bool forward);


	private:
		Node* root;
		int height(Node* node);
		int getBalance(Node* node);
		Node* rightRotate(Node* y);
		Node* leftRotate(Node* x);
		Node* insertRecursive(Node* node, std::string* data);
		Node* minValueNode(Node* node);
		Node* removeRecursive(Node* root, std::string* data);
		void inorder(Node* node, std::vector<std::string*>& result);
		void deleteTree(Node* node);

};

#endif
