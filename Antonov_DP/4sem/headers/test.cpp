#include "Tree.hpp"
#include <iostream>


int main(){
	char name[] = "Antonov";
	int group = 210;
	double rating = 4;
	char info[] = "Moscow";
	student st(name, group, rating, info);
	char name1[] = "Storogeva";
	student st1(name1, group, rating, info);
	char name2[] = "Chekalenko";
        student st2(name2, group, rating, info);
	char name3[] = "Simonyan";
        student st3(name3, group, rating, info);
	char name4[] = "Baderko";
        student st4(name4, group, rating, info);
	char name5[] = "Egorov";
        student st5(name5, group, rating, info);
	char name6[] = "Bakumenko";
        student st6(name6, group, rating, info);
	TreeNode *Tree = nullptr;
	int grow = 0;
	std::cout << "1" << "\n";
	Tree = add(Tree, &st, grow);
	std::cout << Tree->value_->name_ << "\n";
	Tree = add(Tree, &st1, grow);
	std::cout << Tree->right_->value_->name_ << "\n";
	Tree = add(Tree, &st2, grow);
	std::cout << Tree->right_->value_->name_ << "\n";
	Tree = add(Tree, &st3, grow);
	std::cout << Tree->value_->name_ << "\n";
	Tree = add(Tree, &st4, grow);
	std::cout << Tree->value_->name_ << "\n";
	Tree = add(Tree, &st5, grow);
	std::cout << Tree->value_->name_ << "\n";
	Tree = add(Tree, &st6, grow);
	std::cout << Tree->value_->name_ << "\n";
	std::cout << Tree->value_->name_ << "\n";
	std::cout << Tree->right_->value_->name_ << "\n";
	std::cout << strlen(info) << "\n";
	student st8 = Tree->pull(name);
	std::cout << "6" << "\n";
	std::cout << st8.rating_ << "\n";
}
