#include <vector>
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <cstring>
#include <iomanip>
#include <variant>
#include <fstream>
#include <cstdio>
#include <cmath>

using namespace std;

class Table;

class Student;

class Query {
protected:
    string query_;

public:
	explicit Query(const string &query) : query_(query) {}
	virtual ~Query() = default;
	virtual void print() = 0;
	virtual void parse() = 0;

	virtual void apply(Table& table) = 0;

	virtual const Student* getStudent() const{
		return nullptr;
	}
};


class AddQuery;
class DeleteQuery;
class SelectQuery;
class UpdateQuery;


using Value = variant<int, double, string>;

enum class Field {NAME, GROUP, RATING, ADRESS};

enum class Bin_Op {GT, LT, EQ, LT_EQ, GT_EQ, IN};


struct FullName{
	char firstname[64];
	char middlename[64];
	char lastname[64];
};

inline void safeStrCopy(char* dest, const string& src, size_t maxLen){
	strncpy(dest, src.c_str(), maxLen - 1);
	dest[maxLen - 1] = '\0';
}


void parseFullName(const string& nameStr, FullName& name){
	istringstream iss(nameStr);
	vector<string> parts;
	string part;

	while(iss >> part) {
		parts.push_back(part);
	}
	
	if(parts.size() < 2){
		throw invalid_argument(
				"Invalid name format."
		);
	}
	
	safeStrCopy(name.firstname, parts[0], sizeof(name.firstname));

	safeStrCopy(name.lastname, parts.back(), sizeof(name.lastname));

	string middlename;
	if(parts.size() > 2){

		for(size_t i = 1; i < parts.size() - 1; i++){
			if(i != 1) middlename = middlename + " ";
			middlename = middlename + parts[i];
		}
	}

	safeStrCopy(name.middlename, middlename, sizeof(name.middlename));

}


class Student{
private:
	FullName name_;
	int groupNumber_;
	double rating_;
	char email_[64];
public:

	Student(const FullName& name, int group, double rating, const char* email): name_(name),
       	groupNumber_(group),	rating_(rating){
		strncpy(this->email_, email, sizeof(this->email_) - 1);
		this->email_[sizeof(this->email_) - 1] = '\0';
	}

	const FullName& getName() const {return name_;}

	int getGroupNumber() const {return groupNumber_;}

	double getRating() const {return rating_;}

	const char* getEmail() const { return email_;}

	void setName(const FullName& name){ name_ = name;}

	void setGroup(int group) {groupNumber_ = group;}

	void setRating(double rating) { rating_ = rating;}

	void setEmail(const string& email){
		strncpy(email_, email.c_str(), sizeof(email_) - 1);
		email_[sizeof(email_)-1] = '\0';
	}

};



unique_ptr<Query> parseCommand(const string& query);




class Cond{
private:
	Field field;
	Bin_Op binop;
	Value val;
public:
	Cond(Field f, Bin_Op op, Value v) : field(f), binop(op), val(v){}
	
	Field getField() const{
		return field;
	}

	Bin_Op getBin_Op() const{
		return binop;
	}

	string getFieldStr() const{
		switch(field){
			case Field::GROUP : return "GROUP";
				break;
			case Field::RATING : return "RATING";
                                break;
			case Field::NAME : return "NAME";
                                break;
			default:
				return "UNKNOWN";
				break;
		}
	}

	string getBin_OpStr() const{
		switch(binop){
			case Bin_Op::GT : return ">";
				break;
			case Bin_Op::LT : return "<";
				break;
			case Bin_Op::EQ : return "=";
				break;
			case Bin_Op::GT_EQ : return ">=";
				break;
			case Bin_Op::LT_EQ : return "<=";
				break;
			default:
				return "UNKNOWN";
				break;
		}
	}

	Value getValue() const{
		return visit([](auto&& arg) -> Value{
			using T = decay_t<decltype(arg)>;
			if constexpr ( is_same_v<T, string>){
				return arg;
			}
			else{
				return arg;
			}
		},val);
	}
	
