#include "student.hpp"


class TreeNode{
public:
	student *value_;
	TreeNode *left_, *right_;
	int balance;
	TreeNode() { left_ = right_ = nullptr; value_ = nullptr; balance = 0;}
	~TreeNode() = default;
	friend TreeNode *add(TreeNode *tree_, student *st, int &grow); //добавление студента возвращает OK, если сработало и N_OK, в противном случае
	friend TreeNode *del(TreeNode *tree_, char *name, int &grow); //удаление по имени. OK, если сработало и N_OK, в противном случае
	student pull(char *name); //получить данные о студенте
	void kill(){
		if(left_ != nullptr){
                        left_->kill();
                }
                if (right_ != nullptr){
                        right_->kill();
                }
                delete this;
	}
};
