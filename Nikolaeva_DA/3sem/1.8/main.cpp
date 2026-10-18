#include "avl_tree.h"
#include <fstream>
#include <iostream>
#include <string>

int main() {
	AVLTree tree;

	// Загрузка из файла
	std::ifstream file("data.txt");
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			std::string* str = new std::string(line);
			tree.insert(str);
		}
		file.close();
	}


	std::string* search_str = new std::string("apple");
	std::cout << "Search for '" << *search_str << "': " << tree.search(search_str) << std::endl;

	std::cout << "Tree size: " << tree.size() << std::endl;

	std::string* range_start = new std::string("banana");
	std::vector<std::string*> forward_range = tree.range(range_start, true);
	std::cout << "Forward range from '" << *range_start << "': ";
	for (std::string* str : forward_range) {
		std::cout << *str << " ";
	}
	std::cout << std::endl;

	std::vector<std::string*> backward_range = tree.range(range_start, false);
	std::cout << "Backward range from '" << *range_start << "': ";
	for (std::string* str : backward_range) {
		std::cout << *str << " ";
	}
	std::cout << std::endl;

	tree.remove(search_str);
	delete search_str;
	delete range_start;

	return 0;
}
