#include "student.hpp"

struct ListNode{
	student *val_;
	ListNode *next_;
};

class List{
	ListNode *start;
public:
	List(){
		start = nullptr;
	}
	~List(){
		ListNode *p = start;
        	ListNode *temp;
        	while(p->next_ !=nullptr){
			std::cout << "2" << "\n";
                	temp = p;
                	p = p->next_;
                	delete temp;
        	}
	delete p;
	}
	int add(student *st); //Добавляет студента. OK - успешно, N_OK - в противном случае.
	List * del(binop oper, double &rating); //Удаляет студента по рейтингу. OK - успешно, N_OK - в противном случае.
	student pull(double rating); //Берёт данные студента по рейтингу.
};