	void printValue() const{
		visit([] (const auto& arg){
			using T = decay_t<decltype(arg)>;
			if constexpr (is_same_v<T, string>){
				cout << arg << endl;
			}
			else{
				cout << arg << endl;
			}
		}, val);
	}

	
};


Cond parseTriple(const string& condition){
	istringstream iss(condition);
	string fieldStr, opStr, valueStr;
	iss >> fieldStr >> opStr;
	getline(iss >> ws, valueStr);

	transform(fieldStr.begin(), fieldStr.end(), fieldStr.begin(), ::toupper);
	transform(opStr.begin(), opStr.end(), opStr.begin(), :: toupper);

	Field field;

	if(fieldStr == "GROUP") field = Field::GROUP;
	else if(fieldStr == "RATING") field = Field::RATING;
	else if(fieldStr == "NAME") field = Field::NAME;
	else if(fieldStr == "ADRESS") field = Field::ADRESS;
	else throw invalid_argument("Unkmown field: " + fieldStr);

	Bin_Op op;
	if( opStr == ">") op = Bin_Op::GT;
	else if( opStr == "<") op = Bin_Op::LT;
	else if( opStr == "=") op = Bin_Op::EQ;
	else if( opStr == ">=") op = Bin_Op::GT_EQ;
	else if( opStr == "<=") op = Bin_Op::LT_EQ;
	else throw invalid_argument("Unknown operator: " + opStr);

	Value value;
	try{
		switch(field){
			case Field::GROUP:
				value = stoi(valueStr);
				break;
			case Field::RATING:
				value = stod(valueStr);
				break;
			case Field::NAME:
				if(valueStr.front() == '"' && valueStr.back() == '"'){
					valueStr = valueStr.substr(1, valueStr.size() - 2);
				}
				value = valueStr;
				break;
		}
	}
	catch (const exception& e){
		throw invalid_argument("Invalid value for field " + fieldStr + " : " + valueStr);
	}

	return Cond(field, op, value);
}


vector<string> splitAssignments(const string& input){
	vector<string> assignments;
	bool inQuotes = false;
	string current;
	char prevChar = '\0';

	for(char c : input){
		if(c == '"' && prevChar != '\\'){
			inQuotes = !inQuotes;
		}

		if(!inQuotes && (c == ' ' || c == '\t')){
			if(!current.empty()){
				assignments.push_back(current);
				current.clear();
			}
		}
		else{
			if(c != '\\' || (prevChar == '\\' && inQuotes)){
				current = current + c;
			}
			prevChar = c;
		}
	}

	if(!current.empty()){
		assignments.push_back(current);
	}

	vector<string> corrected;

	for(size_t i = 0; i < assignments.size(); ){
		if(i + 2 < assignments.size() && 
				(assignments[i+1] == "=" || assignments[i+1] == ">" ||
				 assignments[i+1] == "<" || assignments[i+1] == ">=" ||
				 assignments[i+1] == "<=")){
			corrected.push_back(assignments[i] + " " + assignments[i+1] + " " +
					assignments[i+2]);
			i = i + 3;
		}
		else{
			corrected.push_back(assignments[i]);
			i = i + 1;
		}
	}

	return corrected;
}


