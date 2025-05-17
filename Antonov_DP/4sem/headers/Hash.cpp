#include "Hash.hpp"
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
	if ( i == max_size){
		std::cout << 1 << "\n";
	}
	else{
		hash_[st].val_ = gr;
	}
	std::cout << hash_[st].val_ << "\n";
}

void Hash::Delete_group(int &gr){
	int st = this->Hash_func(gr);
        int i = 0;
	std::cout << 2 << "\n";
        while (hash_[st].val_ != gr){
                if (i == max_size) { break;}
                st = (st + 1)%max_size;
                i++;
        }
	std::cout << 2 << "\n";
        if ( i == max_size){
                std::cout << 1 << "\n";
        }
        else{
                hash_[st].val_ = 0;
		hash_[st].list_root_->~List();
		std::cout << 2 << "\n";
		hash_[st].tree_root_->~TreeNode();
        }
	std::cout << 2 << "\n";
        std::cout << hash_[st].val_ << "\n";
}
