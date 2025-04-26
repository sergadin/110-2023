#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <variant>
#include <cstring>
#include <memory>

using namespace std;


struct FullName{
	char firstname[64];
	char middlename[64];
	char lastname[64];
};


enum class CommandType {ADD, SELECT, RESELECT, DELETE, UPDATE, PRINT};

enum class Field {NAME, GROUP, RATING, ADRESS};

enum class Bin_Op {GT, LT, EQ, LT_EQ, GT_EQ, IN};

enum class Order {ASC, DESC};

using enum CommandType;

using enum Field;

using enum Bin_Op;

using Value = variant <int, double, std::string>;
//assign main name

/*struct Cond{
	Field field;
	Bin_Op operation;
	union
	{
		int i;
		std::string s;
		double d;
	}value;
};
*/

//class of conditions
class Cond{
private:
	Field field;
	Bin_Op binop;
	Value val;
public:
	Cond(Field f, Bin_Op op, Value v);
	
	Field getField() const{
		return field;
	}

	Bin_Op getBin_Op() const{
		return binop;
	}

	Value getValue() const{
		return val;
	}
};


class Query {
protected:
	string query_;

public:
	explicit Query(const string &query);

	virtual ~Query();
		
	virtual void parse() = 0;
};


class AddQuery : public Query {
private:
	Student student_data;
public:
	explicit AddQuery(const string& query);

	void parse() override;
};


class SelectQuery : public Query{
private:
	vector<Cond> conditions;
public:
	explicit SelectQuery(const string& query);

	void parse() override;
};


class ReselectQuery : public Query{
private:
	vector<Cond> additional_conditions;
public:
	explicit ReselectQuery(const string& query);

	void parse() override;
};


class DeleteQuery : public Query{
private:
	vector<Cond> conditions;
public:
	explicit DeleteQuery(const string& query);

	void parse() override;
};


class UpdataQuery : public Query{
private:
	vector<Cond> conditions;
	StudentUpdataData updata_data;
public:
	explicit UpdataQuery(const string& query);

	void parse() override;
};


class PrintQuery : public Query{
private:
	explicit PrintQuery(const string& query);
	
	void parse() override;
	//need to add new object, which contain print variables

};


class Student{
private:
	FullName name_;
	int groupNumber_;
	double rating_;
	char email_[64];
public:
	Cell(const FullName& name, int group, double rating, const char* email): name_(name),
       	groupNumber_(group),	rating_(rating){
		strncpy(this->email, email, sizeof(this->email) - 1);
		this->email[sizeof(this->email) - 1] = '\0';
	}

	FullName getName() const {return name_;}

	int getGroupNumber() const {return groupNumber_;}

	double getRating() const {return rating_;}

	const char* getEmail() const { return email_;}

};


class Exception{
private:
	int code_;
	string message_;
public:
	Exception(int c; const string& m) : code_(c), message_(m){}
	string getMessage() const{ return message_;}
};


struct Result{
	vector<Student> entries;
	//result of sample
	string message;
	//massage about result of operation
	
	void addEntry(const Student& entry);

	void addError(const Exception& err);

	void addMessage(const string& msg);

	//and more...

};


//class Table of students
//variables:
//students-vector of students
//groupIndex-index of group;
//ratingIndex - index of rating
//emailIndex - index of email
class Table{
private:
	vector<Student*> students;
	map<int, vector<int>> groupIndex;
	map<double, vector<int>> ratingIndex;
	map<string, vector<int>> emailIndex;

	void buildIndices() {
		groupIndex.clear();
		ratingIndex.clear();
		emailIndex.clear();
		for(size_t i =0 ; i < students.size(); i++){
			 groupIndex[students[i].getGroupNumber()].push_back(i);
			 ratingIndex[students[i].getRating()].push_back(i);
			 emailIndex[students[i].getEmail()].push_back(i);
		}
	}

public:
	Table() = default;

	Table(FILE* fin);

	~Table();
	
	void addStudent(const Student& student);
	
	//maybe size_t type?
	void deleteStudent(const vector<Cond>& conditions);
	
	//maybe size_t to?
	void uptadeStudent(const vector<Cond>& conditions, ???);

	vector<Student> selectStudent(const vector<Cond>& conditions) const;

	vector<Student> reselectStudent(const vector<Student>& prev_results, const vector<Cond>& new_conds) const;
	
	void print(const vector<Student*>& goodStudents,???);

	//saveToFile
	//loadToFile
	
};


class DataBase{
private:
	Table* table_;

public:
	DataBase(FILE* fin);
	~DataBase();
	Table* GetTable const{return table_;}
	Result executeQuery(string& query);
		
};


class Creator {
public:
    virtual ~Creator() = default;
    virtual std::unique_ptr<Query> factoryMethod() const = 0;

};


class CreatorAdd : public Creator {
public:
	unique_ptr<Query> factoryMethod() const override {
       		 return make_unique<AddQuery>();
   	 }
};


class CreatorDelete : public Creator {
public:
	unique_ptr<Query> factoryMethod() const override {
       		 return make_unique<DeleteQuery>();
   	 }
};


class CreatorSelect : pulbic Creator{
public:
	uniqie_ptr<Query> factoryMethod() const override{ 
		return make_unique<SelectQuery>();
	}
};


class CreatorReselect : public Creator{
public:
	unique_ptr<Query> factoryMethod() const override{
		return make_unique<ReselectQuery>();
	}
};


class CreatorUpdate : public Creator{
public:
	unique_ptr<Query> factoryMethod() const override{
		return make_unique<UpdateQuery>();
	}
};


class CreatorPrint : public Creator{ 
public:
	unique_ptr<Query> factoryMethod() const override{
		return make_unique<PrintQuery>();
	}
};

// function parse first command and create necessary Query 
Query* parseCommand(string& query);



