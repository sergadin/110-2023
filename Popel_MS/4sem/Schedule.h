#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <variant>
#include <cstring>
#include <list>
#include <fstream>
#include <regex> //Это для масок и шаблонов
#include <memory>
#include <sstream>
//using namespace std;

/*
 * Структура, хранящая данные о дате пары.
 * Переменные:
 *  day - день,
 *  month - месяц,
 */
struct Date{
  int day;
  int month;
};


/*
 * Структура, хранящая данные о ФИО преподавателя.
 * Переменные:
 *  surname - фамилия,
 *  name - имя,
 *  patronymic - отчество.
 */
struct FullName {
  char surname[64];
  char name[32];
  char patronymic[64];
};

/*
 * Класс ошибок.
 * Переменные: code_ - код ошибки, mess_ - причина ошибки;
 */
class Exception {
  private:
    int code_;
    std::string mess_;
  public:
    Exception(int c, std::string m) : code_(c), mess_(m) {}
    int getCode() const { return code_; }
    std::string getMessage() const { return mess_; }
};

using Value = std::variant<int, double, std::string, Date, FullName>;

/*
 * Класс ячеек в базе данных.
 * Переменные:
 * time_ - время пары в расписании
 * room_ - номер аудитории
 * subject_name_ - название предмета
 * teacher_ - ФИО преподавателя
 * group_ - номер группы
 */
class Entry{
  private: 
    Date date_;
    int lesson_;
    int room_;
    char subject_name_[128];
    FullName teacher_;
    int group_;
    
  public:
    Entry(Date date, int lesson, int room, const char* subjName, FullName teacher, int group): date_(date), lesson_(lesson), room_(room), teacher_(teacher), group_(group){
      strncpy(subject_name_, subjName, sizeof(subject_name_));
    }
    
  Date getDate() const { return date_; }
  int getLesson() const { return lesson_; }
  int getRoom() const { return room_; }
  const char* getSubjectName() const { return subject_name_; }
  FullName getTeacher() const { return teacher_; }
  int getGroup() const { return group_; }
  
  void setDate(const Date& date) { date_ = date; }
    void setLesson(int lesson) { lesson_ = lesson; }
    void setRoom(int room) { room_ = room; }
    void setSubjectName(const char* subjName) {
        strncpy(subject_name_, subjName, sizeof(subject_name_));
    }
    void setTeacher(const FullName& teacher) { teacher_ = teacher; }
    void setGroup(int group) { group_ = group; }
};

/*
 * Структура, хранящая данные о результате работы с базой данных.
 * Переменные:
 */
struct result {
    std::vector<Entry> entry;// результаты выборки, построенные по запросу
    std::string message; //сообщения о статусе операций
    Exception error; //ошибки

  result() : entry(), message(), error(0, ""){}

    void addEntry(const Entry& ent){entry.push_back(ent);}
    void addMessage(const std::string& mes){message = mes;}
    void addError(const Exception& err){error = err;}
};

//Методы(запросы) для работы с базой данных.
typedef enum {SELECT, RESELECT, ASSIGN, INSERT, UPDATE, DELETE, PRINT} ComType;
//Названия столбцов в базе данных.
typedef enum {DAY, LESSON_NUM, ROOM, SUBJNAME, TEACHERNAME, TEACHERPATR, TEACHERLASTNAME, GROUP, NONE_FIELD} Field;
//Оператор сортировки.
typedef enum {ASC, DESC} Order;
//Бинарные операции.
typedef enum {LT, GT, EQ, LT_EQ, GT_EQ, NEQ, LIKE} BinOp;


/*
 * Класс условий.
 * Переменные:
 * field_ - поле - название столбца, по нему выполняется условие
 * operation_ - бинарная операция сравнения
 * value_ - значение для сравнения, содержащееся в ячейке
 */
class Cond{
  private: 
    Field field_;
    BinOp operation_;
    Value value_;
  public:
    Cond(Field fld, BinOp optn, Value val) : field_(fld), operation_(optn), value_(val) {}
    Field getField() const {return field_;}
    BinOp getOperation() const {return operation_;}
    Value getVal() const {return value_;}
};

/*
 * Класс запрсов.
 * Переменная: command_ - тип обрабатываемого запроса
 */
class Query{
  private:
    ComType command_;
    std::string query_;
    using parser_fn = Query * (*)(const std::string &query);
    static std::list<parser_fn> parsers;
  public:
    Query(const std::string &query) : command_(SELECT), query_(query) {}

    virtual ~Query() = default;
    //Функция, выделяющая запрос из строчки и определяющая тип команды (функция для парсинга).
    virtual void parse() = 0;
    ComType getCommand() const { return command_;}
    static Query * do_parse(const std::string &query);
    static void register_parser(parser_fn p);
    static void clear_parsers();
  protected:
    void setCommand(ComType command) { command_ = command; }
    virtual const std::string& getQueryString() const { return query_; }
};

/*
 * Подкласс запрсов вида select, reselect (для выборки данных).
 * Переменная: condition_ - вектор условий 
 * fields_ - вектор полей, которые нужно вывести.
 */
class SelectingQuery : virtual public Query{
public:
  SelectingQuery(const std::string &query) : Query(query), condition_(), fields_() {}
  void parse() override;
  //Функция для переопределения в UpdateQuery (функция-дублер переопределенной parse)
  void parseCond();
  const std::vector<Cond>& getConditions() const { return condition_; }
  const std::vector<Field>& getFields() const {return fields_; }
  //Функция, позволяющая проверить тип запроса и допускающая запрос до парсинга
  //static void parse(Query& q, const std::string &query);
  bool parseTriple(const std::string& triple);
private:
  std::vector<Cond> condition_;
  std::vector<Field> fields_;  
};

