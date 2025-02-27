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

