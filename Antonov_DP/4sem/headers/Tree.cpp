#include "database.hpp"


TreeNode *SearchRightmost(TreeNode *tree_);


TreeNode *add(TreeNode *tree_, student *st, int &grow){
	if (tree_ == nullptr){
		tree_ = new TreeNode;
		tree_->value_ = st;
		grow = 1;
		return tree_;
	}
	else{
		TreeNode *B, *C;
		if (strcmp(st->name_, tree_->value_->name_) < 0){
			tree_->left_ = add(tree_->left_, st, grow);
			if (grow == 0){
				return tree_;
			}
			else{
				switch(tree_->balance){
				case 1:
					tree_->balance = 0;
					grow = 0;
					return tree_;
				case 0:
					tree_->balance = -1;
					grow = 1;
					return tree_;
				case -1:
					B=tree_->left_;
					switch(B->balance){
					case -1:
						tree_->left_ = B->right_; B->right_ = tree_;
						tree_->balance = B->balance = 0;
						grow = 0;
						return B;
					case 0:
						tree_->left_ = B->right_; B->right_ = tree_;
						tree_->balance = -1; B->balance = 1;
						grow = 1;
						return B;
					case 1:
						C = B->right_;
						B->right_ = C->left_; C->left_ = B;
						tree_->left_ = C->right_; C->right_ = tree_;
						switch(C->balance) {
						case 0: tree_->balance = B->balance = C->balance = 0; break;
						case 1: tree_->balance = C->balance = 0; B->balance = -1; break;
						case -1: tree_->balance = 1; B->balance = C->balance = 0; break;
						}
						grow = 0;
						return C;
					}
				}
			}
		}
		else{
			tree_->right_ = add(tree_->right_, st, grow);
			if (grow == 0){
                                return tree_;
                        }
                        else{
                                switch(tree_->balance){
                                case -1:
                                        tree_->balance = 0;
                                        grow = 0;
                                        return tree_;
                                case 0:
                                        tree_->balance = 1;
                                        grow = 1;
                                        return tree_;
                                case 1:
                                        B=tree_->right_;
                                        switch(B->balance){
                                        case 1:
                                                tree_->right_ = B->left_; B->left_ = tree_;
                                                tree_->balance = B->balance = 0;
                                                grow = 0;
                                                return B;
                                        case 0:
						std::cout << "6" << "\n";
                                                tree_->right_ = B->left_; B->left_ = tree_;
                                                tree_->balance = 1; B->balance = -1;
                                                grow = 1;
                                                return B;
                                        case -1:
                                                C = B->left_;
                                                B->left_ = C->right_; C->right_ = B;
                                                tree_->right_ = C->left_; C->left_ = tree_;
                                                switch(C->balance) {
                                                case 0: tree_->balance = B->balance = C->balance = 0; break;
                                                case -1: tree_->balance = C->balance = 0; B->balance = 1; break;
                                                case 1: tree_->balance = -1; B->balance = C->balance = 0; break;
                                                }
                                                grow = 0;
                                                return C;
                                        }
                                }
                        }
		}
	}
	return tree_;
}


TreeNode *SearchRightmost(TreeNode *tree_){
	if (tree_->right_ == nullptr) { return tree_; }
	return SearchRightmost(tree_->right_);
}


TreeNode *del(TreeNode *tree_, char *name, int &grow)
{
	TreeNode *p, *B, *C;
	if (tree_ == nullptr) return nullptr;
	if (strcmp(name,tree_->value_->name_) > 0) {
		tree_->right_ = del(tree_->right_, name, grow);
		if (grow == 0){
                	return tree_;
                }
                else{
                	switch(tree_->balance){
                        case 1:
                        	tree_->balance = 0;
                                grow = -1;
                                return tree_;
                        case 0:
                                tree_->balance = -1;
                                grow = 0;
                                return tree_;
                        case -1:
                                B=tree_->left_;
                                switch(B->balance){
                                case -1:
                	                tree_->left_ = B->right_; B->right_ = tree_;
                                        tree_->balance = B->balance = 0;
                                        grow = -1;
                                        return B;
                                case 0:
                                        tree_->left_ = B->right_; B->right_ = tree_;
                                        tree_->balance = -1; B->balance = 1;
                                        grow = 0;
                                        return B;
                                case 1:
                                        C = B->right_;
                                        B->right_ = C->left_; C->left_ = B;
                                        tree_->left_ = C->right_; C->right_ = tree_;
                                        switch(C->balance) {
                                        case 0: tree_->balance = B->balance = C->balance = 0; break;
                                        case 1: tree_->balance = C->balance = 0; B->balance = -1; break;
                                        case -1: tree_->balance = 1; B->balance = C->balance = 0; break;
                                        }
                                        grow = -1;
                                        return C;
				}
			}
		}
	} else if (strcmp(name,tree_->value_->name_) < 0) {
		tree_->left_ = del(tree_->left_, name, grow);
		if (grow == 0){
			return tree_;
		}
		else{
			switch(tree_->balance){
			case -1:
				tree_->balance = 0;
				grow = -1;
				return tree_;
			case 0:
				tree_->balance = 1;
				grow = 0;
				return tree_;
			case 1:
				B=tree_->right_;
				switch(B->balance){
				case 1:
					tree_->right_ = B->left_; B->left_ = tree_;
					tree_->balance = B->balance = 0;
					grow = -1;
					return B;
				case 0:
					tree_->right_ = B->left_; B->left_ = tree_;
					tree_->balance = 1; B->balance = -1;
					grow = 0;
					return B;
				case -1:
					C = B->left_;
					B->left_ = C->right_; C->right_ = B;
					tree_->right_ = C->left_; C->left_ = tree_;
					switch(C->balance) {
					case 0: tree_->balance = B->balance = C->balance = 0; break;
					case -1: tree_->balance = C->balance = 0; B->balance = 1; break;
					case 1: tree_->balance = -1; B->balance = C->balance = 0; break;
					}
					grow = -1;
					return C;
				}
			}
		}
	} else {
		if (tree_->right_ == nullptr) {
			p = tree_->left_;
			delete tree_;
			grow = -1;
			return p;
		}
		if (tree_->left_ == nullptr) {std::cout << "1" << "\n";
			p = tree_->right_;
			delete tree_;
			grow = -1;
			return p;
		}
		p = SearchRightmost (tree_->left_);
		tree_->value_ = p->value_;
		tree_->left_ = del(tree_->left_, tree_->value_->name_, grow);
	}
	return tree_;
}


student TreeNode::pull(char *name){
	std::cout << "2" << "\n";
	if (strcmp(name,this->value_->name_) < 0) {
		if (left_ == nullptr){std::cout << "1" << "\n";}
		return this->left_->pull(name);
	}
	if (strcmp(name,this->value_->name_) > 0) {
		if (right_ == nullptr){std::cout << "1" << "\n";}
		return this->right_->pull(name);
	}
	std::cout << "2" << "\n";
	student st (this->value_->name_,this->value_->group_, this->value_->rating_, this->value_->info_);
	std::cout << "2" << "\n";
	st.print();
	return st;
}

void clear_null(List *deleted,TreeNode *tree){
	ListNode *p = deleted->start;
	int grow;
	while (p != nullptr){
		tree = del(tree, p->val_->name_,grow);
		p = p->next_;
	}
	delete deleted;
}