/*
 * Подкласс запрсов вида insert, delete.
 * Переменная: values_ - вектор пар для добавления или удаления.
 */
class AssigningQuery : virtual public Query {
public:
  AssigningQuery(const std::string &query) : Query(query), values_() {}
  void parse() override;
//Функция для переопределения в UpdateQuery (функция-дублер переопределенной parse)
  const std::vector<std::pair<Field, Value>>& getValues() const { return values_;}
  //static void parse(Query& q, const std::string &query);
protected:
  bool parseAssigningTriple(const std::string& triple);
private:
  std::vector<std::pair<Field, Value>> values_;

};

/*
 * Подкласс запрсов update (для обновления данных). 
 */
class UpdateQuery : public SelectingQuery, public AssigningQuery { 
public:
  UpdateQuery(const std::string &query) : Query(query), SelectingQuery(query), AssigningQuery(query) {}
  void parse() override;
  //static void parse(Query& q, const std::string &query);
};

/*
 * Подкласс запросов insert для вставки новых данных.
 */

class InsertQuery : public AssigningQuery {
public:
    InsertQuery(const std::string& query) : Query(query), AssigningQuery(query) {}
    void parse() override;
};

/*
 * Подкласс запросов print для вывода данных.
 * Переменная: fields_ - вектор полей для вывода.
 * sort_fields_ - вектор пар для сортировки.
 */
class PrintQuery : public Query {
private:
  std::vector<Field> fields_;
  std::vector<std::pair<Field, Order>> sort_fields_;
public:
  PrintQuery(const std::string &query) : Query(query), fields_(), sort_fields_() {}
  void parse() override;
  const std::vector<Field>& getFields() const { return fields_;}
  const std::vector<std::pair<Field, Order>>& getSortFields() const { return sort_fields_;}
  //static void parse(Query& q, const std::string &query);
};

/*
 * Подкласс запросов delete для удаления данных.
 */

class DeleteQuery : public SelectingQuery {
private:
    std::vector<Cond> conditions;

public:
    DeleteQuery(const std::string& query) : Query(query), SelectingQuery(query), conditions() {}
    void parse() override;

    const std::vector<Cond>& getConditions() const { return conditions; }
};


//Функции для более простого парсинга
Field parseField(const std::string& fieldStr);
BinOp parseBinOp(const std::string& opStr);
Value parseValue(const std::string& valueStr);
std::vector<std::pair<Date, Date>> parseDateRange(const std::string& dateStr);
std::vector<std::pair<int, int>> parseLessonRange(const std::string& lessonStr);

/*
 * Класс расписания.
 * Переменные:
 * schedule_ - само расписание - вектор ячеек
 * teacherInd - индекс преподавателя
 * groupInd - индекс группы
 * roomInd - индекс аудитории
 * timeInd - индекс времени пары
 * subjectInd - индекс предмета
 */
class Schedule{
  private: 
    std::vector<Entry*> schedule_;
  public:
    Schedule();
    Schedule(FILE* fin);
    ~Schedule();
    /*std::map<FullName, std::vector<int>> teacherInd;
    std::map<int, std::vector<int>> groupInd;
    std::map<int, std::vector<int>> roomInd;
    std::map<TimeHM, std::vector<int>> timeInd;
    std::map<char[128], std::vector<int>> subjectInd;*/
    
    //Функция, конструирующая и присваивающая индексы
    //void buildInd();
    //Функция, получающая индекс по названию/номеру
    //std::vector<int> getCritInd(const std::string& crit);
    //Функция, "пересекающая" множество индексов (для поиска по нескольким критериям)
    //std::vector<int> intesectInd(const std::vector<int>& ind1, const std::vector<int>& ind2);
    //Функция, проверяющая совпадение времени для одной аудитории, группы и т.п.
    bool checkTimeCross(const Date& date1, const Date& date2);
    //Функция добавления новой ячейки
    void addEntry(Entry* entry);
    //Функция удаления ячейки
    void deleteEntry(const Date& date, int lesson, int room);
    // Функция обновления уже существующей ячейки
    void updateEntry(const Date& date, int lesson, int room, Entry* newEntry);
    //Функция выбора ячейки для работы с ней
    std::vector<Entry*> select(const std::vector<Cond>& crit);
    //Функция выбора из уже имеющихся ячеек
    std::vector<Entry*> reselect(const std::vector<Entry*>& selected, const std::vector<Cond>& crit);
    //Функция вывода подходящих ячеек на экран
    void print(const std::vector<Entry*>& entries/*, const std::vector<Field>& fields*/);
    //Функция, сохраняющая в файл массив ячеек (базу данных)
    void saveToFile(FILE* fout);
    std::vector<Entry*> deleteEntries(const std::vector<Cond>& crit);
};

/*
 * Класс базы данных
 * Переменная: schedule_ - расписание (массив ячеек).
 */
class DataBase{
  private:
    Schedule *schedule_;
    std::vector<Entry*> previousSelection;
  public:
    DataBase(FILE* fin);
    ~DataBase();
    DataBase(const DataBase&) = delete;
    DataBase& operator=(const DataBase&) = delete;
    //Функция, получающая в виде строчки результат обработки запроса
    result startQuery(std::string& query);
    Schedule* getSchedule() const {return schedule_;}
};

bool compareDates(const Date& date1, const Date& date2, BinOp operation);

bool compareLessons(int lesson, int lessonNum, BinOp operation);

bool compareInts(int val1, int val2, BinOp operation);

bool compareStrings(const std::string& str1, const std::string& str2, BinOp operation);