bool checkStudentConditions(const Student& student, const vector<Cond>& conditions){
	const double eps = 1e-6;

	for(const auto& cond : conditions){
		const Field field = cond.getField();
		const Bin_Op op = cond.getBin_Op();
		const Value& value = cond.getValue();

		try{
			switch(field){
				case Field::GROUP:{
					int studentValue = student.getGroupNumber();
					int condValue = get<int>(value);

					switch(op){
						case Bin_Op::GT:
							if(!(studentValue > condValue)){
								return false;
							}
							break;
						case Bin_Op::LT:
							if(!(studentValue < condValue)){
								return false;
							}
							break;
						case Bin_Op::EQ:
							if(studentValue != condValue){
								return false;
							}
							break;
						case Bin_Op::GT_EQ:
							if(studentValue < condValue){
								return false;
							}
							break;
						case Bin_Op::LT_EQ:
							if(studentValue > condValue){
								return false;
							}
							break;
						default: throw invalid_argument("Unsupported operator for GROUP");

					}
					break;
				}

				case Field::RATING:{
					double studentValue = student.getRating();
					double condValue = get<double>(value);

					switch(op){
						case Bin_Op::GT:
							if(!(studentValue > condValue)){
								return false;
							}
							break;
						case Bin_Op::LT:
							if(!(studentValue < condValue)){
								return false;
							}
							break;
						case Bin_Op::EQ:
							if(fabs(studentValue - condValue) >= eps){
								return false;
							}
							break;
						case Bin_Op::GT_EQ:
							if(!(studentValue >= condValue - eps)){
								return false;
							}
							break;
						case Bin_Op::LT_EQ:
							if(!(studentValue <= condValue + eps)){
								return false;
							}
							break;
						default: throw invalid_argument("Unsupported operator for RATING");
					}
					break;
				}

				case Field::ADRESS:{
					string studentValue = student.getEmail();
					string condValue = get<string>(value);

					if(op != Bin_Op::EQ){
						throw invalid_argument("Only EQ operator supported for ADRESS");
					}
					if(studentValue != condValue){
						return false;
					}
					break;
				}

				default:
					throw invalid_argument("Unknown field");

			}
		}
		catch(const bad_variant_access&){
			throw invalid_argument("Invalid value type for field");
		}
	}

	return true;
}


class AddQuery : public Query {
private:
	Student student_data;
	
public:
	explicit AddQuery(const string& query) : Query(query),
		student_data(FullName{}, 0, 0.0, " ")	{}

	void print() override {
		cout << "ADD: "
			<< student_data.getName().firstname << " "
			<< student_data.getName().middlename << " "
			<< student_data.getName().lastname << endl;
		cout << "Group: " << student_data.getGroupNumber() << endl;
		cout << "Rating: " << student_data.getRating() << endl;
		cout << "Email: " << student_data.getEmail() << endl;
   	}

	const Student* getStudent() const override{
		return &student_data;
	}

	void parse() override{
		size_t addPos = query_.find("ADD");

		string content = query_.substr(addPos + 3);
		vector<string> assignments = splitAssignments(content);

		if(assignments.empty() || assignments.back() != "END"){
			throw invalid_argument("Query must end with END");
		}
		assignments.pop_back();
		for(const auto& assignment : assignments) {
			try{
				Cond cond = parseTriple(assignment);
				applyCondition(cond);
			}
			catch (const exception& e){
				cerr << "Warning Skipping invalid condition" << assignment << ": " << e.what() <<endl;
			}
		}
	}
	
	void apply(Table& table) override;


private:
	void checkTokenFormat(istringstream& iss, char expected){
		string eq;
		if(!(iss >>eq) || eq != "="){
			throw invalid_argument("Expected '=' after field");
		}
	}

	void applyCondition(const Cond& cond){
		switch(cond.getField()){
			case Field::NAME:
				FullName name;
				parseFullName(get<string>(cond.getValue()), name);
				student_data.setName(name);
				break;
			case Field::GROUP:
				student_data.setGroup(get<int>(cond.getValue()));
				break;
			case Field::RATING:
				student_data.setRating(get<double>(cond.getValue()));
				break;
			case Field::ADRESS:
				student_data.setEmail(get<string>(cond.getValue()));
				break;
			default:
				throw invalid_argument("Unsupported field");
		}
	}

};


class SelectQuery : public Query {
private:
	vector<Cond> conditions_;

public:
	explicit SelectQuery(const string& query) : Query(query) {}

	void print() override {
        	cout << "this is SELECT (" << query_ << ")" << endl;
   	 }
	
