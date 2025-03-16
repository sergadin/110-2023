#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <variant>
#include <cstring>
#include <list>
#include <fstream>

//using namespace std;


/*
 * Структура, хранящая данные о времени. 
 * Переменные: 
 *    startHour - час начала,
 *    startMinute - минута начала,
 *    endHour - час окончания,
 *    endMinute - минута окончания.
 */
struct TimeHM {
  int startHour;
  int startMinute;
  int endHour;
  int endMinute;
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
    Exception(int c, std::string m){
      code_ = c;
      mess_ = m;
    }
    int getCode() const { return code_; }
    std::string getMessage() const { return mess_; }
};

using Value = std::variant<int, double, std::string>;

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
    TimeHM time_;
    int room_;
    char subject_name_[128];
    FullName teacher_;
    int group_;
    
  public:
    Entry(TimeHM time, int room, const char* subjName, FullName teacher, int group): time_(time), room_(room), teacher_(teacher), group_(group){
      strncpy(subject_name_, subjName, sizeof(subject_name_));
    }
};

/*
 * Структура, хранящая данные о результате работы с базой данных.
 * Переменные:
 */
struct result {
    std::vector<Entry> entry;// результаты выборки, построенные по запросу
    std::string message; //сообщения о статусе операций
    Exception error; //ошибки

    void addEntry(const Entry& ent);
    void addMessage(const std::string& mes);
    void addError(const Exception& err);
};

//Методы(запросы) для работы с базой данных.
typedef enum {SELECT, RESELECT, INSERT, UPDATE, DELETE, PRINT} ComType;
//Названия столбцов в базе данных.
typedef enum {TIME, ROOM, SUBJNAME, TEACHER, GROUP} Field;
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
    Cond(Field fld, BinOp optn, Value val);
    const Field getField() const {return field_;}
    const BinOp getOperation() const {return operation_;}
    const Value getVal() const {return value_;}
};

/*
 * Класс запрсов.
 * Переменная: command_ - тип обрабатываемого запроса
 */
class Query{
  private:
    ComType command_;
    std::string query_;
    using parser_fn = void (*)(Query&, const std::string &query);
    static std::list<parser_fn> parsers;
  public:
    Query(const std::string &query);
    virtual ~Query() = default;
    //Функция, выделяющая запрос из строчки и определяющая тип команды (функция для парсинга).
    virtual void parse() = 0;
    ComType getCommand() const { return command_;}
    static Query * do_parse(const std::string &query);
    static void register_parser(parser_fn p);
};

/*
 * Подкласс запрсов вида select, reselect (для выборки данных).
 * Переменная: condition_ - вектор условий 
 * fields_ - вектор полей, которые нужно вывести.
 */
class SelectingQuery : public Query{
  SelectingQuery(const std::string &query);
  void parse() override;
  //Функция для переопределения в UpdateQuery (функция-дублер переопределенной parse)
  virtual void parseCond();
  virtual void parseCondTriple(const std::string &frag);
  const std::vector<Cond>& getConditions() const { return condition_; }
  const std::vector<Field>& getFields() const {return fields_; }
  //Функция, позволяющая проверить тип запроса и допускающая запрос до парсинга
  static void parse(Query& q, const std::string &query);
private:
  std::vector<Cond> condition_;
  std::vector<Field> fields_;
};

/*
 * Подкласс запрсов вида insert, delete.
 * Переменная: values_ - вектор пар для добавления или удаления.
 */
class AssigningQuery : public Query {
  AssigningQuery(const std::string &query);
  void parse() override;
//Функция для переопределения в UpdateQuery (функция-дублер переопределенной parse)
  virtual void parseKeyVal();
  virtual void parseKeyValTriple(const std::string &frag);
  const std::vector<std::pair<Field, Value>>& getValues() const { return values_;}
  static void parse(Query& q, const std::string &query);
private:
  std::vector<std::pair<Field, Value>> values_;
};

/*
 * Подкласс запрсов update (для обновления данных). 
 */
class UpdateQuery : public SelectingQuery, public AssigningQuery { 
  UpdateQuery(const std::string &query);
  void parseCond() override;
  void parseKeyVal() override;
  void parseCondTriple(const std::string &frag) override;
  void parseKeyValTriple(const std::string &frag) override;
  static void parse(Query& q, const std::string &query);
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
  PrintQuery(const std::string &query);
  void parse() override;
  void parseTriple(const std::string &frag);
  const std::vector<Field>& getFields() const { return fields_;}
  const std::vector<std::pair<Field, Order>>& getSortFields() const { return sort_fields_;}
  static void parse(Query& q, const std::string &query);
};


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
    std::map<FullName, std::vector<int>> teacherInd;
    std::map<int, std::vector<int>> groupInd;
    std::map<int, std::vector<int>> roomInd;
    std::map<TimeHM, std::vector<int>> timeInd;
    std::map<char[128], std::vector<int>> subjectInd;
    
    //Функция, конструирующая и присваивающая индексы
    void buildInd();
    //Функция, получающая индекс по названию/номеру
    std::vector<int> getCritInd(const std::string& crit);
    //Функция, "пересекающая" множество индексов (для поиска по нескольким критериям)
    std::vector<int> intesectInd(const std::vector<int>& ind1, const std::vector<int>& ind2);
    //Функция, проверяющая совпадение времени для одной аудитории, группы и т.п.
    bool checkTimeCross(const TimeHM& time1, const TimeHM& time2);
    //Функция добавления новой ячейки
    void addEntry(Entry* entry);
    //Функция удаления ячейки
    void deleteEntry(const TimeHM& time, int room);
    //Функция обновления уже существующей ячейки
    void updateEntry(const TimeHM& time, int room, Entry* newEntry);
    //Функция выбора ячейки для работы с ней
    std::vector<Entry*> select(const std::vector<Cond>& crit);
    //Функция выбора из уже имеющихся ячеек
    std::vector<Entry*> reselect(const std::vector<Entry*>& selected, const std::vector<Cond>& crit);
    //Функция вывода подходящих ячеек на экран
    void print(const std::vector<Entry*>& entries/*, const std::vector<Field>& fields*/);
    //Функция, сохраняющая в файл массив ячеек (базу данных)
    void saveToFile(FILE* fout);
    
};

/*
 * Класс базы данных
 * Переменная: schedule_ - расписание (массив ячеек).
 */
class DataBase{
  private:
    Schedule *schedule_;
  public:
    DataBase(FILE* fin);
    ~DataBase();
    //Функция, получающая в виде строчки результат обработки запроса
    result startQuery(std::string& query);
    Schedule* getSchedule() const {return schedule_;}
};
