#include "database.hpp"
#include <iostream>


int Hash::Hash_func(int gr){
	int n = ((31 * ((int) (gr / 100)) + 11 * (gr % 100))%max_size);
	return n;
}


void Hash::Add_group(int &gr){
	int st = this->Hash_func(gr);
	int i = 0;
	while (hash_[st].val_){
		if (i == max_size) { break;}
		st = (st + 1)%max_size;
		i++;
	}
	if (i == max_size){
		std::cout << 1 << "\n";
	}
	else{
		hash_[st].list_root_ = new List;
		hash_[st].tree_root_ = new TreeNode;
		hash_[st].val_ = gr;
	}
}

void Hash::Delete_group(int &gr){
	int st = this->Hash_func(gr);
        int i = 0;
        while (hash_[st].val_ != gr){
                if (i == max_size) { break;}
                st = (st + 1)%max_size;
                i++;
        }
	std::cout << 2 << "\n";
        if (i == max_size){
		std::cout << "1" << "\n";
        }
        else{
                hash_[st].val_ = 0;
        }
}

void Hash::Add_student(student &st){
	int num = this->Hash_func(st.group_);
	int i = 0;
        while ((hash_[num].val_ != st.group_) && hash_[num].val_){
                if (i == max_size) { break;}
                num = (num + 1) % max_size;
                i++;
        }
	if (i == max_size){
		std::cout << 1 << "\n";
	}
	else if(hash_[num].val_ == 0) {
		int grow = 0;
		hash_[num].val_ = st.group_;
		hash_[num].tree_root_ = nullptr;
		hash_[num].tree_root_ = add(hash_[num].tree_root_ ,&st, grow);
		hash_[num].list_root_ = new List;
		hash_[num].list_root_->add(&st);
	}
	else{
		int grow;
		hash_[num].tree_root_ = add(hash_[num].tree_root_ ,&st, grow);
                hash_[num].list_root_->add(&st);
	}
}


void Hash::Delete_student(int &gr, char name[64]){
	int num = this->Hash_func(gr);
	int i = 0;
        while ((hash_[num].val_ != gr) && hash_[num].val_){
                if (i == max_size) { break;}
                num = (num + 1) % max_size;
                i++;
        }
        if ((i == max_size) || (hash_[num].val_ == 0)){
                std::cout << 1 << "\n";
        }
	else{
		int grow;
                hash_[num].tree_root_ = del(hash_[num].tree_root_ ,name, grow);
                hash_[num].list_root_->clear();
	}
}
