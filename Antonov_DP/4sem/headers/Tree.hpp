#include "student.hpp"


class TreeNode{
	student *value_;
	TreeNode *left_, *right_;
	int balance;
	TreeNode() { left_ = right_ = nullptr; value_ = nullptr;}
public:
	~TreeNode(){
		if (left_ == nullptr){
			delete left_;
		}
		else{
			left_->~TreeNode();
			delete left_;
		}
		if (right_ == nullptr){
                        delete right_;
                }
                else{
                        right_->~TreeNode();
                        delete right_;
                }
	}
	int add(student *st); //добавление студента возвращает OK, если сработало и N_OK, в противном случае
	int del(char *name); //удаление по имени. OK, если сработало и N_OK, в противном случае
	void bal(); // сбалансировать дерево
	student pull(char *name); //получить данные о студенте
};
