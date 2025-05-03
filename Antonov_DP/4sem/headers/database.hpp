#include "Session.hpp"
#include "Hash.hpp"
#include <iostream>
#include <list>

typedef enum {OK, N_OK} confirm;
typedef enum {SELECT, RESELECT, PRINT, INSERT, REMOVE, UPDATE} oper;
typedef enum {NAME, GROUP, RATING, INFO} field;
typedef enum {EQ, N_EQ, GR, LE, GR_EQ, LE_EQ} binop;

class database {
	Hash **database;
};


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
    oper cmd;
    SearchConditions conditions;
};
