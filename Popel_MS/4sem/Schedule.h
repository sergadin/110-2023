
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <variant>
#include <pair>
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
}

//Методы(запросы) для работы с базой данных.
typedef enum {SELECT, RESELECT, INSERT, UPDATE, DELETE, PRINT} ComType;
//Названия столбцов в базе данных.
typedef enum {TIME, ROOM, SUBJNAME, TEACHER, GROUP} Field;
//Оператор сортировки.
typedef enum {ASC, DESC} Order;
//Бинарные операции.
typedef enum {LT, GT, EQ, LT_EQ, GT_EQ, NEQ, LIKE} BinOp;



/*
 * Класс запрсов.
 * Переменная: command_ - тип обрабатываемого запроса
 */
class Query{
  private:
    ComType command_;
  public:
    Query(const std::string &query);
    //Функция, выделяющая запрос из строчки и определяющая тип команды
    virtual void parse() = 0;
};

/*
 * Подкласс запрсов вида select, reselect.
 * Переменная: condition_ - вектор условий 
 */
class SelectingQuery : public Query{
  SelectingQuery(const std::string &query);
  void parse() override;
private:
  std::vector<Cond> condition_;
};

/*
 * Подкласс запрсов вида insert, delete.
 * Переменная: values_ - вектор  
 */
class AssigningQuery : public Query {
  InsertQuery(const std::string &query);
  void parse() override;
private:
  std::vector<std::pair<Field, Value>> values_;
};

/*
 * Подкласс запрсов update. 
 */
class UpdateQuery : public SelectingQuery, public AssigningQuery { 
  UpdateQuery(const std::string &query);
  void parse() override;
};

/*
 * Подкласс запрсов print.
 * Переменная: condition_ - вектор условий 
 */
class PrintQuery : public Query {
  std::vector<Field> fields_;
  std::vector<std::pair<Field, Order> sort_fields_>;
  PrintQuery(const std::string &query);
  void parse() override;
};

using Value = std::variant<int, double, std::string>;

/*
 * Класс условий.
 * Переменные:
 * field_ - поле - название столбца
 * operation_ - бинарная операция
 * value_ - значение, содержащееся в ячейке
 */
class Cond{
  private: 
    Field field_;
    BinOp operation_;
    Value value_;
  public:
    Cond(Field fld, BinOp optn, Value val);
    const Field getField() const {return field_};
    const BinOp getOperation() const {return operation_};
    const Value getVal() const {return value_};
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
    Entry(TimeHM time, int room, char subjName, FullName teacher, int group): time_(time), room_(room), teacher_(teacher), group_(group){
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
    void updateEntry(const TimeHM& time, int room, Subject* newEntry);
    //Функция выбора ячейки для работы с ней
    std::vector<Entry*> select(const std::vector<Cond>& crit);
    //Функция выбора из уже имеющихся ячеек
    std::vector<Entry*> reselect(const std::vector<Entry*>& selected, const std::vector<Cond>& crit);
    //Функция вывода подходящих ячеек на экран
    void print(const std::vector<Entry*>& entries/*, const std::vector<Field>& fields*/);
    //Функция, сохраняющая в файл массив ячеек (базу данных)
    void saveToFile(FILE* fout);
    
}

/*
 * Класс базы данных
 * Переменная: schedule_ - расписание (массив ячеек)
 */
class DataBase{
  private:
    Schedule *schedule_;
  public:
    DataBase(FILE* fin);
    ~DataBase();
    //Функция, получающая в виде строчки результат обработки запроса
    result startQuery(Query& query);
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
