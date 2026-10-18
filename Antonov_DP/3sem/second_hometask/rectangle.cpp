#include <iostream>
#include "rectangle.h"

#define SIZE 10
#define LIMIT 10

int TreeNode::add_point(point &p){
	if (small_ != 0){
		int quan = small_[((int)((p[1] - a_[1]) / ((b_[1] - a_[1]) / SIZE))) * SIZE + ((int)((p[0] - a_[0]) / ((b_[0] - a_[0]) / SIZE)))].add_point(p);
		len_ += quan;
		return quan;
	}
	for (int i = 0; i < len_; i++){
                if (p.compare(points_[i])){
			return 0;
		}
        }
	point *new_;
       	point *temp;
	new_ = new point[len_ + 1];
	for (int i = 0; i < len_; i++){
		new_[i] = points_[i];
	}
	new_[len_] = p;
	temp = points_;
	points_ = new_;
	new_ = temp;
	delete[] new_;
	if((len_ == LIMIT) && (level_ < 3)){
		this->change();
	}
	len_++;
	return 1;
}

void TreeNode::change(){
	double d_l((b_[0] - a_[0]) / SIZE), d_w((b_[1] - a_[1]) / SIZE);
	point temp;
	small_ = new TreeNode[SIZE * SIZE];
	for (int i = 0; i < SIZE; i++){
		for(int j = 0; j < SIZE; j++){
			temp[0] = a_[0] + (j * d_l);
			temp[1] = a_[1] + (i * d_w);
			small_[(i * SIZE) + j].set_a(temp);
			temp[0] = a_[0] + ((j + 1) * d_l);
                        temp[1] = a_[1] + ((i + 1) * d_w);
			small_[(i * SIZE) + j].set_b(temp);
			small_[(i * SIZE) + j].set_level(level_ + 1);
		}
	}
	for (int i = 0 ; i < len_; i++){
		small_[((int)((points_[i][1] - a_[1]) / d_w)) * SIZE + ((int)((points_[i][0] - a_[0]) / d_l))].add_point(points_[i]);
	}
	delete[] points_;
	points_ = new point[0];
}

int TreeNode::delete_point(point &p){
	if (small_ != 0){
                int quan = small_[((int)(((p[1] - a_[1])) / ((b_[1] - a_[1]) / SIZE))) * SIZE + ((int)((p[0] - a_[0]) / ((b_[0] - a_[0]) / SIZE)))].delete_point(p);
        	len_ += quan;
		return quan;
	}
	for (int i = 0; i < len_; i++){
                if (p.compare(points_[i])){
                	point *new_; 
        		point *temp;
        		new_ = new point[len_ - 1];
			int k = 0;
        		for (int j = 0; j < len_; j++){
				if (i != j){
                			new_[j - k] = points_[j];
				}
				else { k = 1; }
        		}
			temp = points_;
			points_ = new_;
			new_ = temp;
			delete[] new_;
			len_ --;
			return -1;
		}
        }
	return 0;
}

point TreeNode::operator[](int n){
	int sum = 0;
	if (small_ != 0){
		for (int i = 0; i < (SIZE * SIZE); i++){
			sum += small_[i].len_;
			if (sum > n){
				return small_[i].operator[]((n - sum) + small_[i].len_);
			}
		}
		throw Rectangle_Exception(-1, "out of range");
	}
	if (n >= len_){
		throw Rectangle_Exception(-1, "out of range");
	}
	return points_[n];
}

int TreeNode::len(){
	return len_;
}

bool TreeNode::point_in_set(point &p){
	if (small_ != 0){
                return small_[((int)(((p[1] - a_[1])) / ((b_[1] - a_[1]) / SIZE))) * SIZE + ((int)((p[0] - a_[0]) / ((b_[0] - a_[0]) / SIZE)))].point_in_set(p);
        }
        for (int i = 0; i < len_; i++){
                if (p.compare(points_[i])){
                        return true;
		}
	}
	return false;
}
point* TreeNode::neighbours(point &p){
	if (small_ != 0){
                return small_[((int)(((p[1] - a_[1])) / ((b_[1] - a_[1]) / SIZE))) * SIZE + ((int)((p[0] - a_[0]) / ((b_[0] - a_[0]) / SIZE)))].neighbours(p);
        }
	point *result;
	result = new point[len_];
	for (int i = 0; i < len_; i++){
		result[i] = points_[i];
	}
	return result;
}

int TreeNode::get_len_neighbours(point &p){
	if (small_ != 0){
                return small_[((int)(((p[1] - a_[1])) / ((b_[1] - a_[1]) / SIZE))) * SIZE + ((int)((p[0] - a_[0]) / ((b_[0] - a_[0]) / SIZE)))].get_len_neighbours(p);
        }
	return len_;
}
