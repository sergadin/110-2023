#include "Schedule.h"
#include <iostream>
#include <fstream>
#include <locale>
#include <cstring>
#include <vector>
#include <string>

static Query* parseSelectingQuery(const std::string& query);
static Query* parseAssigningQuery(const std::string& query);
static Query* parseUpdateQuery(const std::string& query);
static Query* parseInsertQuery(const std::string& query);
static Query* parsePrintQuery(const std::string& query);
static Query* parseDeleteQuery(const std::string& query);

static Query* parseSelectingQuery(const std::string& query) {
    SelectingQuery* q = new SelectingQuery(query);
    try {
        q->parse();
        return q;
    } catch (Exception &err) {
        delete q;
        return nullptr;
    }
}

static Query* parseAssigningQuery(const std::string& query) {
    AssigningQuery* q = new AssigningQuery(query);
    try {
        q->parse();
        return q;
    } catch (Exception &err) {
        delete q;
        return nullptr;
    }
}

static Query* parseUpdateQuery(const std::string& query) {
    UpdateQuery* q = new UpdateQuery(query);
    try {
        q->UpdateQuery::parse();
        return q;
    } catch (Exception &err) {
        delete q;
        return nullptr;
    }
}

static Query* parseInsertQuery(const std::string& query) {
    InsertQuery* q = new InsertQuery(query);
    try {
        q->parse();
        return q;
    } catch (Exception &err) {
        delete q;
        return nullptr;
    }
}

static Query* parsePrintQuery(const std::string& query) {
    PrintQuery* q = new PrintQuery(query);
    try {
        q->parse();
        return q;
    } catch (Exception &err) {
        delete q;
        return nullptr;
    }
}

static Query* parseDeleteQuery(const std::string& query) {
    DeleteQuery* q = new DeleteQuery(query);
    try {
        q->parse();
        return q;
    } catch (Exception &err) {
        delete q;
        return nullptr;
    }
}

void registerParsers() {
    Query::register_parser(parseSelectingQuery);
    Query::register_parser(parseUpdateQuery);
    Query::register_parser(parseInsertQuery);
    Query::register_parser(parsePrintQuery);
    Query::register_parser(parseDeleteQuery);
    Query::register_parser(parseAssigningQuery);
}

int main() {
    Schedule schedule;

    std::cout << "Загрузка базы из текстового файла" << std::endl;
    {
        std::ifstream file("schedule.txt");
        if (!file.is_open()) {
            std::cerr << "Ошибка открытия файла: schedule.txt" << std::endl;
            return 1;
        }

        Date date;
        int lesson, room, group;
        char subject_name[128];
        FullName teacher;
        while (file >> date.day >> date.month >> lesson >> room >> subject_name >> teacher.surname >> teacher.name >> teacher.patronymic >> group) {
            Entry* entry = new Entry(date, lesson, room, subject_name, teacher, group);
            schedule.addEntry(entry);
        }

        file.close();
    }
    std::cout << "База загружена." << std::endl;

    std::cout << "Добавление нового пункта в расписание" << std::endl;
    {
        std::ofstream file("scheduleout.txt");
        Date newDate = {15, 10};
        FullName newTeacher = {"Петров", "Иван", "Иванович"};
        Entry* newEntry = new Entry(newDate, 3, 101, "Физика", newTeacher, 211);
        if (!schedule.checkTimeCross(newDate, 3, newTeacher, 101, 211)) {
            schedule.addEntry(newEntry);
            std::cout << "Новый пункт добавлен." << std::endl;
        } else {
            std::cerr << "Накладка времени!" << std::endl;
            delete newEntry;
        }
        schedule.saveToFile(file);
    }

    std::cout << "Удаление пункта из расписания" << std::endl;
    {
        Date deleteDate = {15, 10};
        schedule.deleteEntry(deleteDate, 3, 101);
        std::cout << "Пункт удален." << std::endl;
    }

    std::cout << "Получение частных расписаний" << std::endl;
    {
        std::vector<Cond> conditions = {
            Cond(TEACHERLASTNAME, EQ, std::string("Иванов")),
            Cond(GROUP, EQ, 210)
        };
        std::vector<Entry*> result = schedule.select(conditions);
        for (const auto& entry : result) {
            std::cout << entry->toString() << std::endl;
        }
        std::cout << "Частные расписания получены." << std::endl;
    }
    std::cout << "Вывод всего расписания" << std::endl;
    {
        std::vector<Entry*> allEntries = schedule.select({});
        if (allEntries.empty()) {
            std::cout << "Расписание пустое." << std::endl;
        } else {
            schedule.print(allEntries);
            std::cout << "Расписание выведено." << std::endl;
        }
    }
    return 0;
}