	void parse() override{
		size_t selectPos = query_.find("SELECT");
		string content = query_.substr(selectPos + 6);

		vector<string> assignments = splitAssignments(content);
		if(assignments.empty() || assignments.back() != "END"){
			throw invalid_argument("SELECT query must end with END");
		}
		assignments.pop_back();
		
		for(const auto& assignment : assignments){
			try{
				Cond cond = parseTriple(assignment);
				conditions_.push_back(cond);
			} catch (const exception& e){
				cerr << "Warning: skipping invalid condition " << assignment << ": " << e.what()
					<< endl;
			}
		}	
	}

	const vector<Cond>& getConditions() const{
		return conditions_;
	}
	
	void apply(Table& table) override;

};


class DeleteQuery : public Query{
private:
	vector<Cond> conditions_;

public:
	explicit DeleteQuery(const string& query) : Query(query) {}

	void parse() override{
		size_t deletePos = query_.find("DELETE");
		string content = query_.substr(deletePos + 6);

		vector<string> assignments = splitAssignments(content);
		if(assignments.empty() || assignments.back() != "END"){
			throw invalid_argument("DELETE query must end with END");
		}
		assignments.pop_back();

		for(const auto& assignment : assignments){
			try{
				Cond cond = parseTriple(assignment);
				conditions_.push_back(cond);
			} catch (const exception& e){
				cerr << "Warning skipping invalid condition " << assignment << ": " << e.what()
					<< endl;
			}
		}
	}

	const vector<Cond>& getConditions() const{
		return conditions_;
	}

	void print() override{
		cout << "DELETE QUERY:" << endl;
		cout << "Conditions:" << endl;

		for(const auto& cond : conditions_){
			cout << cond.getFieldStr() << " " << cond.getBin_OpStr() << " ";
			visit([](const auto& v) {cout << v; }, cond.getValue());
			cout << endl;
		}
	}
	
	void apply(Table& table) override;


};


class UpdateQuery : public Query{
private:
	vector<Cond> set_conditions_;
	vector<Cond> where_conditions_;

public:
	explicit UpdateQuery(const string& query) : Query(query) {}

	void parse() override{
		set_conditions_.clear();
		where_conditions_.clear();

		size_t updatePos = query_.find("UPDATE");
		size_t setPos = query_.find("SET");
		size_t wherePos = query_.find("WHERE");
		size_t endPos = query_.find("END");

		if(setPos == string::npos){
			throw invalid_argument("Missing SET");
		}
		if(wherePos == string::npos){
			throw invalid_argument("Missing WHERE");
		}
		if(endPos == string::npos){
			throw invalid_argument("Missing END");
		}

		string setPart = query_.substr(setPos + 3, wherePos - setPos - 3);

		vector<string> set_assignments = splitAssignments(setPart);
		for(const auto& assignment : set_assignments){
			try{

				Cond cond = parseTriple(assignment);
				if(cond.getBin_Op() != Bin_Op::EQ){
					throw invalid_argument("SET need '=' operator");
				}
				set_conditions_.push_back(cond);
			}catch (const exception& e){
				cerr << "Warning skipping invalid condition " << assignment << ": " << e.what()
					<< endl;
			}
		}

		string wherePart = query_.substr(wherePos + 5, endPos - wherePos - 5);

		vector<string> where_assignments = splitAssignments(wherePart);
		for(const auto& assignment : where_assignments){
			try{
				Cond cond = parseTriple(assignment);
				where_conditions_.push_back(cond);
			}catch (const exception& e){
				cerr << "Warning skipping invalid condition " << assignment << ": " << e.what()
					<< endl;
			}
		}
	}
	

	const vector<Cond>& getSetConditions() const{
		return set_conditions_;
	}
	

	const vector<Cond>& getWhereConditions() const{
		return where_conditions_;
	}

