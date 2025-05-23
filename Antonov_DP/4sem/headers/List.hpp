#include "Tree.hpp"
#include <vector>


class List{
	std::vector<student> students_;
public:
	List();
	~List() = default;
	int Add(student &st); //Добавляет студента. OK - успешно, N_OK - в противном случае.
	int Delete(double rating); //Удаляет студента по рейтингу. OK - успешно, N_OK - в противном случае.
	student pull(double rating); //Берёт данные студента по рейтингу.
};
