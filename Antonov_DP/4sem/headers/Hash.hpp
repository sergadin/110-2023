#include "List.hpp"


union h_object{
        List* list_root_;
        TreeNode* tree_root_;
        int val_;
};

class Hash {
	h_object* hash_;
	int max_size;
public:
	int Hash_func(int gr);
	Hash(size_t max_size = 100){
		hash_ = new h_object[max_size];
	}
	~Hash(){
		delete[] hash_;
	}
	void Add_group(int &gr);
	void Add_student(student &st);
	void Delete_group(int &gr);
	void Delete_student(int &gr, char name[64]);
	std::vector<student> Give_group(int &gr);
};
