#include "intset.h"

using namespace std;

Sets::Sets(int minEl, int maxEl){
    if (maxEl < minEl){
        throw(Error(-1, string("Wrong boards\n")));
    }
    maxEl_ = maxEl;
    minEl_ = minEl;
    size_ = 0;
}
Sets::Sets(Sets &set){
    if(!(this->set_ == set.set_) && set.size_ == 0){
        throw Error(-2, string("Zero size\n"));
    }
    delete []this->set_;
    size_ = set.size_;
    maxEl_ = set.maxEl_;
    minEl_= set.minEl_;
    set_ = new int[size_];
    if(set_ == nullptr){
        throw Error(-4, string("Memory problems\n"));
    }
    for(int i = 0; i < size_; i++){
        set_[i] = set.set_[i];
    }
}

Sets::Sets(const Sets &set){
    if(!(this->set_ == set.set_) && set.size_ == 0){
        throw Error(-2, string("Zero size\n"));
    }
    size_ = set.size_;
    maxEl_ = set.maxEl_;
    minEl_ = set.minEl_;
    delete []this->set_;
    set_ = new int[size_];
    if(set_ == nullptr){
        throw Error(-4, string("Memory problems\n"));
    }
    for (int i = 0; i < size_; i++){
        set_[i] = set.set_[i];
    }
}
Sets::~Sets(){
    if (size_<=0){
        return;
    }
    maxEl_ = 0;
    minEl_ = 0;
    size_ = 0;
    delete[] set_;
}

bool Sets::find_el(int el) const{
    if (size_ <= 0){
        return 0;
    }
    for(int i = 0; i < size_; i++){
        if(set_[i] == el){
            return 1;
        }
    }
    return 0;
}
void Sets::put(int el){
    int *set = nullptr;
    if(find_el(el)){
        return;
    }
    if(maxEl_ < el || minEl_ > el){
        throw Error(-1, string("Wrong boards\n"));
    }
    set = new int[size_ + 1];
    if(set == nullptr){
        throw Error(-4, string("Memory problems\n"));
    }
    if(set == nullptr){
        throw Error(-4, string("Memory problems\n"));
    }
    for(int i = 0; i < size_; i++){
        set[i] = set_[i];
    }
    set[size_] = el;
    delete[] set_;
    size_++;
    set_ = new int[size_];
    for(int i = 0; i<size_; i++){
        set_[i] = set[i];
    }
    delete[] set;
}
void Sets::rem(int el){
    int fnd = 0;
    int *set = nullptr;
    if(!(this->Sets::find_el(el))){
        throw Error(-3, string("No such element in set\n"));
    }
    set = new int[size_ - 1];
    if(set == nullptr){
        throw Error(-4, string("Memory problems\n"));
    }
    size_--;
    for(int i = 0; i < size_; i++){
        if(!fnd){
            if(set_[i] == el){
                fnd = 1;
                set[i] = set_[i+1];
            }else{
                set[i] = set_[i];
            }
        }else{
            set[i] = set_[i+1];
        }
        
    } 
    delete []set_;
        set_ = new int[size_];
        if(set_ == nullptr){
            throw Error(-4, string("Memory problems\n"));
        }
        for(int j = 0; j < size_; j++){
            set_[j] = set[j];
        }
        delete []set;
}
 int Sets::get_max() const{
    int mx = 0;
    if(size_ <=0){
        throw Error(-1, string("Zero size\n"));
    }
    mx = set_[0];
    for(int i = 0; i<size_; i++){
        if(mx<set_[i]){
            mx = set_[i];
        }
    }
    return mx;
}
int Sets::get_min() const{
    int mn = 0;
    if(size_ <=0){
        throw Error(-1, string("Zero size\n"));
    }
    mn = set_[0];
    for(int i = 0; i<size_; i++){
        if(mn>set_[i]){
            mn = set_[i];
        }
    }
    return mn;
}

Sets& Sets::operator= (const Sets &frst){
    this->maxEl_ = frst.maxEl_;
    this->minEl_ = frst.minEl_;
    if(this->set_ == frst.set_){
        return *this;
    }
    delete[] set_;
    size_ = frst.size_;
    this->set_ = new int[size_];
    maxEl_ = frst.maxEl_;
    minEl_ = frst.minEl_;
    for (int i = 0; i < size_; i++){
        this->set_[i] = frst.set_[i];
    }
    return *this;
}

Sets& Sets::operator*= (const Sets &st){
    int min_sz = 0, min_set = 0;
    Sets set(this->minEl_, st.maxEl_);
    if(this->maxEl_ > st.maxEl_){
        set.maxEl_ = st.maxEl_;
    }
    if(this->minEl_ < st.minEl_){
        set.minEl_ = st.minEl_;
    }
    if(this->size_ <= 0 || st.size_ <= 0){
        throw Error(-2, string("Zero size\n"));
    }
    if(this->size_ < st.size_){
        min_sz = this->size_;
    }else{
        min_sz = st.size_;
        min_set = 1;
    }
    for(int i = 0; i < min_sz; i++){
        if(min_set && this->Sets::find_el(st.set_[i])){
            set.put(st.set_[i]);
        }else if(!min_set && st.Sets::find_el(this->set_[i])){
            set.put(this->set_[i]);
        }
    }
    *this = set;
    return *this;
}
Sets operator* (const Sets &frst, const Sets &scnd){
    Sets tmp = frst;
    tmp*=scnd;
    return tmp;
}

bool operator== (const Sets &frst, const Sets &scnd){
    if((((frst*scnd).size_)!=frst.size_) || (frst.size_!=scnd.size_)){
        return 0;
    } return 1;
}

void Sets::print() const{
    for (int i = 0; i < (this->size_); i++){
        printf("%d ", this->set_[i]);
    }
    printf("\n");
}
