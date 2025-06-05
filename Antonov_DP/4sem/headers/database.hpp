#include "Session.hpp"
#include "student.hpp"
#include <iostream>
#include <list>
#include <vector>

typedef enum {OK, N_OK} confirm;
typedef enum {SELECT, RESELECT, PRINT, INSERT, REMOVE, UPDATE} oper;
typedef enum {NAME, GROUP, RATING, INFO} field;
typedef enum {EQ, N_EQ, GR, LE, GR_EQ, LE_EQ} binop;


struct ListNode{
        student *val_;
        ListNode *next_;
};


class List{
public:
        ListNode *start;
        List(){
                start = nullptr;
        }
        ~List(){
                ListNode *p=start;
		ListNode *temp;
		while (p != nullptr){
			temp = p;
			p=p -> next_;
			delete temp;
		}
		delete p;
        }
        int add(student *st); //Добавляет студента. OK - успешно, N_OK - в противном случае.
        List * del(binop oper, double &rating); //Удаляет студента по рейтингу. OK - успешно, N_OK - в противном случае.
        student *pull(double rating); //Берёт данные студента по рейтингу.
	void clear();
};


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
        friend void clear_null(List *deleted, TreeNode *tree);
};


struct h_object{
        List* list_root_;
        TreeNode* tree_root_;
        int val_;
};

class Hash {
public:
        h_object* hash_;
        int max_size;
        int Hash_func(int gr);
        Hash(int max_size_ = 100){
                hash_ = new h_object[max_size_];
		max_size=max_size_;
		for (int i = 0; i < max_size;i++){
			hash_[i].val_ = 0;
		}
        }
        ~Hash(){
		for (int i = 0; i < max_size; i++){
			if(hash_[i].val_ != 0){
				hash_[i].tree_root_->kill();
				delete hash_[i].list_root_;
			}
		}
                delete[] hash_;
        }
        void Add_group(int &gr);
        void Add_student(student &st);
        void Delete_group(int &gr);
        void Delete_student(int &gr, char name[64]);
	void Delete_student(int &gr, binop oper, double rating);
	void Delete_student(student &st);
        std::vector<student> Give_group(int &gr);
};


class database {
	Hash **database;
};


struct Cond{
	field f_;
	binop b_;
	struct{
		int gr;
		char *name;
		double rat;
	} v_;
};

typedef std::list<Cond> SearchConditions;
struct Command {
    oper cmd;
    SearchConditions conditions;
};

