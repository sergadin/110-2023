#include "Schedule.h"
#include <iostream>

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
    //std::cout << "Регистрация parseSelectingQuery: " << reinterpret_cast<void*>(parseSelectingQuery) << std::endl;
    Query::register_parser(parseSelectingQuery);
    //std::cout << "Регистрация parseUpdateQuery: " << reinterpret_cast<void*>(parseUpdateQuery) << std::endl;
    Query::register_parser(parseUpdateQuery);
    //std::cout << "Регистрация parseInsertQuery: " << reinterpret_cast<void*>(parseInsertQuery) << std::endl;
    Query::register_parser(parseInsertQuery);
    //std::cout << "Регистрация parsePrintQuery: " << reinterpret_cast<void*>(parsePrintQuery) << std::endl;
    Query::register_parser(parsePrintQuery);
    //std::cout << "Регистрация parseDeleteQuery: " << reinterpret_cast<void*>(parseDeleteQuery) << std::endl;
    Query::register_parser(parseDeleteQuery);
    //std::cout << "Регистрация parseAssigningQuery: " << reinterpret_cast<void*>(parseAssigningQuery) << std::endl;
    Query::register_parser(parseAssigningQuery);
}

int main() {
    FILE* fin = fopen("schedule.txt", "r");
    if (!fin) {
        printf("Problems with openning file\n");
        Query::clear_parsers();
        return -1;
    }
    DataBase db(fin);
    fclose(fin);
  
  
    registerParsers();
    std::string query = "INSERT room=130 subject=Math teacherLastName=Иванов group=210 day=14.03 lessonNum=3 end";

    result res = db.startQuery(query);

    if (res.error.getCode() != 0) {
        printf("Incorrect Query\n");
        Query::clear_parsers();
        return -1;
    }
    std::cout << res.message << std::endl;
    Query::clear_parsers();

    return 0;
}



