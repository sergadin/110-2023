#include "database.hpp"


struct Cond{
	field f_;
	binop b_;
	union{
		int gr;
		char *name;
		double rat;
	} v_;
};

typedef std::list<Cond> SearchConditions;
struct Command {
    CommandType cmd;
    SearchConditions conditions;
};