	void print() override{
		cout << "UPDATE QUERY" << endl;
		cout << "SET cond:" << endl;
		for(const auto& cond : set_conditions_){
			cout << cond.getFieldStr() << " " << cond.getBin_OpStr() << " ";
			visit([](const auto& v) { cout << v;}, cond.getValue());
			cout << endl;
		}

		cout << "WHERE cond:" << endl;
		for(const auto& cond : where_conditions_){
			cout << cond.getFieldStr() << " " << cond.getBin_OpStr() << " ";
			visit([](const auto& v) {cout << v;}, cond.getValue());
			cout << endl;
		}
	}

	void apply(Table& table) override;


};



class Table {
private:
	vector<Student> students_;

public:
	
	void loadFromFile(const string& filename) {
		ifstream file(filename);
		if (!file.is_open()) {
			throw runtime_error("Cannot open file: " + filename);
         	 }

         	 students_.clear();
   		 string line;
   		 size_t line_num = 0;

    		while (getline(file, line)) {
        		line_num++;
        		istringstream iss(line);
		        Student student{FullName{}, 0, 0.0, " "};
		        string field;
		        size_t field_num = 0;

		        try {
		            while (getline(iss, field, ';')) {
		                switch (field_num++) {
					case 0: {
		                       		 FullName name;
		                       		 parseFullName(field, name);
		                       		 student.setName(name);
                		       		 break;
                   			 }
                   			 case 1:
                       				 if (!field.empty())
                           				 student.setGroup(stoi(field));
                       			 break;
                   			 case 2:
                       				 if (!field.empty())
                           				 student.setRating(stod(field));
                       				 break;
                   			 case 3:
                       				 student.setEmail(field);
                       				 break;
                    			default:
                        			break;
               			 }
           			 }

            		if (student.getName().firstname[0] == '\0' || student.getName().lastname[0] == '\0') {
                		throw invalid_argument("Missing required name fields");
           		 }

           		 students_.push_back(student);
       			 } catch (const exception& e) {
           			 cerr << "Error in line " << line_num << ": " << e.what() << endl;
           			 cerr << line << endl;
       			 }
   		 }
}


void saveToFile(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Cannot create file: " + filename);
    }

    for (const auto& student : students_) {
        file << student.getName().firstname << " "
             << student.getName().middlename << " "
             << student.getName().lastname << ";"
             << student.getGroupNumber() << ";"
             << student.getRating() << ";"
             << student.getEmail() << endl;
    }
}


	explicit Table(const string& filename){
		loadFromFile(filename);
	}


	const vector<Student>& getStudents() const{
		return students_;
	}
	
	vector<Student> selectStudents(const SelectQuery& query) const{
		vector<Student> result;
		for(const auto& student : students_){
			if(checkStudentConditions(student, query.getConditions())){
				result.push_back(student);
			}
		}
		return result;
	}
	
	size_t deleteStudents(const DeleteQuery& query){
		auto new_end = remove_if(students_.begin(), students_.end(), [&](const Student& student){
				return checkStudentConditions(student, query.getConditions());
				});
		size_t deleted_count = students_.end() - new_end;
		students_.erase(new_end, students_.end());
		return deleted_count;
	}
	
	void addStudent(const AddQuery& query){
		students_.push_back(*query.getStudent());
	}

private:
	void applySetConditions(Student& student, const vector<Cond>& set_conditions){
		for(const auto& cond : set_conditions){
			const Field field = cond.getField();
			const Value& value = cond.getValue();

			switch(field){
				case Field::GROUP:
					student.setGroup(get<int>(value));
					break;
				case Field::RATING:
					student.setRating(get<double>(value));
					break;
				case Field::ADRESS:
					student.setEmail(get<string>(value));
					break;
				case Field::NAME:
					FullName name;
					parseFullName(get<string>(value), name);
					student.setName(name);
					break;
				default:
					throw invalid_argument("Unsupported field in SET");
			}
		}
	}

public:
	size_t updateStudents(const UpdateQuery& query){
		const auto& where_conditions = query.getWhereConditions();
		const auto& set_conditions = query.getSetConditions();

		size_t update_count = 0;

		for(auto& student : students_){
			if(checkStudentConditions(student, where_conditions)){
				applySetConditions(student, set_conditions);
				update_count++;
			}
		}
		return update_count;
	}


};


