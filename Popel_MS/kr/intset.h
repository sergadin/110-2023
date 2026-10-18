#include <iostream>
#include <string>

//using namespace std;
class Sets{
private:
    int maxEl_;
    int minEl_;
    int *set_ = nullptr;
    int size_;
public:
    Sets(int minEl, int maxEl);
    Sets(Sets &set);
    Sets(const Sets &set);
    ~Sets();
    Sets() = delete;
    bool find_el(int el) const;
    void put(int el);
    void rem(int el);
    bool is_empty() const{
        return (size_==0);
    }
    
    int get_max() const;
    int get_min() const;
    int left_board() const{
        return minEl_;
    }
    int right_board() const{
        return maxEl_;
    }
    int get_size() const{
        return size_;
    }
    void print() const;
    friend Sets operator* (const Sets &frst, const Sets &scnd);
    Sets& operator*= (const Sets &set);
    Sets& operator=(const Sets &frst);
    friend bool operator==(const Sets& frst, const Sets &scnd);
};

class Error{
private:
    int code_;
    std::string message_;
public:
    Error(int code, std::string message){
        code_ = code;
        message_ = message;
    }
    
    const std::string get_mes() const{
        return message_;
    }
};
