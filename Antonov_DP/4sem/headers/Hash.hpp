#include "Tree.hpp"
#include "List.hpp"


union h_object{
        List* list_root_;
        TreeNode* tree_root_;
        int val_;
};

class Hash {
	std::vector<h_object> hash_;
	size_t max_size;
	unsigned int Hash_func(int gr);
public:
	void Add_group(int &gr);
	void Add_student(student &st);
	void Delete_group(int &gr);
	void Delete_student(int &gr, char name[64]);
	vector<student> Give_group(int &gr)
};