void AddQuery::apply(Table& table){
	table.addStudent(*this);
}

void SelectQuery::apply(Table& table){
	vector<Student> selected = table.selectStudents(*this);
}

void DeleteQuery::apply(Table& table){
	size_t deleted = table.deleteStudents(*this);
}

void UpdateQuery::apply(Table& table) {
	size_t updated = table.updateStudents(*this);
}




unique_ptr<Query> parseCommand(const string& query) {
    // Проверка на пустую строку
	if(query.empty() || query.find_first_not_of(" \t\n\v\f\r") == string::npos) {
		cerr << "Error: Empty query" << endl;
		return nullptr;
	}

	size_t first_char_pos = query.find_first_not_of(" \t\n\v\f\r");
	if(first_char_pos != 0){
		cout<< "Error: Command cannot start with spaces" << endl;
		return nullptr;
	}	


	istringstream iss(query);
	string command;
	iss >> command;
	transform(command.begin(), command.end(), command.begin(), ::toupper);

	if (command == "ADD") {
		return make_unique<AddQuery>(query);
	}
	else if (command == "SELECT") {
		return make_unique<SelectQuery>(query);
	}
	else if (command == "UPDATE"){
		return make_unique<UpdateQuery>(query);
	}
	else if (command == "DELETE"){
		return make_unique<DeleteQuery>(query);
	}


    cerr << "Error: Unknown command '" << command << "'" << endl;
    return nullptr;
}
	

class Database { 
private:
	Table table_;
	string db_file;
public:
	explicit Database(const string& filename) : db_file(filename), table_(filename){}

	void safeSave(){
		const string temp_file = db_file + ".tmp";

		table_.saveToFile(temp_file);

		if(remove(db_file.c_str()) != 0 ){
			throw runtime_error("failde to delete original file");
		}

		if(rename(temp_file.c_str(), db_file.c_str()) != 0){
			throw runtime_error("failde to rename temp file");
		}
	}

	Table& getTable(){
		return table_;
	}

};


/*int main(){
	string input;
	cout << "Enter command: " << endl;
	getline(cin, input);

	auto query = parseCommand(input);
	query->parse();
	query->print();

	return 0;
}
*/

/*
int main(){
	try{
			
		string input;
		cout << "Enter command" << endl;
		getline(cin, input);
		auto query = parseCommand(input);
		query->parse();
		const Student* student_ptr = query->getStudent();
		Database db("students.txt");
		FullName name;
		parseFullName("Olga Dmitrievna Smirnova", name);
		Student student(name, 106, 4.5, "olgasmirn@mail.ru");
		vector<Cond> conditions1 = {
			Cond(Field::GROUP, Bin_Op::GT, 100),
			Cond(Field::RATING, Bin_Op::GT_EQ, 4.0)
		};
		bool result = checkStudentConditions(student, conditions1);
		cout << result << endl;
		
		vector<Student> find = db.getTable().selectStudents(conditions1);
		for(const auto& student : find){
			cout << student.getGroupNumber() << endl;
		}

		db.getTable().addStudent(student);
		db.getTable().addStudent(*student_ptr);
		db.getTable().saveToFile("updated_students.txt");

	}
	catch(const exception& e){
		cerr << e.what() << endl;
		return 1;
	}
	return 0;
}
*/


int main(){
	auto query = parseCommand("UPDATE SET GROUP = 215 WHERE GROUP = 210 RATING < 4.0 END");
	auto queryadd = parseCommand("ADD NAME = \"Maxim Sergeevich Miheev\" GROUP = 305 RATING = 4.2 END");
	query->parse();
	query->print();
	queryadd->parse();
	Database db("students.txt");
	query->apply(db.getTable());
	queryadd->apply(db.getTable());
	db.getTable().saveToFile("new_students.txt");

	return 0;

}	
