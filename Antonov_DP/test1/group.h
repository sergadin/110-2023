#include <iostream>
using namespace std

using Element = int;
class Group {
	vector<Element> elements_;
	size_t unit_idx_;
	const Element unit_;
public:
	Group(vector<Element> &elements, Element(*mul)(Element, Element), Element(*inverse)(Element), Element unit);
	Group() = delete;
	map<Element Element> inverses_;
	const Element &inverse(const Element &a) const{
		size_t idx;
		if (inverses_.find(elem) == inverses.end()){
			Element elem1 = f_inverse_(elem);
			inverses_[a] = a1;
		}
		return inverses_[a];
}

class MyException: /*public runtime_exception*/{
	int code_;
	string what_;
	MyException(int c, string w)
		: code(c), what(w) {}
	string what() const {return what_;}
	try{
	}
	catch(MyException &ex){
		cout <<ex.what;
	}
}

try{
	op;
	cout << "error";
}
catch (MyEx&){}
