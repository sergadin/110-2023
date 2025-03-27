#include "Schedule.h"
#include <iostream>





namespace {
    struct ParserRegistrar {
        ParserRegistrar() {
            Query::register_parser(parseSelectingQuery);
            Query::register_parser(parseAssigningQuery);
            Query::register_parser(parseUpdateQuery);
            Query::register_parser(parseInsertQuery);
            Query::register_parser(parsePrintQuery);
            Query::register_parser(parseDeleteQuery);
        }
    };
    static ParserRegistrar registrar; 
}

int main() {
    FILE* fin = fopen("schedule.txt", "r");
    if (!fin) {
        printf("Problems with oppening file\n");
        return -1;
    }
    DataBase db(fin);
    fclose(fin);

    std::string query = "SELECT teacher=Иванов group=100-499 subject=Математический_анализ end PRINT teacher group date_time room subject sort group end";

    result res = db.startQuery(query);

    if (res.error.getCode() != 0) {
        printf("Incorrect Query\n");
        return -1;
    }

    std::cout << res.message << std::endl;

    return 0;
}

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
