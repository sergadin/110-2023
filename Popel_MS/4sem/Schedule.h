#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <variant>
#include <cstring>
#include <list>
#include <fstream>
#include <regex> // Это для масок и шаблонов
#include <memory>
#include <sstream>
#include <unordered_map>

//using namespace std;

class Exception {
private:
    int code_;
    std::string mess_;
public:
    Exception(int c, std::string m) : code_(c), mess_(m) {}
    int getCode() const { return code_; }
    std::string getMessage() const { return mess_; }
};

using Value = std::variant<int, double, std::string>;

class Entry {
private:
    int day_;
    int month_;
    int lesson_;
    int room_;
    char subject_name_[128];
    std::string teacher_;
    int group_;

public:
    Entry(int day, int month, int lesson, int room, const char* subjName, std::string teacher, int group)
        : day_(day), month_(month), lesson_(lesson), room_(room), teacher_(teacher), group_(group) {
        strncpy(subject_name_, subjName, sizeof(subject_name_));
    }

    int getDay() const { return day_; }
    int getMonth() const { return month_; }
    int getLesson() const { return lesson_; }
    int getRoom() const { return room_; }
    const char* getSubjectName() const { return subject_name_; }
    std::string getTeacher() const { return teacher_; }
    int getGroup() const { return group_; }

    void setDay(int day) { day_ = day; }
    void setMonth(int month) { month_ = month; }
    void setLesson(int lesson) { lesson_ = lesson; }
    void setRoom(int room) { room_ = room; }
    void setSubjectName(const char* subjName) {
        strncpy(subject_name_, subjName, sizeof(subject_name_));
    }
    void setTeacher(
    std::string teacher) { teacher_ = teacher; }
    void setGroup(int group) { group_ = group; }

    std::string toString() const {
        std::stringstream ss;
        ss << "Date: " << day_ << "." << month_
           << ", Lesson: " << lesson_
           << ", Room: " << room_
           << ", Subject: " << subject_name_
           << ", Teacher: " << teacher_
           << ", Group: " << group_;
        return ss.str();
    }
};

struct ClientInfo {
    int socket;
    std::vector<Entry*> previousSelection;

    ClientInfo() : socket(0), previousSelection() {}
};

struct result {
    std::vector<Entry> entry; // результаты выборки, построенные по запросу
    std::string message; // сообщения о статусе операций
    Exception error; // ошибки

    result() : entry(), message(), error(0, "") {}

    void addEntry(const Entry& ent) { entry.push_back(ent); }
    void addMessage(const std::string& mes) { message = mes; }
    void addError(const Exception& err) { error = err; }
};

typedef enum { SELECT, RESELECT, ASSIGN, INSERT, UPDATE, DELETE, PRINT } ComType;
typedef enum { DAY, MONTH, LESSON_NUM, ROOM, SUBJNAME, TEACHERNAME, GROUP, NONE_FIELD } Field;
typedef enum { ASC, DESC } Order;
typedef enum { LT, GT, EQ, LT_EQ, GT_EQ, NEQ, LIKE } BinOp;

class Cond {
private:
    Field field_;
    BinOp operation_;
    Value value_;
public:
    Cond(Field fld, BinOp optn, Value val) : field_(fld), operation_(optn), value_(val) {}
    Field getField() const { return field_; }
    BinOp getOperation() const { return operation_; }
    Value getVal() const { return value_; }
};

class Query {
private:
    ComType command_;
    std::string query_;
    using parser_fn = Query* (*)(const std::string& query);
    static std::list<parser_fn> parsers;
public:
    Query(const std::string& query) : command_(SELECT), query_(query) {}

    virtual ~Query() = default;
    virtual void parse() = 0;
    ComType getCommand() const { return command_; }
    static Query* do_parse(const std::string& query);
    static void register_parser(parser_fn p);
    static void clear_parsers();
protected:
    void setCommand(ComType command) { command_ = command; }
    virtual const std::string& getQueryString() const { return query_; }
};

