#include "avl_tree.h"
#include <algorithm>

AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree() {
	deleteTree(root);
}

void AVLTree::deleteTree(Node* node) {
	if (node != nullptr) {
		deleteTree(node->left);
		deleteTree(node->right);
		delete node->data; 
		delete node;
	}
}

int AVLTree::height(Node* node) {
	if (node == nullptr)
		return 0;
	return node->height;
}

int AVLTree::getBalance(Node* node) {
	if (node == nullptr)
		return 0;
	return height(node->left) - height(node->right);
}

Node* AVLTree::rightRotate(Node* y) {
	Node* x = y->left;
	Node* T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = std::max(height(y->left), height(y->right)) + 1;
	x->height = std::max(height(x->left), height(x->right)) + 1;

	return x;
}

Node* AVLTree::leftRotate(Node* x) {
	Node* y = x->right;
	Node* T2 = y->left;

	y->left = x;
	x->right = T2;

	x->height = std::max(height(x->left), height(x->right)) + 1;
	y->height = std::max(height(y->left), height(y->right)) + 1;

	return y;
}

Node* AVLTree::insertRecursive(Node* node, std::string* data) {
	if (node == nullptr)
		return new Node(data);

	if (*data < *node->data)
		node->left = insertRecursive(node->left, data);
	else if (*data > *node->data)
		node->right = insertRecursive(node->right, data);
	else
		return node;

	node->height = 1 + std::max(height(node->left), height(node->right));

	int balance = getBalance(node);

	// Left Left Case
	if (balance > 1 && *data < *node->left->data)
		return rightRotate(node);

	// Right Right Case
	if (balance < -1 && *data > *node->right->data)
		return leftRotate(node);

	// Left Right Case
	if (balance > 1 && *data > *node->left->data) {
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	// Right Left Case
	if (balance < -1 && *data < *node->right->data) {
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	return node;
}

void AVLTree::insert(std::string* data) {
	root = insertRecursive(root, data);
}


Node* AVLTree::minValueNode(Node* node) {
	Node* current = node;
	while (current->left != nullptr)
		current = current->left;
	return current;
}

Node* AVLTree::removeRecursive(Node* root, std::string* data) {
	if (root == nullptr)
		return root;

	if (*data < *root->data)
		root->left = removeRecursive(root->left, data);
	else if (*data > *root->data)
		root->right = removeRecursive(root->right, data);
	else {
		if ((root->left == nullptr) || (root->right == nullptr)) {
			Node* temp = root->left ? root->left : root->right;

			if (temp == nullptr) {
				temp = root;
				root = nullptr;
			} else
				*root = *temp;
			delete temp;
		} else {
			Node* temp = minValueNode(root->right);
			*root->data = *temp->data;
			root->right = removeRecursive(root->right, temp->data);
		}
	}

	if (root == nullptr)
		return root;

	root->height = 1 + std::max(height(root->left), height(root->right));

	int balance = getBalance(root);


	if (balance > 1 && getBalance(root->left) >= 0)
		return rightRotate(root);


	if (balance > 1 && getBalance(root->left) < 0) {
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}


	if (balance < -1 && getBalance(root->right) <= 0)
		return leftRotate(root);


	if (balance < -1 && getBalance(root->right) > 0) {
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}

void AVLTree::remove(std::string* data) {
	root = removeRecursive(root, data);
}

bool AVLTree::search(std::string* data) {
	Node* current = root;
	while (current != nullptr) {
		if (*data == *current->data)
			return true;
		else if (*data < *current->data)
			current = current->left;
		else
			current = current->right;
	}
	return false;
}

int AVLTree::size() {
	std::vector<std::string*> result;
	inorder(root, result);
	return result.size();
}

void AVLTree::inorder(Node* node, std::vector<std::string*>& result) {
	if (node != nullptr) {
		inorder(node->left, result);
		result.push_back(node->data);
		inorder(node->right, result);
	}
}

std::vector<std::string*> AVLTree::range(std::string* start, bool forward) {
	std::vector<std::string*> result;
	std::vector<std::string*> all;
	inorder(root,all);
	auto it = std::find(all.begin(), all.end(), start);
	if (it == all.end()) return result; 

	if (forward) {
		for (auto i = it; i != all.end(); ++i) {
			result.push_back(*i);
		}
	} else {
		for (auto i = it; i != all.begin() -1; --i) {
			result.push_back(*i);
		}
		std::reverse(result.begin(), result.end());
	}
	return result;
}

