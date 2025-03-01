
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <variant>
#include <cstring>

//using namespace std;


/*
 * Структура, хранящая данные о времени. 
 * Переменные: 
 *    hour - час,
 *    minute - минуты.
 */
struct TimeHM {
  int hour;
  int minute;
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

using Value = std::variant<int, double, std::string>;
/*
 * Структура, хранящая данные о результате работы с базой данных.
 * Переменная:
 *  data - фрагмент базы данных
 */
struct result {
  std::vector<std::string> data;
  
  //Функция добавляет в структуру новую строку или массив строк (фрагмент базы данных)
  void add(const std::string& data);
  void add(const std::vector<std::string>& data);
};

//Методы(запросы) для работы с базой данных.
enum class ComType {SELECT, RESELECT, INSERT, UPDATE, DELETE, PRINT};
//Названия столбцов в базе данных.
enum class Field {TIME, ROOM, SUBJNAME, TEACHER, GROUP};
//Оператор сортировки.
enum class Order {ASC, DESC};
//Бинарные операции.
enum class BinOp {LT, GT, EQ, LT_EQ, GT_EQ, NEQ, LIKE};


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
  public:
    Query(const std::string &query);
    virtual ~Query() = default;
    //Функция, выделяющая запрос из строчки и определяющая тип команды (функция для парсинга).
    virtual void parse() = 0;
    ComType getCommand() const { return command_;}
};

/*
 * Подкласс запрсов вида select, reselect (для выборки данных).
 * Переменная: condition_ - вектор условий 
 * fields_ - вектор полей, которые нужно вывести.
 */
class SelectingQuery : public Query{
public:
  SelectingQuery(const std::string &query);
  void parse() override;
  const std::vector<Cond>& getConditions() const { return condition_; }
  const std::vector<Field>& getFields() const {return fields_; }
private:
  std::vector<Cond> condition_;
  std::vector<Field> fields_;
};

/*
 * Подкласс запрсов вида insert, delete.
 * Переменная: values_ - вектор пар для добавления или удаления.
 */
class AssigningQuery : public Query {
public:
  AssigningQuery(const std::string &query);
  void parse() override;
  const std::vector<std::pair<Field, Value>>& getValues() const { return values_;}
private:
  std::vector<std::pair<Field, Value>> values_;
};

/*
 * Подкласс запрсов update (для обновления данных). 
 */
class UpdateQuery : public SelectingQuery, public AssigningQuery { 
public:
  UpdateQuery(const std::string &query);
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
  PrintQuery(const std::string &query);
  void parse() override;
  const std::vector<Field>& getFields() const { return fields_;}
  const std::vector<std::pair<Field, Order>>& getSortFields() const { return sort_fields_;}
};





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
  public:
    Schedule();
    Schedule(FILE* fin);
    ~Schedule();
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
    result startQuery(Query& query);
    Schedule* getSchedule() const {return schedule_;}
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
};
