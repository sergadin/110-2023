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
printf("Hello!!\n");
    registerParsers();
    return 0;
}
