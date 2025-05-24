#include "Tree.hpp"
#include <iostream>


int main(){
	char name[] = "Антонов";
	int group = 210;
	double rating = 4;
	char info[] = "Москва";
	student st(name, group, rating, info);
	char name1[] = "Сторожева";
	student st1(name1, group, rating, info);
	char name2[] = "Чепкаленко";
        student st2(name2, group, rating, info);
	char name3[] = "Симонян";
        student st3(name3, group, rating, info);
	char name4[] = "Бадерко";
        student st4(name4, group, rating, info);
	char name5[] = "Егоров";
        student st5(name5, group, rating, info);
	char name6[] = "Бакуменко";
        student st6(name6, group, rating, info);
	char name7[] = "Янсон";
        student st7(name7, group, rating, info);
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
	Tree = add(Tree, &st7, grow);
	std::cout << Tree->value_->name_ << "\n";
	std::cout << Tree->value_->name_ << "\n";
	std::cout << Tree->right_->value_->name_ << "\n";
	std::cout << Tree->left_->value_->name_ << "\n";
	std::cout << Tree->right_->right_->value_->name_ << "\n";
	std::cout << Tree->right_->left_->value_->name_ << "\n";
	std::cout << Tree->left_->right_->value_->name_ << "\n";
        std::cout << Tree->left_->left_->value_->name_ << "\n";
}
