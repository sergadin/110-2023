#include "datsbasse.hpp"


class TreeNode{
	student *value_;
	TreeNode *left_, *right_;
	int balance;
	TreeNode() { left = right = nullptr; }
public:
	int add(student *value); //добавление студента возвращает OK, если сработало и N_OK, в противном случае
	int del(char *name); //удаление по имени. OK, если сработало и N_OK, в противном случае
	void bal(); // сбалансировать дерево
	student pull(char *name) //получить данные о студенте
}
