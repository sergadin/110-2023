#include "database.hpp"
#include <cmath>

static int compRR(double a, double b, double eps);

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MAX3(a, b, c) MAX(MAX((a), (b)), (c))

static int compRR(double a, double b, double eps)
{
        if (fabs(a - b) < eps * MAX3(a, b, 1))
	{
		return 0;
	}
	if (a > b)
	{
		return 1;
	}
	return -1;
}


int List::add(student *st){
	ListNode *p = start;
	if (p == nullptr){
		start = new ListNode;
		start->val_ = st;
		start->next_ = nullptr;
		return 0;
	}
	if(p->val_->rating_ < st->rating_){
		ListNode *answer = new ListNode;
		answer->next_ = start;
		answer->val_ = st;
		start = answer;
		return 0;
	}
	while(p->next_ != nullptr){
		if ((p->val_->rating_ >= st->rating_) && (st->rating_ >= p->next_->val_->rating_)){
			ListNode *answer = new ListNode;
			answer->val_ = st;
			answer->next_ = p->next_;
			p->next_ = answer;
			return 0;
		}
		p = p->next_;
	}
	ListNode *answer = new ListNode;
	answer->val_ = st;
        answer->next_ = p->next_;
        p->next_ = answer;
	return 0;
}

List * List::del(binop oper, double &rating){
	ListNode *p = start;
	ListNode *temp = nullptr;
	List *deleted = new List;
	switch(oper){
		case EQ:
			while(p->next_ != nullptr){
				if (compRR(p->val_->rating_, rating,0.001) == 0){			
					if(p == start){
						deleted->add(p->val_);
						temp = p;
						start = p->next_;
						p = p->next_;
						delete temp;
						temp = nullptr;
					}
					else{
						temp->next_ = p->next_;
						delete p;
						p = temp->next_;
					}
				}
				else{
					temp = p;
					p = p->next_;
				}
			}
		case GR:
			while(p->next_ != nullptr){
                                if (compRR(p->val_->rating_, rating,0.001) == 1){
                                        if(p == start){
                                                deleted->add(p->val_);
                                                temp = p;
                                                start = p->next_;
                                                p = p->next_;
                                                delete temp;
                                                temp = nullptr;
                                        }
                                        else{
                                                temp->next_ = p->next_;
                                                delete p;
                                                p = temp->next_;
                                        }
                                }
                                else{
                                        temp = p;
                                        p = p->next_;
                                }
                        }
		case LE:
			while(p->next_ != nullptr){
                                if (compRR(p->val_->rating_, rating,0.001) == -1){
                                        if(p == start){
                                                deleted->add(p->val_);
                                                temp = p;
                                                start = p->next_;
                                                p = p->next_;
                                                delete temp;
                                                temp = nullptr;
                                        }
                                        else{
                                                temp->next_ = p->next_;
                                                delete p;
                                                p = temp->next_;
                                        }
                                }
                                else{
                                        temp = p;
                                        p = p->next_;
                                }
                        }
		case GR_EQ:
			while(p->next_ != nullptr){
                                if (compRR(p->val_->rating_, rating,0.001) != -1){
                                        if(p == start){
                                                deleted->add(p->val_);
                                                temp = p;
                                                start = p->next_;
                                                p = p->next_;
                                                delete temp;
                                                temp = nullptr;
                                        }
                                        else{
                                                temp->next_ = p->next_;
                                                delete p;
                                                p = temp->next_;
                                        }
                                }
                                else{
                                        temp = p;
                                        p = p->next_;
                                }
                        }
		case LE_EQ:
			while(p->next_ != nullptr){
                                if (compRR(p->val_->rating_, rating,0.001) != 1){
                                        if(p == start){
                                                deleted->add(p->val_);
                                                temp = p;
                                                start = p->next_;
                                                p = p->next_;
                                                delete temp;
                                                temp = nullptr;
                                        }
                                        else{
                                                temp->next_ = p->next_;
                                                delete p;
                                                p = temp->next_;
                                        }
                                }
                                else{
                                        temp = p;
                                        p = p->next_;
                                }
                        }
		case N_EQ:
			while(p->next_ != nullptr){
                                if (compRR(p->val_->rating_, rating,0.001) != 0){
                                        if(p == start){
                                                deleted->add(p->val_);
                                                temp = p;
                                                start = p->next_;
                                                p = p->next_;
                                                delete temp;
                                                temp = nullptr;
                                        }
                                        else{
                                                temp->next_ = p->next_;
                                                delete p;
                                                p = temp->next_;
                                        }
                                }
                                else{
                                        temp = p;
                                        p = p->next_;
                                }
			}
	}
	return deleted;
}


student *List::pull(double rating){
	ListNode *p = start;
	while (p->next_ != nullptr){
		if(compRR(p->val_->rating_,rating,0.001) == 0){
			return p->val_;
		}
		p = p->next_;
	}
	return nullptr;
}

void List::clear(){
	ListNode *temp = nullptr;
	while (start->val_ == nullptr){
		temp = start;
		start = temp->next_;
		delete temp;
	}
	ListNode *p = start;
	if(start == nullptr){
		return;
	}
	while(p->next_ != nullptr){
		if(p->val_ == nullptr){
			temp->next_ = p->next_;
			delete p;
			p = temp->next_;
		}
		temp = p;
		p = p->next_;
	}
}
