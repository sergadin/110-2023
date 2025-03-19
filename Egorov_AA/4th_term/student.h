#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <variant>
#include <cstring>
#include <list>
#include <fstream>


// Структура ФИО
struct FullName {
    char last_name[64];
    char name[64];
    char patronymic[64];
};


// Класс ошибок
class Exception {
private:
    int code_;
    std::string mess_;
public:
    Exception(int c, std::string m) {
        code_ = c;
        mess_ = m;
    }
    int getCode() const { return code_; }
    std::string getMessage() const { return mess_; }
};

using Value = std::variant<int, double, std::string>;

// Класс ячеек в базе данных
class Entry {
private:
    FullName student_;
    int group_;
    double rating_;
    char* info_;

public:
    Entry(FullName student, int group, double rating, char* info);

};


// Структура, хранящая данные о результате работы с базой данных
struct result {
    std::vector<Entry> entry;  // Результаты выборки, построенные по запросу
    std::string message;  // Сообщения о статусе операций
    Exception error;  // Ошибки

    void addEntry(const Entry& ent);
    void addMessage(const std::string& mes);
    void addError(const Exception& err);
};


typedef enum { SELECT, RESELECT, INSERT, UPDATE, DELETE, PRINT } CommandType;  // Команды для работы с базой данных

typedef enum { NAME, GROUP, RATING, INFO } Field;  // Названия столбцов в базе данных

typedef enum { ASC, DESC } Order;  // Оператор сортировки

typedef enum { LT, GT, EQ, NE, LE, GE, LIKE } RelationType;  // Отношение порядка


// Класс условий.
class Condition {
private:
    Field field_;
    RelationType operation_;
    Value value_;
public:
    Condition(Field field, RelationType rel, Value val);
    const Field getField() const { return field_; }
    const RelationType getOperation() const { return operation_; }
    const Value getVal() const { return value_; }
};


// Класс запросов
class Query {
private:
    CommandType command_;
    std::string query_;
    using parser_fn = void (*)(Query&, const std::string& query);
    static std::list<parser_fn> parsers;
public:
    Query(const std::string& query);
    virtual ~Query() = default;
    virtual void parse() = 0;  // Функция, выделяющая запрос из строчки и определяющая тип команды (функция для парсинга)
    CommandType getCommand() const { return command_; }
    static Query* do_parse(const std::string& query);
    static void register_parser(parser_fn p);
};


// Подкласс запрсов вида select, reselect (для выборки данных).
class SelectingQuery : public Query {
    SelectingQuery(const std::string& query);
    void parse() override;
    virtual void parseCond();  // Функция для переопределения в UpdateQuery (функция-дублер переопределенной parse)
    virtual void parseCondTriple(const std::string& frag);
    const std::vector<Condition>& getConditions() const { return condition_; }
    const std::vector<Field>& getFields() const { return fields_; }
    static void parse(Query& q, const std::string& query);  // Функция, позволяющая проверить тип запроса и допусакющая запрос до парсинга
private:
    std::vector<Condition> condition_;
    std::vector<Field> fields_;
};


// Подкласс запрсов вида insert, delete.
class AssigningQuery : public Query {
    AssigningQuery(const std::string& query);
    void parse() override;
    virtual void parseKeyVal();  // Функция для переопределения в UpdateQuery (функция-дублер переопределенной parse)
    virtual void parseKeyValTriple(const std::string& frag);
    const std::vector<std::pair<Field, Value>>& getValues() const { return values_; }
    static void parse(Query& q, const std::string& query);
private:
    std::vector<std::pair<Field, Value>> values_;
};


// Подкласс запрсов update (для обновления данных)
class UpdateQuery : public SelectingQuery, public AssigningQuery {
    UpdateQuery(const std::string& query);
    void parseCond() override;
    void parseKeyVal() override;
    void parseCondTriple(const std::string& frag) override;
    void parseKeyValTriple(const std::string& frag) override;
    static void parse(Query& q, const std::string& query);
};


// Подкласс запросов print для вывода данных
class PrintQuery : public Query {
private:
    std::vector<Field> fields_;
    std::vector<std::pair<Field, Order>> sort_fields_;
public:
    PrintQuery(const std::string& query);
    void parse() override;
    void parseTriple(const std::string& frag);
    const std::vector<Field>& getFields() const { return fields_; }
    const std::vector<std::pair<Field, Order>>& getSortFields() const { return sort_fields_; }
    static void parse(Query& q, const std::string& query);
};



// Класс списка студентов
class Student {
private:
    std::vector<Entry*> student_;
public:
    Student();
    Student(FILE* fin);
    ~Student();
    std::map<FullName, std::vector<int>> studentInd;
    std::map<int, std::vector<int>> groupInd;
    std::map<char[128], std::vector<int>> subjectInd;

    void buildInd();  // Функция, конструирующая и присваивающая индексы

    std::vector<int> getCritInd(const std::string& crit);  // Функция, получающая индекс по названию/номеру

    std::vector<int> intesectInd(const std::vector<int>& ind1, const std::vector<int>& ind2);  // Функция, "пересекающая" множество индексов (для поиска по нескольким критериям)

    void addEntry(Entry* entry);  // Функция добавления новой ячейки

    void deleteEntry(int room);  // Функция удаления ячейки

    void updateEntry(int room, Entry* newEntry);  // Функция обновления уже существующей ячейки

    std::vector<Entry*> select(const std::vector<Condition>& crit);  // Функция выбора ячейки для работы с ней

    std::vector<Entry*> reselect(const std::vector<Entry*>& selected, const std::vector<Condition>& crit);  // Функция выбора из уже имеющихся ячеек

    void print(const std::vector<Entry*>& entries);  //Функция вывода подходящих ячеек на экран

    void saveToFile(FILE* fout);  // Функция, сохраняющая в файл массив ячеек (базу данных)

};


// Класс базы данных
class DataBase {
private:
    Student* student_;
public:
    DataBase(FILE* fin);
    ~DataBase();

    result startQuery(std::string& query);  // Функция, получающая в виде строчки результат обработки запроса
    Student* getStudnet() const { return student_; }
};

#endif // STUDENT_H