class SelectingQuery : virtual public Query {
public:
    SelectingQuery(const std::string& query) : Query(query), condition_(), fields_() {}
    void parse() override;
    void parseCond();
    const std::vector<Cond>& getConditions() const { return condition_; }
    const std::vector<Field>& getFields() const { return fields_; }
    bool parseTriple(const std::string& triple);
private:
    std::vector<Cond> condition_;
    std::vector<Field> fields_;
};

class AssigningQuery : virtual public Query {
public:
    AssigningQuery(const std::string& query) : Query(query), values_() {}
    void parse() override;
    const std::vector<std::pair<Field, Value>>& getValues() const { return values_; }
protected:
    bool parseAssigningTriple(const std::string& triple);
private:
    std::vector<std::pair<Field, Value>> values_;
};

class UpdateQuery : public SelectingQuery, public AssigningQuery {
public:
    UpdateQuery(const std::string& query) : Query(query), SelectingQuery(query), AssigningQuery(query) {}
    void parse() override;
};

class InsertQuery : public AssigningQuery {
public:
    InsertQuery(const std::string& query) : Query(query), AssigningQuery(query) {}
    void parse() override;
};

class PrintQuery : public Query {
private:
    std::vector<Field> fields_;
    std::vector<std::pair<Field, Order>> sort_fields_;
public:
    PrintQuery(const std::string& query) : Query(query), fields_(), sort_fields_() {}
    void parse() override;
    const std::vector<Field>& getFields() const { return fields_; }
    const std::vector<std::pair<Field, Order>>& getSortFields() const { return sort_fields_; }
};

class DeleteQuery : public SelectingQuery {
private:
    std::vector<Cond> conditions;

public:
    DeleteQuery(const std::string& query) : Query(query), SelectingQuery(query), conditions() {}
    void parse() override;

    const std::vector<Cond>& getConditions() const { return conditions; }
};

Field parseField(const std::string& fieldStr);
BinOp parseBinOp(const std::string& opStr);
Value parseValue(const std::string& valueStr);
std::vector<std::pair<int, int>> parseDateRange(const std::string& dateStr);
std::vector<std::pair<int, int>> parseLessonRange(const std::string& lessonStr);

class Schedule {
private:
    std::vector<Entry*> schedule_;
    std::unordered_map<std::string, std::vector<int>> teacher_index_;
    std::unordered_map<int, std::vector<int>> group_index_;
    std::unordered_map<int, std::vector<int>> room_index_;
    std::unordered_map<int, std::vector<int>> lesson_index_;
    std::unordered_map<std::string, std::vector<int>> subject_index_;

public:
    Schedule();
    Schedule(FILE* fin);
    ~Schedule();
    bool checkTimeCross(int day, int month, int lesson, std::string teacher, int room, int group);
    void addEntry(Entry* entry);
    void deleteEntry(int day, int month, int lesson, int room);
    void updateEntry(int day, int month, int lesson, int room, Entry* newEntry);
    std::vector<Entry*> select(const std::vector<Cond>& crit);
    std::vector<Entry*> reselect(const std::vector<Entry*>& selected, const std::vector<Cond>& crit);
    void print(const std::vector<Entry*>& entries);
    void saveToFile(std::ofstream& fout);
    std::vector<Entry*> deleteEntries(const std::vector<Cond>& crit);

    void buildIndexes();
    void loadFromFile(const std::string& filename);
};

class DataBase {
private:
    Schedule* schedule_;
    std::unordered_map<int, ClientInfo> clientSessions;
public:
    DataBase(FILE* fin);
    ~DataBase();
    DataBase(const DataBase&) = delete;
    DataBase& operator=(const DataBase&) = delete;
    result startQuery(int clientSocket, std::string& query);
    Schedule* getSchedule() const { return schedule_; }
};

bool compareDates(int day1, int month1, int day2, int month2, BinOp operation);
bool compareLessons(int lesson, int lessonNum, BinOp operation);
bool compareInts(int val1, int val2, BinOp operation);
bool compareStrings(const std::string& str1, const std::string& str2, BinOp operation);
bool compareIntStr(const std::string& str1, const std::string& str2, BinOp operation);
